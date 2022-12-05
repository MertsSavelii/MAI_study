from flask import Flask, render_template, request, redirect
from flask_sqlalchemy import SQLAlchemy

app = Flask(__name__)
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///university.db'
app.config['SQLALCHEMY_TRACK_MODIFICATIONS'] = False

db = SQLAlchemy(app)


class University(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    name = db.Column(db.String(50), nullable=False)
    adress = db.Column(db.String(100), nullable=False)
    bachelor_plans = db.relationship('Bachelor', backref="university", lazy='select')

    def __repr__(self):
        return '<University %r>' % self.id


class Bachelor(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    id_university = db.Column(db.Integer, db.ForeignKey('university.id'))
    num_of_spec = db.Column(db.String(10), nullable=False)
    name = db.Column(db.String(50), nullable=False)
    exams = db.Column(db.String(10), nullable=False)
    budget_score = db.Column(db.Integer)
    paid_score = db.Column(db.Integer)
    budget_places = db.Column(db.Integer)
    paid_places = db.Column(db.Integer)
    paid_cost = db.Column(db.Integer)

    def __repr__(self):
        return '<Bachelor_plan %r>' % self.id


@app.route('/', methods=['GET'])
def index():
    return render_template("index.html")


@app.route('/admin', methods=['GET'])
def admin():
    return render_template("admin.html")


@app.route('/admin_uni', methods=['GET'])
def admin_uni():
    university = University.query.order_by(University.id).all()
    return render_template("admin_uni.html", univers=university)


@app.route('/upd_uni/<int:id>',  methods=['POST', 'GET'])
def upd_uni(id):
    uni = db.session.query(University).get(id)
    if request.method == "GET":
        return render_template("upd_uni.html", univer=uni)
    else:
        uni.name = request.form['name']
        uni.adress = request.form['adress']
        try:
            db.session.add(uni)
            db.session.commit()
            return redirect('/admin_uni')
        except:
            return "Произошла ошибка"



@app.route('/del/uni/<int:id>',  methods=['GET'])
def dell_uni(id):
    uni = db.session.query(University).get(id)
    try:
        db.session.delete(uni)
        db.session.commit()
        return redirect('/admin_uni')
    except:
        return "Произошла ошибка"


@app.route('/admin_spec', methods=['GET'])
def admin_spec():
    spec = Bachelor.query.order_by(Bachelor.id).all()
    return render_template("admin_spec.html", bachelors=spec)


@app.route('/upd_spec/<int:id>',  methods=['POST', 'GET'])
def upd_spec(id):
    bachelor = db.session.query(Bachelor).get(id)
    uni = db.session.query(University).get(bachelor.id_university)
    uni_name = uni.name
    if request.method == "GET":
        return render_template("upd_spec.html", bach=bachelor, uni_name=uni_name)
    if request.method == "POST":
        bachelor.num_of_spec = request.form['num_of_spec']
        bachelor.name = request.form['name']
        bachelor.exams = request.form['exams']
        bachelor.budget_score = request.form['budget_score']
        bachelor.paid_score = request.form['paid_score']
        bachelor.budget_places = request.form['budget_places']
        bachelor.paid_places = request.form['paid_places']
        bachelor.paid_cost = request.form['paid_cost']
        try:
            db.session.add(bachelor)
            db.session.commit()
            return redirect('/admin_spec')
        except:
            return "Произошла ошибка"


@app.route('/del/spec/<int:id>',  methods=['GET'])
def dell_spec(id):
    spec = db.session.query(Bachelor).get(id)
    try:
        db.session.delete(spec)
        db.session.commit()
        return redirect('/admin_spec')
    except:
        return "Произошла ошибка"

@app.route('/add_univ', methods=['POST', 'GET'])
def add_uni():
    if request.method == "GET":
        return render_template("add_uni.html")
    if request.method == "POST":
        curr = University()
        curr.name = request.form['name']
        curr.adress = request.form['adress']
        try:
            db.session.add(curr)
            db.session.commit()
            return redirect('/admin')
        except:
            return "Произошла ошибка"


@app.route('/add_spec', methods=['POST', 'GET'])
def add_spec():
    if request.method == "POST":
        curr = Bachelor()
        curr.name_univers = request.form['univer_name']
        univer = db.session.query(University).filter(University.name == curr.name_univers).first()
        curr.id_univer = univer.id
        curr.num_of_spec= request.form['num_of_special']
        curr.name = request.form['name']
        curr.exam = request.form['exam']
        curr.budget_score = request.form['budget_score']
        curr.paid_score = request.form['paid_score']
        curr.budget_place = request.form['budget_place']
        curr.paid = request.form['paid']
        curr.cost = request.form['cost']
        try:
            db.session.add(curr)
            db.session.commit()
            return redirect('/add_spec')
        except:
            return "Произошла ошибка"
    else:
        univ_name = db.session.query(University.name).order_by(University.id).all()
        return render_template("add_spec.html", univers=univ_name)


@app.route('/user', methods=['POST', 'GET'])
def user():
    bachelors = Bachelor.query.order_by(Bachelor.id).all()
    if request.method == "POST":
        filter = request.form['desk']
        if filter == '1':
            bachelors = Bachelor.query.filter(Bachelor.budget_score != 0).order_by(Bachelor.budget_score).all()
        if filter == '2':
            bachelors = Bachelor.query.order_by(Bachelor.budget_score.desc()).all()
        if filter == '3':
            bachelors = Bachelor.query.order_by(Bachelor.paid_cost).all()
        if filter == '4':
            bachelors = Bachelor.query.order_by(Bachelor.paid_cost.desc()).all()
    return render_template("user.html", bachelors=bachelors)


@app.route('/search_exams', methods=['POST', 'GET'])
def search_exams():
    bachelors = Bachelor.query.order_by(Bachelor.id).all()
    if request.method == "POST":
        exam = request.form['exam']
        bachelors = Bachelor.query.filter(Bachelor.exams == exam).order_by(Bachelor.id).all()
    return render_template("search_exams.html", bachelors=bachelors)


@app.route('/search_spec', methods=['POST', 'GET'])
def search_spec():
    bachelors = Bachelor.query.order_by(Bachelor.id).all()
    if request.method == "POST":
        num_spec = request.form['num_of_spec']
        bachelors = Bachelor.query.filter(Bachelor.num_of_spec == num_spec).order_by(Bachelor.id).all()
    return render_template("search_spec.html", bachelors=bachelors)


if __name__ == "__main__":
    app.run(debug=False)
#include <complex>
#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

typedef complex<double> base;
 
void fft (vector<base> & a, bool invert) {
	int n = (int) a.size();
	if (n == 1)
        return;
 
	vector<base> a0 (n/2),  a1 (n/2);
	for (int i=0, j=0; i<n; i+=2, ++j) {
		a0[j] = a[i];
		a1[j] = a[i+1];
	}
	fft (a0, invert);
	fft (a1, invert);
 
	double ang = 2*M_PI /n;
    ang *= invert ? -1 : 1;

	base w (1),  wn (cos(ang), sin(ang));
	for (int i=0; i<n/2; ++i) {
		a[i] = a0[i] + w * a1[i];
		a[i+n/2] = a0[i] - w * a1[i];
		if (invert)
			a[i] /= 2,  a[i+n/2] /= 2;
		w *= wn;
	}
}

void MultiplyBigNum (const vector<int> & poli1, const vector<int> & poli2, vector<int> & res) {
	vector<base> fa (poli1.begin(), poli1.end()),  fb (poli2.begin(), poli2.end());
	size_t n = 1;
	while (n < max (poli1.size(), poli2.size()))
		n <<= 1;
	n <<= 1;
	fa.resize (n),  fb.resize (n);
 
	fft (fa, false),  fft (fb, false);
	for (size_t i=0; i<n; ++i)
		fa[i] *= fb[i];
	fft (fa, true);
 
	res.resize (n);
	for (size_t i=0; i<n; ++i)
		res[i] = int (fa[i].real() + 0.5);
	int carry = 0;
	//нормализуем результат
	for (size_t i=0; i<n; ++i) {
		res[i] += carry;
		carry = res[i] / 10;
		res[i] %= 10;
	}
}

void BigNumToPolinom(string big_num, vector<int>& poli){
	for(int i = 0; i < big_num.length(); ++i){
		poli.push_back(big_num[i] - '0');
	}
}

void PolinomToBigNum(vector<int> poli, string& big_num){
	for(int i = 0; i < poli.size(); ++i){
		big_num.push_back(poli[i] + '0');
	}
}

int main(){
	string big_num1, big_num2, res_big_num;
	vector<int> poli1, poli2, res_poli;
	cin >> big_num1 >> big_num2;
	BigNumToPolinom(big_num1, poli1);
	BigNumToPolinom(big_num2, poli2);
	MultiplyBigNum(poli1, poli2, res_poli);
	PolinomToBigNum(res_poli, res_big_num);
	cout << res_big_num << endl;
	return 0;
}
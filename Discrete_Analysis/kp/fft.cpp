#include <bits/stdc++.h>
using namespace std;

#define M_PI 3.14159265358979323846
#define SIZE_BLOCK 4096
typedef complex<double> cd;

vector<cd> fft(vector<cd>& a)
{
	int n = a.size();
	if (n == 1) return vector<cd>(1, a[0]);

	vector<cd> A0(n / 2), A1(n / 2);
	for (int i = 0; i < n / 2; i++) {
		A0[i] = a[i * 2];
		A1[i] = a[i * 2 + 1];
	}

	vector<cd> y0 = fft(A0),
			   y1 = fft(A1);

	vector<cd> y(n);
	double alpha;
	cd w;
	for (int k = 0; k < n / 2; k++) {
		alpha = -2*M_PI * k / n;
		w = cd(cos(alpha), sin(alpha));
		y[k] = y0[k] + w * y1[k];
		y[k + n / 2] = y0[k] - w * y1[k];
	}
	return y;
}

vector<cd> ifft(vector<cd>& y)
{
	y = fft(y);
	for(int i = 0; i < y.size(); ++i)
		y[i] /= y.size();
	vector<cd> a;
	a.push_back(y[0].real());
	for(int i = y.size() - 1; i >= 1; --i)
		a.push_back(y[i].real());
	return a;
}

vector<double> put_hann(vector<double>& value) // можно преподсчитать
{
	for (int i =0; i < SIZE_BLOCK; ++i) {
		double multiplier = 0.5 * (1 - cos(2*M_PI * i / (SIZE_BLOCK-1)));
		value[i] = multiplier * value[i];
	}
	return value;
}

vector<cd> ToComplex(vector<double>& value){
	vector<cd> res(SIZE_BLOCK);
	for(int i = 0; i < value.size(); i++)
		res[i] = value[i];
	return res;
}

long long FindMax(vector<cd>& value){
	long long max = LLONG_MIN;
	for(int i = 0; i < value.size(); i++)
		max = max < value[i].real() ? value[i].real() : max;
	return max;
}

int main()
{
	string file_name;
	int interval; // интервал между отсчётам
	cin >> file_name >> interval;
	// потом надо получить 4096 отсчёта из файла мп3
	vector<double> in_amp(SIZE_BLOCK);
	// in_app = from.mp3.file_name как-то так
	in_amp = put_hann(in_amp);
	vector<cd> in_complex = ToComplex(in_amp);
	vector<cd> res_fft = fft(in_complex);
	long long max = FindMax(res_fft);
	cout << max;
	return 0;
}
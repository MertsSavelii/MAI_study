#include <mpg123.h>
#include <bits/stdc++.h>

using namespace std;

typedef uint64_t TSize;
typedef int32_t TInt;

typedef complex<float> TComplex;

const TSize BLOCK_SIZE = 4096;

void ReadPCMFormMP3File(vector <float>& arr, const char* file_name) {
	mpg123_init();

   	int err;
    mpg123_handle *mh = mpg123_new(NULL, &err);
    unsigned char *buffer;
    size_t buffer_size;
    size_t done;

    int channels, encoding;
    long rate;
    buffer_size = mpg123_outblock(mh);
    buffer = (unsigned char*)malloc(buffer_size * sizeof(unsigned char));

    assert(mpg123_open(mh, file_name) == MPG123_OK);
    assert(mpg123_getformat(mh, &rate, &channels, &encoding) == MPG123_OK);
    
    for (int totalBtyes = 0; mpg123_read(mh, buffer, buffer_size, &done) == MPG123_OK; totalBtyes += done) {
        short* tst = reinterpret_cast<short*>(buffer);   
		for (int i = 0; i < buffer_size/2 ; i++){
			arr.push_back((float)tst[i]);
		}
    }
    free(buffer);
    mpg123_close(mh);
    mpg123_delete(mh);
    mpg123_exit();
}

void HannWindow(vector<TComplex>& value)
{
	for (int i =0; i < BLOCK_SIZE; ++i) {
		TComplex multiplier = 0.5 * (1 - cos(2*M_PI * i / (BLOCK_SIZE-1)));
		value[i] *= multiplier;
	}
}

void FFT(vector <TComplex> *arr) {
	TSize size = arr->size();
	if (size <= 1) {
		return;
	}
	vector <TComplex> arr1(size / 2);
	vector <TComplex> arr2(size / 2);

	for (TSize i = 0, j = 0; i < size; i += 2, j++) {
		arr1[j] = (*arr)[i];
		arr2[j] = (*arr)[i + 1];
	}

	FFT(&arr1);
	FFT(&arr2);

	const float coeff = 2 * M_PI / size;

	TComplex w(1.);
	TComplex wn(cos(coeff), sin(coeff));

	for (TSize i = 0; i < size / 2; i++) {
		(*arr)[i] = arr1[i] + w * arr2[i];
		(*arr)[i + size / 2] = arr1[i] - w * arr2[i];
		w *= wn;
	}
}

void TransformPCMToMaxAplitude(vector <float>& audio, vector <TSize>& out) {
	TSize audio_size = audio.size();
	TSize block_num = audio_size / BLOCK_SIZE;

	out.resize(0);

	for (TSize i = 0; i < block_num; i++) {
		vector <TComplex> complex_array(BLOCK_SIZE);
		for (TSize j = 0; j < BLOCK_SIZE; j++) {
			TComplex tmp(audio[i * BLOCK_SIZE + j], 0);
			complex_array[j] = tmp;
		}

		HannWindow(complex_array);

		FFT(&complex_array);

		TComplex max_real = abs(*max_element(complex_array.begin(), complex_array.end(), [](TComplex a, TComplex b){ return abs(a.real()) < abs(b.real()); }));
		out.push_back(log(max_real.real()));
	}
}

void FindMaxAmplitude(char *file_name, char * otstup, vector <TSize>& out) {
	vector <float> audio;
	ReadPCMFormMP3File(audio, file_name);
	vector <float> pcm;
	char* p;
	int os = strtol( otstup, &p, 10);
	cout << os << endl;
	for(int i = 0; i < audio.size(); i+= 1 + os)
		pcm.push_back(audio[i]);
	while(pcm.size() % BLOCK_SIZE != 0)
		pcm.push_back(0);
	TransformPCMToMaxAplitude(pcm, out);
}

int main(int argc, char *argv[])
{
	if (argc < 3) {
		cout << "to few arg\n";
		exit(1);
	}
	vector <TSize> res;
	FindMaxAmplitude(argv[1], argv[2], res);
	for(auto it: res)
		cout << it << endl;
	return 0;
}
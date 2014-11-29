#include "Wave.hpp"
#include <iostream>
#include <stdlib.h>
#include <math.h>

using namespace std;

/*
	x [-1,1] => [0,255]
*/
int normaliser(float i) {
	return (i+1)*255/2;
}

float denormaliser(int i) {
	return (((float) i)*2.0/255.0)-1;
}

void normaliserData(float* data, int size) {
	for (int i=0; i < size; i++) {
		data[i] = normaliser(data[i]);
	}
}

float* denormaliserData(unsigned char* data, int size) {
	float *dataOut = (float*) malloc(size*sizeof(float));
	for (int i=0; i < size; i++) {
		dataOut[i] = denormaliser(data[i]);
	}
	return dataOut;
}


/**
	Buff doit être initialisé à zéro
**/
void createFreq(float* buff, int periode, int nbrPeriodes) {
	int j = 0;
	for (int p=0; p < nbrPeriodes; p++) {
		for (int i =0; i < periode; i++) {
			float x = (float)i*(2.0*M_PI)/(float)periode;
			float val = sin(x);
			buff[j++] += val;
		}
	}
}

/**
	Buff doit être initialisé à zéro
**/
void createFreqV2(float* buff, float freq, float nbrEchanillonsPerSecs, int duree) {

	int size = duree * nbrEchanillonsPerSecs;
	float periode = nbrEchanillonsPerSecs/freq;

	for (int i=0; i < size; i++) {
		float x = (float)i*(2.0*M_PI)/(float)periode;
		float val = sin(x);
		buff[i] += val;
	}
}


void copySound(char *source, char *destination) {
	Wave* w = new Wave();
	w->read(source);

	unsigned char** data = new unsigned char*[1];
	unsigned char** dataCopy = new unsigned char*[1];
	int* size = (int*) malloc(sizeof(int));

	w->getData8(data, size);
	cout << *size << " lus" << endl;

	(*dataCopy) = new unsigned char[*size];

	int j = 0;
	for (int i=0; i < *size; i++) {
		unsigned int d = (*data)[i];
		(*dataCopy)[j++] = d;
	}

	Wave* copy = new Wave(*dataCopy, *size, 1, w->sampling_freq);
	copy->write(destination);
}

unsigned char* floatToChar(int size, float* datas) {
	unsigned char* dataOut = (unsigned char*) malloc(sizeof(unsigned char) * size);
	for (int i = 0; i < size; ++i) {
		dataOut[i] = (char) datas[i];
	}
	return dataOut;
}

unsigned char* floatNormalToChar(int size, float* datas) {
	normaliserData(datas, size);
	return floatToChar(size, datas);
}

float* charToFloatNormal(int size, unsigned char* datas) {
	return NULL; // TODO
}

float* createbuffer(int size) {
	float* datas = (float*) malloc(sizeof(float) * size);
	for (int i =0; i < size; i++) {
		datas[i] = 0;
	}
	return datas;
}

void createLa() {
	char destination[] = "sin_440.wav";
	
	int frequenceEnchantillon = 44100;
	float duree = 1;

	int size = duree * frequenceEnchantillon;
	float* datas = createbuffer(size);

	createFreqV2(datas, 440, frequenceEnchantillon, duree);
	normaliserData(datas, size);

	unsigned char* dataOut = floatToChar(size, datas);
	Wave* copy = new Wave(dataOut, size, 1, frequenceEnchantillon);
	copy->write(destination);
}

void DFT(float *signal, float *partie_reelle, float *partie_imaginaire, int N) {
	int total = N * N;
	cout << total << " octets à traiter" << endl;
	int pas = 0;
	int pourcent = 0;
	for (int k=0; k < N; k++) {
		partie_reelle[k] = 0;
		partie_imaginaire[k] = 0;
		for (int n=0; n < N; n++) {
			partie_reelle[k] += signal[n] * cos(2*M_PI*(k*n/N));
			partie_imaginaire[k] += signal[n] * sin(2*M_PI*(k*n/N));
			pas++;

			int pourcentActuel = (((float) pas / (float) total)) * 1000;
			if (pourcentActuel > pourcent) {
				cout << (float)pourcent/10 << " pourcents" << endl;
				pourcent = pourcentActuel;
			}
		}
		partie_imaginaire[k] *= -1;
	}
}

void test_fourier() {

	char source[] = "sin_440.wav";

	Wave* w = new Wave();
	w->read(source);

	unsigned char** data = new unsigned char*[1];
	int* size = new int(0);

	w->getData8(data, size);
	cout << *size << " lus" << endl;

	float *partie_reelle = (float*) malloc(*size*sizeof(float));
	float *partie_imaginaire = (float*) malloc(*size*sizeof(float));
	float *datas_normal = denormaliserData(*data, *size);

	DFT(datas_normal, partie_reelle, partie_imaginaire, 10000);
}

int main() {
	createLa();
	test_fourier();
}

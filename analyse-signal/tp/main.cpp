#include "Wave.hpp"
#include <iostream>
#include <stdlib.h>
#include <math.h>

using namespace std;

int normaliser(float i) {
	return (i+1)*255/2;
}

void normaliserData(float* data, int size) {
	for (int i=0; i < size; i++) {
		data[i] = normaliser(data[i]);
	}
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


int main() {
	cout << "Hello" << endl;

	char source[] = "Whistle.wav";
	char destination[] = "copy.wav";
	//copySound(source, destination);
	
	int frequenceEnchantillon = 44100;
	float duree = 10;

	int size = duree * frequenceEnchantillon;
	/*
	float* dataLa = (float*) malloc(sizeof(float) * size);
	float* dataSi = (float*) malloc(sizeof(float) * size);
	for (int i =0; i < size; i++) {
		dataLa[i] = 0;
		dataSi[i] = 0;
	}*/

	Wave* w = new Wave();
	unsigned char* dataOut = new unsigned char;
	dataOut = (unsigned char*) malloc(sizeof(char) * size);

	int nbrNotes = 10;
	float datas[nbrNotes][size/nbrNotes];
	int z = 0;
	for (int i=0; i < nbrNotes; i++) {
		for (int j=0; j < size/nbrNotes; j++)
			datas[i][j] = 0;

		createFreqV2(datas[i], 50*(i+1), frequenceEnchantillon, duree/nbrNotes);
		normaliserData(datas[i], size/nbrNotes);

		for (int j=0; j < size/nbrNotes; j++)
			dataOut[z++] = (int) datas[i][j];
	}
	

	Wave* copy = new Wave(dataOut, size, 1, frequenceEnchantillon);
	copy->write(destination);
}

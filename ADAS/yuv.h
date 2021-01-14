#ifndef _YUV_H_
#define _YUV_H_

#define _CRT_SECURE_NO_WARNINGS

#define ROUND1DEC(r) (round(r*10)/10)
#define ROUND2DEC(r) (round(r*100)/100)
#define ROUND3DEC(r) (round(r*1000)/1000)
#define ROUND4DEC(r) (round(r*10000)/10000)
#define ROUND5DEC(r) (round(r*100000)/100000)

#define clip(var) ((var >= 255.00) ? 255.00: (var<=0.00)?0:var)

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

typedef struct {
	uint8_t y;
	uint8_t u;
	uint8_t v;
} YUV;

typedef struct {
	double y;
	double u;
	double v;
} YUV_Double;

void createMess(YUV** matrix, uint8_t* output, int width, int height);

void setBetaValue(double* q, YUV_Double** yuv, int startPosition, int iCordFloor, int jCordFloor, int iCordCeil, int jCordCeil, char channel);

double calculateBicubicValue(YUV** yuvOrigin, YUV_Double** yuv, YUV_Double** Ix, YUV_Double** Iy, YUV_Double** Ixy, double WIDTH, double HEIGHT, double I, double J, double SF, char channel);

void createDerivative(YUV_Double** Ix, YUV_Double** Iy, YUV_Double** Ixy, YUV** yuv, int width, int height);

double calculateBilinearValue(YUV** yuv, double I, double J, double xScale, double yScale, char channel);

int getFrameCount(char* filename, int frame_size);

void allocateMatrix(YUV*** matrix, double WIDTH, double HEIGHT, double FACTOR);

void allocateMatrixTypeDouble(YUV_Double*** matrix, double WIDTH, double HEIGHT, double FACTOR);

void deallocateMatrix(YUV** matrix, double HEIGHT);

void allocateBuffer(uint8_t** data, double SIZE);

void deallocateBuffer(uint8_t* data);

void allocateYUVBuffer(YUV** data, double SIZE);

void deallocateYUVBuffer(YUV* data);

void fillBuffer(uint8_t* data, double DATASIZE, uint8_t* buffer, double START);

void createYUYV(uint8_t* input, uint8_t* output, double WIDTH, double HEIGHT);

void fillMatrix(YUV** yuv, uint8_t* y1, uint8_t* y2, uint8_t* u, uint8_t* v, double WIDTH, double HEIGHT);

void fillYUVBuffer(YUV* yuvArray, YUV** yuv, double WIDTH, double HEIGHT);

void createOutput(uint8_t* bufferOut, YUV* yuvArray, double SIZE);

void nearestNeighbourInterpolation(YUV** originalMatrix, YUV** matrix, double WIDTH, double HEIGHT, double FACTOR);

void bilinearInterpolation(YUV** originalMatrix, YUV** matrix, double WIDTH, double HEIGHT, double FACTOR);

void bicubicInterpolation(YUV** originalMatrix, YUV** matrix, double WIDTH, double HEIGHT, double SF);

double* getAlpha(double* beta, double* alpha);

uint8_t* getFrameFromVideo(char* fileForRead, int frameSize, int frameNumber);

#endif
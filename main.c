#include "yuv.h"
#define _CRT_SECURE_NO_WARNINGS
#define WIDTH 640 //row
#define HEIGHT 360 //column
#define SF 2

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>

//int main()
//{
//	uint32_t frameSize;
//	uint32_t bufferSize = 0;
//
//	uint8_t* bufferIn;
//	uint8_t* bufferOut;
//
//	char* fileToOpen;
//	char* fileToWrite;
//
//	fileToOpen = "C:\\Users\\kelava\\Desktop\\Dummy5.bin";
//
//	frameSize = (1280 * 720 * 2); //YUV422 format
//
//	FILE* fp1 = fopen(fileToOpen, "rb");
//
//	bufferIn = (uint8_t*)malloc(frameSize * sizeof(uint8_t));
//	bufferOut = (uint8_t*)malloc(frameSize * sizeof(uint8_t));
//
//	fread(bufferIn, 1, frameSize, fp1);
//	fclose(fp1);
//
//	volatile int i, j;
//
//#pragma region yuv
//
//	uint8_t* y;
//	y = (uint8_t*)malloc(360 * 640 * sizeof(uint8_t));
//	uint8_t* u;
//	u = (uint8_t*)malloc(360 * 640 * sizeof(uint8_t));
//	uint8_t* v;
//	v = (uint8_t*)malloc(360 * 640 * sizeof(uint8_t));
//
//	uint8_t* yuv[3];
//	yuv[0] = y;
//	yuv[1] = u;
//	yuv[2] = v;
//
//#pragma endregion
//
//#pragma region matrix
//
//	uint8_t* y1;
//	y1 = (uint8_t*)malloc(720 * 1280 * sizeof(uint8_t));
//	uint8_t* u1;
//	u1 = (uint8_t*)malloc(720 * 1280 * sizeof(uint8_t));
//	uint8_t* v1;
//	v1 = (uint8_t*)malloc(720 * 1280 * sizeof(uint8_t));
//
//	uint8_t* matrix[3];
//	matrix[0] = y1;
//	matrix[1] = u1;
//	matrix[2] = v1;
//
//#pragma endregion
//
//
//	int ct0 = 0, ct1 = 1, ct2 = 2, ct3 = 3;
//	for (i = 0; i < 720; i++)
//	{
//		for (j = 0; j < 1280; j = j + 2)
//		{
//			matrix[0][i * 1280 + j] = bufferIn[ct0];
//			matrix[1][i * 1280 + j] = bufferIn[ct1];
//			matrix[2][i * 1280 + j] = bufferIn[ct3];
//
//			matrix[0][i * 1280 + j + 1] = bufferIn[ct2];
//			matrix[1][i * 1280 + j + 1] = bufferIn[ct1];
//			matrix[2][i * 1280 + j + 1] = bufferIn[ct3];
//
//			ct0 = ct0 + 4;
//			ct1 = ct1 + 4;
//			ct2 = ct2 + 4;
//			ct3 = ct3 + 4;
//		}
//	}
//
//	for (i = 0; i < 360; i++)
//	{
//		for (j = 0; j < 640; j++)
//		{
//			yuv[0][i * 640 + j] = matrix[0][i * 1280 + j];
//			yuv[1][i * 640 + j] = matrix[1][i * 1280 + j];
//			yuv[2][i * 640 + j] = matrix[2][i * 1280 + j];
//		}
//	}
//
//	for (i = 0; i < 720; i++)
//	{
//		for (j = 0; j < 1280; j++)
//		{
//			matrix[0][i * 1280 + j] = 255;
//			matrix[1][i * 1280 + j] = 255;
//			matrix[2][i * 1280 + j] = 255;
//		}
//	}
//
//	bicubicInterpolation(yuv, matrix, 640.00, 360.00, 2.00);
//
//	int counter = 0;
//	for (i = 0; i < 720; i++)
//	{
//		for (j = 0; j < 1280; j = j + 2)
//		{
//			bufferOut[counter] = matrix[0][i * 1280 + j];
//			counter++;
//			bufferOut[counter] = matrix[1][i * 1280 + j];
//			counter++;
//			bufferOut[counter] = matrix[0][i * 1280 + j + 1];
//			counter++;
//			bufferOut[counter] = matrix[2][i * 1280 + j + 1];
//			counter++;
//		}
//	}
//
//	FILE* fp;
//	fp = fopen("C:\\Users\\kelava\\Desktop\\nnout.bin", "wb");
//	fwrite(bufferOut, 1, frameSize, fp);
//	fclose(fp);
//
//	return 0;
//}

//int main()
//{
//	uint32_t frameSize;
//	uint32_t frameCount;
//	uint32_t bufferSize = 0;
//
//	uint8_t* bufferIn;
//	uint8_t* bufferOut;
//
//	char* fileToOpen;
//	char* fileToWrite;
//
//	fileToOpen = "C:\\Users\\kelava\\Desktop\\Dummy5.bin";
//
//	frameSize = (1280 * 720 * 2); //YUV422 format
//
//	FILE* fp1 = fopen(fileToOpen, "rb");
//
//	allocateBuffer(&bufferIn, frameSize);
//	allocateBuffer(&bufferOut, frameSize);
//
//	fread(bufferIn, 1, frameSize, fp1);
//	fclose(fp1);
//
//	int ct = 0;
//	uint8_t q11;
//	uint8_t q12;
//	uint8_t q21;
//	uint8_t q22;
//
//	double iCordFloor;
//	double jCordFloor;
//	double iCordCeil;
//	double jCordCeil;
//
//	volatile int i, j;
//
//#pragma region yuv
//
//	uint8_t* y;
//	y = (uint8_t *)malloc(360*640 * sizeof(uint8_t*));
//	uint8_t** u;
//	u = (uint8_t *)malloc(360*640 * sizeof(uint8_t*));
//	uint8_t** v;
//	v = (uint8_t *)malloc(360*640 * sizeof(uint8_t*));
//
//	uint8_t* yuv[3];
//	yuv[0] = y;
//	yuv[1] = u;
//	yuv[2] = v;
//
//#pragma endregion
//
//#pragma region matrix
//
//	uint8_t* y1;
//	y1 = (uint8_t *)malloc(720*1280 * sizeof(uint8_t*));
//	uint8_t** u1;
//	u1 = (uint8_t *)malloc(720*1280 * sizeof(uint8_t*));
//	uint8_t* v1;
//	v1 = (uint8_t *)malloc(720*1280 * sizeof(uint8_t*));
//
//	uint8_t* matrix[3];
//	matrix[0] = y1;
//	matrix[1] = u1;
//	matrix[2] = v1;
//
//#pragma endregion
//	
//	int ct0 = 0, ct1 = 1, ct2 = 2, ct3 = 3;
//	for (i = 0; i < 720; i++)
//	{
//		for (j = 0; j < 1280; j = j + 2)
//		{
//			matrix[0][i * 1280 + j] = bufferIn[ct0];
//			matrix[1][i * 1280 + j] = bufferIn[ct1];
//			matrix[2][i * 1280 + j] = bufferIn[ct3];
//
//			matrix[0][i * 1280 + j + 1] = bufferIn[ct2];
//			matrix[1][i * 1280 + j + 1] = bufferIn[ct1];
//			matrix[2][i * 1280 + j + 1] = bufferIn[ct3];
//
//			ct0 = ct0 + 4;
//			ct1 = ct1 + 4;
//			ct2 = ct2 + 4;
//			ct3 = ct3 + 4;
//		}
//	}
//
//	for (i = 0; i < 360; i++)
//	{
//		for (j = 0; j < 640; j++)
//		{
//			yuv[0][i * 640 + j] = matrix[0][i * 1280 + j];
//			yuv[1][i * 640 + j] = matrix[1][i * 1280 + j];
//			yuv[2][i * 640 + j] = matrix[2][i * 1280 + j];
//		}
//	}
//
//	for (i = 0; i < 720; i++)
//	{
//		for (j = 0; j < 1280; j++)
//		{
//			double I = (double)i;
//			double J = (double)j;
//			double xScale = (640 * SF) / (640 - 1.00);
//			double yScale = (360 * SF) / (360 - 1.00);
//			double W = -(((I / yScale) - floor(I / yScale)) - 1);
//			double H = -(((J / xScale) - floor(J / xScale)) - 1);
//			double result;
//
//			iCordFloor = floor(I / yScale);
//			jCordFloor = floor(J / xScale);
//			iCordCeil = ceil(I / yScale);
//			jCordCeil = ceil(J / xScale);
//
//			q11 = yuv[0][(int)(iCordFloor * 640 + jCordFloor)];
//			q12 = yuv[0][(int)(iCordCeil * 640 + jCordFloor)];
//			q21 = yuv[0][(int)(iCordFloor * 640 + jCordCeil)];
//			q22 = yuv[0][(int)(iCordCeil * 640 + jCordCeil)];
//
//			result = ((1 - W) * (1 - H) * q22) + (W * (1 - H) * q21) + ((1 - W) * H * q12) + (W * H * q11);
//			matrix[0][i * 1280 + j] = (uint8_t)result;
//
//
//			q11 = yuv[1][(int)(iCordFloor * 640 + jCordFloor)];
//			q12 = yuv[1][(int)(iCordCeil * 640 + jCordFloor)];
//			q21 = yuv[1][(int)(iCordFloor * 640 + jCordCeil)];
//			q22 = yuv[1][(int)(iCordCeil * 640 + jCordCeil)];
//
//			result = ((1 - W) * (1 - H) * q22) + (W * (1 - H) * q21) + ((1 - W) * H * q12) + (W * H * q11);
//			matrix[1][i * 1280 + j] = (uint8_t)result;
//
//			q11 = yuv[2][(int)(iCordFloor * 640 + jCordFloor)];
//			q12 = yuv[2][(int)(iCordCeil * 640 + jCordFloor)];
//			q21 = yuv[2][(int)(iCordFloor * 640 + jCordCeil)];
//			q22 = yuv[2][(int)(iCordCeil * 640 + jCordCeil)];
//
//			result = ((1 - W) * (1 - H) * q22) + (W * (1 - H) * q21) + ((1 - W) * H * q12) + (W * H * q11);
//			matrix[2][i * 1280 + j] = (uint8_t)result;
//		}
//	}
//
//
//	int counter = 0;
//	for (i = 0; i < 720; i++)
//	{
//		for (j = 0; j < 1280; j = j + 2)
//		{
//			bufferOut[counter] = matrix[0][i * 1280 + j];
//			counter++;
//			bufferOut[counter] = matrix[1][i * 1280 + j];
//			counter++;
//			bufferOut[counter] = matrix[0][i * 1280 + j + 1];
//			counter++;
//			bufferOut[counter] = matrix[2][i * 1280 + j + 1];
//			counter++;
//		}
//	}
//
//	FILE* fp;
//	fp = fopen("C:\\Users\\kelava\\Desktop\\nnout.bin", "wb");
//	fwrite(bufferOut, 1, frameSize, fp);
//	fclose(fp);
//
//	return 0;
//}

/*NN enlarge*/
//int main()
//{
//	uint32_t frameSize;
//	uint32_t frameCount;
//	uint32_t bufferSize = 0;
//
//	uint8_t* bufferIn;
//	uint8_t* bufferOut;
//
//	char* fileToOpen;
//	char* fileToWrite;
//
//	fileToOpen = "C:\\Users\\kelava\\Desktop\\Dummy5.bin";
//
//	frameSize = (1280 * 720 * 2); //YUV422 format
//
//	FILE* fp1 = fopen(fileToOpen, "rb");
//
//	allocateBuffer(&bufferIn, frameSize);
//	allocateBuffer(&bufferOut, frameSize);
//
//	fread(bufferIn, 1, frameSize, fp1);
//	fclose(fp1);
//
//	int i, j;
//	int ct = 0;
//	int iCord;
//	int jCord;
//
//#pragma region yuv
//
//	uint8_t* y;
//	y = (uint8_t *)malloc(360*640 * sizeof(uint8_t*));
//	uint8_t** u;
//	u = (uint8_t *)malloc(360*640 * sizeof(uint8_t*));
//	uint8_t** v;
//	v = (uint8_t *)malloc(360*640 * sizeof(uint8_t*));
//
//	uint8_t* yuv[3];
//	yuv[0] = y;
//	yuv[1] = u;
//	yuv[2] = v;
//
//#pragma endregion
//
//#pragma region matrix
//
//	uint8_t* y1;
//	y1 = (uint8_t *)malloc(720*1280 * sizeof(uint8_t*));
//	uint8_t** u1;
//	u1 = (uint8_t *)malloc(720*1280 * sizeof(uint8_t*));
//	uint8_t* v1;
//	v1 = (uint8_t *)malloc(720*1280 * sizeof(uint8_t*));
//
//	uint8_t* matrix[3];
//	matrix[0] = y1;
//	matrix[1] = u1;
//	matrix[2] = v1;
//
//#pragma endregion
//	
//	int ct0 = 0, ct1 = 1, ct2 = 2, ct3 = 3;
//	for (i = 0; i < 720; i++)
//	{
//		for (j = 0; j < 1280; j = j + 2)
//		{
//			matrix[0][i * 1280 + j] = bufferIn[ct0];
//			matrix[1][i * 1280 + j] = bufferIn[ct1];
//			matrix[2][i * 1280 + j] = bufferIn[ct3];
//
//			matrix[0][i * 1280 + j + 1] = bufferIn[ct2];
//			matrix[1][i * 1280 + j + 1] = bufferIn[ct1];
//			matrix[2][i * 1280 + j + 1] = bufferIn[ct3];
//
//			ct0 = ct0 + 4;
//			ct1 = ct1 + 4;
//			ct2 = ct2 + 4;
//			ct3 = ct3 + 4;
//		}
//	}
//
//	for (i = 0; i < 360; i++)
//	{
//		for (j = 0; j < 640; j++)
//		{
//			yuv[0][i * 640 + j] = matrix[0][i * 1280 + j];
//			yuv[1][i * 640 + j] = matrix[1][i * 1280 + j];
//			yuv[2][i * 640 + j] = matrix[2][i * 1280 + j];
//		}
//	}
//
//	for (int i = 0; i < 720; i++)
//	{
//		for (int j = 0; j < 1280; j++)
//		{
//			iCord = (i / 2);
//			jCord = (j / 2);
//
//			matrix[0][i * 1280 + j] = yuv[0][iCord * 640 + jCord];
//			matrix[1][i * 1280 + j] = yuv[1][iCord * 640 + jCord];
//			matrix[2][i * 1280 + j] = yuv[2][iCord * 640 + jCord];
//		}
//	}
//
//	int counter = 0;
//	for (i = 0; i < 720; i++)
//	{
//		for (j = 0; j < 1280; j = j + 2)
//		{
//			bufferOut[counter] = matrix[0][i * 1280 + j];
//			counter++;
//			bufferOut[counter] = matrix[1][i * 1280 + j];
//			counter++;
//			bufferOut[counter] = matrix[0][i * 1280 + j + 1];
//			counter++;
//			bufferOut[counter] = matrix[2][i * 1280 + j + 1];
//			counter++;
//		}
//	}
//
//	FILE* fp;
//	fp = fopen("C:\\Users\\kelava\\Desktop\\nnout.bin", "wb");
//	fwrite(bufferOut, 1, frameSize, fp);
//	fclose(fp);
//
//	return 0;
//}

/*NN reduce*/
int main()
{
	int w = 1280;
	int h = 720;

	int inputWidth = 1280;
	int inputHeight = 720;
	double sf = 0.6;
	int32_t outputWidth = (int)((double)inputWidth * sf);
	int32_t outputHeight = (int)((double)inputHeight * sf);

	uint32_t frameSize;
	uint32_t frameCount;
	uint32_t bufferSize = 0;

	uint8_t* bufferIn;
	uint8_t* bufferOut;

	char* fileToOpen;
	char* fileToWrite;

	fileToOpen = "C:\\Users\\kelava\\Desktop\\output.bin";

	FILE* fp1 = fopen(fileToOpen, "rb");

	allocateBuffer(&bufferIn, w*h*2);
	allocateBuffer(&bufferOut, outputWidth * outputHeight*2);

	fread(bufferIn, 1, inputWidth*inputHeight, fp1);
	fclose(fp1);

	int i, j;
	int ct = 0;

#pragma region yuv

	uint8_t* y;
	y = (uint8_t *)malloc(inputWidth * inputHeight * sizeof(uint8_t*));
	uint8_t** u;
	u = (uint8_t *)malloc(inputWidth * inputHeight * sizeof(uint8_t*));
	uint8_t** v;
	v = (uint8_t *)malloc(inputWidth * inputHeight * sizeof(uint8_t*));

	uint8_t* yuv[3];
	yuv[0] = y;
	yuv[1] = u;
	yuv[2] = v;

#pragma endregion

#pragma region matrix

	uint8_t* y1;
	y1 = (uint8_t *)malloc(w*h* sizeof(uint8_t*));
	uint8_t** u1;
	u1 = (uint8_t *)malloc(w * h * sizeof(uint8_t*));
	uint8_t* v1;
	v1 = (uint8_t *)malloc(w * h * sizeof(uint8_t*));

	uint8_t* matrix[3];
	matrix[0] = y1;
	matrix[1] = u1;
	matrix[2] = v1;

#pragma endregion
	
	int ct0 = 0, ct1 = 1, ct2 = 2, ct3 = 3;
	for (i = 0; i < h; i++)
	{
		for (j = 0; j < w; j = j + 2)
		{
			matrix[0][i * w + j] = bufferIn[ct0];
			matrix[1][i * w + j] = bufferIn[ct1];
			matrix[2][i * w + j] = bufferIn[ct3];

			matrix[0][i * w + j + 1] = bufferIn[ct2];
			matrix[1][i * w + j + 1] = bufferIn[ct1];
			matrix[2][i * w + j + 1] = bufferIn[ct3];

			ct0 = ct0 + 4;
			ct1 = ct1 + 4;
			ct2 = ct2 + 4;
			ct3 = ct3 + 4;
		}
	}

	for (i = 0; i < inputHeight; i++)
	{
		for (j = 0; j < inputWidth; j++)
		{
			yuv[0][i * inputWidth + j] = matrix[0][i * w + j];
			yuv[1][i * inputWidth + j] = matrix[1][i * w + j];
			yuv[2][i * inputWidth + j] = matrix[2][i * w + j];
		}
	}



	int iCord = 0;
	int jCord = 0;
	double xScale = (inputWidth * sf) / (inputWidth - 1.00);
	double yScale = (inputHeight * sf) / (inputHeight - 1.00);
	for (int i = 0; i < outputHeight; i++)
	{
		for (int j = 0; j < outputWidth; j++)
		{
			iCord = (int)(round((double)i / yScale));
			jCord = (int)(round((double)j / xScale));

			matrix[0][i * outputWidth + j] = yuv[0][iCord * inputWidth + jCord];
			matrix[1][i * outputWidth + j] = yuv[1][iCord * inputWidth + jCord];
			matrix[2][i * outputWidth + j] = yuv[2][iCord * inputWidth + jCord];
		}
	}

	int counter = 0;
	for (i = 0; i < outputHeight; i++)
	{
		for (j = 0; j < outputWidth; j = j + 2)
		{
			bufferOut[counter] = matrix[0][i * outputWidth + j];
			counter++;
			bufferOut[counter] = matrix[1][i * outputWidth + j];
			counter++;
			bufferOut[counter] = matrix[0][i * outputWidth + j + 1];
			counter++;
			bufferOut[counter] = matrix[2][i * outputWidth + j + 1];
			counter++;
		}
	}

	FILE* fp;
	fp = fopen("C:\\Users\\kelava\\Desktop\\nnout.bin", "wb");
	fwrite(bufferOut, 1, outputWidth* outputHeight*2, fp);
	fclose(fp);

	return 0;
}

//int main()
//{
//	uint32_t frameSize;
//	uint32_t frameCount;
//	uint32_t bufferSize = 0;
//
//	uint8_t* bufferIn;
//	uint8_t* bufferOut;
//
//	char* fileToOpen;
//	char* fileToWrite;
//
//	fileToOpen = "C:\\Users\\kelava\\Desktop\\Dummy5.bin";
//
//	frameSize = (1280 * 720 * 2); //YUV422 format
//
//	FILE* fp1 = fopen(fileToOpen, "rb");
//
//	allocateBuffer(&bufferIn, frameSize);
//	allocateBuffer(&bufferOut, 640*360);
//
//	fread(bufferIn, 1, frameSize, fp1);
//	fclose(fp1);
//
//	int i;
//	int ct1, ct2;
//	int iCord;
//	int jCord;
//
//	int size = 1280 * 720 / 2;
//	int full = 1280 * 720;
//
//	uint8_t* component1;
//	uint8_t* component2;
//	uint8_t* interpolate;
//
//	allocateBuffer(&component1, size);
//	allocateBuffer(&component2, size);
//	allocateBuffer(&interpolate, full);
//
//	ct1 = 0;
//	ct2 = 0;
//	for (i = 0; i < full * 2; i = i + 4)
//	{
//		component1[ct1] = bufferIn[i];
//		component2[ct2] = bufferIn[i + 2];
//		ct1++;
//		ct2++;
//	}
//
//	ct1 = 0;
//	for (i = 0; i < full; i = i + 2)
//	{
//		interpolate[i] = component1[ct1];
//		interpolate[i + 1] = component2[ct1];
//		ct1++;
//	}
//
//	ct1 = 0;
//	for (i = 0; i < full; i++)
//	{
//		if (i % 640 == 0 && i != 0)
//			i = i + 640;
//
//		bufferOut[ct1] = interpolate[i];
//		ct1++;
//	}
//
//	FILE* fp;
//	fp = fopen("C:\\Users\\kelava\\Desktop\\nnout.bin", "wb");
//	fwrite(bufferOut, 1, 640 * 360 , fp);
//	fclose(fp);
//
//	return 0;
//}

//int main()
//{
//	uint32_t frameSize;
//	uint32_t frameCount;
//	uint32_t bufferSize = 0;
//
//	uint8_t* bufferIn;
//	uint8_t* bufferOut;
//
//	char* fileToOpen;
//	char* fileToWrite;
//
//	YUV** yuv;
//	allocateMatrix(&yuv, WIDTH, HEIGHT, 1.0);
//
//	fileToOpen = "C:\\Users\\kelava\\Desktop\\Dummy5.bin";
//
//	frameSize = (1280 * 720 * 2); //YUV422 format
//
//	FILE* fp1 = fopen(fileToOpen, "rb");
//
//	allocateBuffer(&bufferIn, frameSize);
//	allocateBuffer(&bufferOut, frameSize);
//
//	fread(bufferIn, 1, frameSize, fp1);
//	fclose(fp1);
//
//	YUV** input;
//	allocateMatrix(&input, 1280, 720, 1.0);
//
//	int ct0 = 0, ct1 = 1, ct2 = 2, ct3 = 3;
//	int i, j;
//	for (i = 0; i < 720; i++)
//	{
//		for (j = 0; j < 1280; j = j + 2)
//		{
//			input[i][j].y = bufferIn[ct0];
//			input[i][j].u = bufferIn[ct1];
//			input[i][j].v = bufferIn[ct3];
//
//			input[i][j + 1].y = bufferIn[ct2];
//			input[i][j + 1].u = bufferIn[ct1];
//			input[i][j + 1].v = bufferIn[ct3];
//
//			ct0 = ct0 + 4;
//			ct1 = ct1 + 4;
//			ct2 = ct2 + 4;
//			ct3 = ct3 + 4;
//		}
//	}
//
//	printf("ct0 %d ct1 %d ct2 %d ct3 %d\n", ct0, ct1, ct2, ct3);
//
//	for (i = 0; i < 360; i++)
//	{
//		for (j = 0; j < 640; j++)
//		{
//			yuv[i][j].y = input[i][j].y;
//			yuv[i][j].u = input[i][j].u;
//			yuv[i][j].v = input[i][j].v;
//		}
//	}
//
//	nearestNeighbourInterpolation(yuv, input, WIDTH, HEIGHT, 2.0);
//
//	int counter = 0;
//	for (i = 0; i < 720; i++)
//	{
//		for (j = 0; j < 1280; j = j + 2)
//		{
//			bufferOut[counter] = input[i][j].y;
//			counter++;
//			bufferOut[counter] = input[i][j].u;
//			counter++;
//			bufferOut[counter] = input[i][j + 1].y;
//			counter++;
//			bufferOut[counter] = input[i][j + 1].v;
//			counter++;
//		}
//	}
//
//	FILE* fp;
//	fp = fopen("C:\\Users\\kelava\\Desktop\\nnout.bin", "wb");
//	fwrite(bufferOut, 1, frameSize, fp);
//	fclose(fp);
//
//	return 0;
//}

//int main()
//{ /*from uyvy to yuyv*/
//	uint32_t frameSize;
//	uint32_t frameCount;
//	uint32_t bufferSize = 0;
//
//	uint8_t* bufferIn;
//	uint8_t* bufferOut;
//
//	char* fileToOpen;
//	char* fileToWrite;
//
//	fileToOpen = "C:\\Users\\kelava\\Desktop\\Dummy5.bin";
//
//	frameSize = (WIDTH * HEIGHT * 2); //YUV422 format
//
//	FILE * fp1 = fopen(fileToOpen, "rb");
//
//	allocateBuffer(&bufferIn, frameSize);
//	allocateBuffer(&bufferOut, frameSize);
//
//	fread(bufferIn, 1, frameSize, fp1);
//	fclose(fp1);
//
//	for (int i = 0; i < frameSize; i = i + 4)
//	{
//		bufferOut[i] = bufferIn[i + 1];
//		bufferOut[i + 1] = bufferIn[i];
//		bufferOut[i + 2] = bufferIn[i + 3];
//		bufferOut[i + 3] = bufferIn[i + 2];
//	}
//
//	FILE* fp;
//	fp = fopen("C:\\Users\\kelava\\Desktop\\nnout.bin", "wb");
//	fwrite(bufferOut, 1, frameSize, fp);
//	fclose(fp);
//
//	return 0;
//}

//int main()
//{
//	uint32_t frameSize;
//	uint32_t frameCount;
//	uint32_t bufferSize = 0;
//
//	uint8_t* bufferIn;
//	uint8_t* bufferOut;
//
//	char* fileToOpen;
//	char* fileToWrite;
//
//	YUV** yuv;
//	allocateMatrix(&yuv, WIDTH, HEIGHT, 1.0);
//
//	fileToOpen = "C:\\Users\\kelava\\Desktop\\Dummy5.bin";
//
//	frameSize = (1280 * 720 * 2); //YUV422 format
//	//frameCount = getFrameCount(fileToOpen, frameSize);
//
//	FILE* fp1 = fopen(fileToOpen, "rb");
//	
//	allocateBuffer(&bufferIn, frameSize);
//
//	fread(bufferIn, 1, frameSize, fp1);
//	fclose(fp1);
//
//	//int ct0 = 0, ct1 = 1, ct2 = 2, ct3 = 3;
//	//for (int i = 0; i < 360; i++)
//	//{
//	//	for (int j = 0; j < 640; j = j + 2)
//	//	{
//	//		//inputPtr[rowIdx * wordWidth + colIdx + 0] /= 3;
//	//		//inputPtr[rowIdx * wordWidth + colIdx + 2] /= 3;
//	//		yuv[i][j].y = bufferIn[ct0];
//	//		yuv[i][j].u = bufferIn[ct1];
//	//		yuv[i][j].v = bufferIn[ct3];
//
//	//		yuv[i][j+1].y = bufferIn[ct2];
//	//		yuv[i][j+1].u = bufferIn[ct1];
//	//		yuv[i][j+1].v = bufferIn[ct3];
//
//	//		ct0 = ct0 + 4;
//	//		ct1 = ct1 + 4;
//	//		ct2 = ct2 + 4;
//	//		ct3 = ct3 + 4;
//	//	}
//	//}
//	long long int counter = 0;
//	for (int i = 0; i < 360; i++)
//	{
//		printf("loop %d, counter %d\n", i, counter);
//		for (int j = 0; j < 640; j = j + 2)
//		{
//			yuv[i][j].y = bufferIn[counter];
//			yuv[i][j].u = bufferIn[counter + 1];
//			yuv[i][j].v = bufferIn[counter + 3];
//
//			yuv[i][j + 1].y = bufferIn[counter + 2];
//			yuv[i][j + 1].u = bufferIn[counter + 1];
//			yuv[i][j + 1].v = bufferIn[counter + 3];
//
//			counter = counter + 4;
//		}
//		counter = counter + 640;
//	}
//	printf("counter %lld\n", counter);
//	counter = 1843200;
//	printf("counter %lld\n", counter);
//
//	YUV** output;
//	allocateMatrix(&output, WIDTH, HEIGHT, 2.0);
//	nearestNeighbourInterpolation(yuv, output, WIDTH, HEIGHT, 2.0);
//
//	allocateBuffer(&bufferOut, WIDTH * 2.0 * HEIGHT * 2.0 * 2.0 * 2.0);
//
//	counter = 0;
//	int i, j;
//	for (i = 0; i < 720; i++)
//	{
//		for (j = 0; j < 1280; j = j + 2)
//		{
//			bufferOut[counter] = output[i][j].y;
//			counter++;
//			bufferOut[counter] = output[i][j].u;
//			counter++;
//			bufferOut[counter] = output[i][j + 1].y;
//			counter++;
//			bufferOut[counter] = output[i][j + 1].v;
//			counter++;
//		}
//	}
//
//	FILE* fp;
//	fp = fopen("C:\\Users\\kelava\\Desktop\\nnout.bin", "wb");
//	fwrite(bufferOut, 1, frameSize, fp);
//	fclose(fp);
//
//	return 0;
//}

//int main()
//{
//	YUV** yuv;
//
//	allocateMatrix(&yuv, 4.0, 4.0, 1.0);
//
//	yuv[0][0].y = 1;
//	yuv[0][1].y = 2;
//	yuv[0][2].y = 3;
//	yuv[0][3].y = 4;
//
//	yuv[1][0].y = 2;
//	yuv[1][1].y = 3;
//	yuv[1][2].y = 4;
//	yuv[1][3].y = 5;
//
//	yuv[2][0].y = 5;
//	yuv[2][1].y = 6;
//	yuv[2][2].y = 7;
//	yuv[2][3].y = 8;
//
//	yuv[3][0].y = 1;
//	yuv[3][1].y = 3;
//	yuv[3][2].y = 5;
//	yuv[3][3].y = 7;
//
//
//	for (int i=0;i<4;i++)
//		for (int j = 0; j < 4; j++)
//		{
//			yuv[i][j].u = 0;
//			yuv[i][j].v = 0;
//		}
//
//	YUV** res;
//	allocateMatrix(&res, 4.0, 4.0, 2.0);
//
//	//bilinearInterpolation(yuv, res, 4.0, 4.0, 2.0);
//	bicubicInterpolation(yuv, res, 4.0, 4.0, 2.0);
//
//	return 0;
//}

//int main() /*original slika iz 422 -> 444*/
//{
//	double SCALE_FACTOR = ROUND1DEC(SF);
//
//	FILE* fp1;
//	FILE* fp2;
//	uint8_t* bufferIn;
//	//uint8_t* bufferYUYV;
//	uint8_t* bufferOut;
//
//	uint8_t* y1;
//	uint8_t* y2;
//	uint8_t* u;
//	uint8_t* v;
//
//	uint32_t frameSize;
//	uint32_t frameCount;
//	uint32_t bufferSize = 0;
//
//	char* fileToOpen;
//	char* fileToWrite;
//
//	YUV* yuv;
//
//	fileToOpen = "C:\\Users\\kelava\\Desktop\\Dummy5.bin";
//
//	fileToWrite = "C:\\Users\\kelava\\Desktop\\Dummy5_YUV444.bin";
//
//	frameSize = (WIDTH * HEIGHT * 2); //YUV422 format
//	bufferSize = (WIDTH * HEIGHT / 2);
//	//frameCount = getFrameCount(fileToOpen, frameSize);
//
//	fp1 = fopen(fileToOpen, "rb");
//	fp2 = fopen(fileToWrite, "wb");
//
//	allocateBuffer(&bufferIn, frameSize);
//
//	fread(bufferIn, 1, frameSize, fp1);
//	fclose(fp1);
//
//	allocateBuffer(&y1, bufferSize);
//	allocateBuffer(&y2, bufferSize);
//	allocateBuffer(&u, bufferSize);
//	allocateBuffer(&v, bufferSize);
//
//	fillBuffer(bufferIn, frameSize, y1, 0);
//	fillBuffer(bufferIn, frameSize, y2, 2);
//	fillBuffer(bufferIn, frameSize, u, 1);
//	fillBuffer(bufferIn, frameSize, v, 3);
//
//	allocateMatrix(&yuv, WIDTH, HEIGHT, 1);
//	fillMatrix(yuv, y1, y2, u, v, WIDTH, HEIGHT);
//
//	uint8_t* output;
//	allocateBuffer(&output, WIDTH * HEIGHT * 3);
//
//	createMess(yuv, output, WIDTH, HEIGHT);
//
//	fwrite(output, 1, WIDTH * HEIGHT * 3, fp2);
//	fclose(fp2);
//
//	deallocateBuffer(y1);
//	deallocateBuffer(y2);
//	deallocateBuffer(u);
//	deallocateBuffer(v);
//
//
//	printf("Hello World! PROGRAM ENDED!\n");
//
//	return 0;
//}

 /*difference*/
//int main()
//{
//	double SCALE_FACTOR = ROUND1DEC(SF);
//
//	FILE* fp1;
//	FILE* fp2;
//	uint8_t* bufferIn1;
//	uint8_t* bufferIn2;
//	//uint8_t* bufferYUYV;
//	uint8_t* bufferOut;
//
//	int width = (int)(WIDTH * SCALE_FACTOR);
//	int height = (int)(HEIGHT * SCALE_FACTOR);
//	int bang = width * height;
//
//	uint32_t size = width * height * 2;
//
//	char* fileToOpen1 = "C:\\Users\\kelava\\Desktop\\nnout.bin";
//	char* fileToOpen2 = "C:\\Users\\kelava\\Desktop\\output.bin";
//	char* fileToWrite = "C:\\Users\\kelava\\Desktop\\diff2.bin";
//
//	fp1 = fopen(fileToOpen1, "rb");
//	fp2 = fopen(fileToOpen2, "rb");
//
//	allocateBuffer(&bufferIn1, size);
//	allocateBuffer(&bufferIn2, size);
//	allocateBuffer(&bufferOut, size);
//
//	fread(bufferIn1, 1, size, fp1);
//	fread(bufferIn2, 1, size, fp2);
//
//	fclose(fp1);
//	fclose(fp2);
//
//	uint8_t* output;
//	allocateBuffer(&output, size);
//
//	for (int i = 0; i < size; i++)
//	{
//		//printf("%d %d\n", bufferIn1[i], bufferIn2[i]);
//		output[i] = bufferIn1[i] - bufferIn2[i];
//		clip(output[i]);
//	}
//
//	/*writing diff between all pixels*/
//	fp1 = fopen(fileToWrite, "wb");
//
//	fwrite(output, 1, 1280 * 720 * 2, fp1);
//
//	fclose(fp1);
//
//	/*only Y*/
//	//uint8_t* y;
//	//allocateBuffer(&y, bang);
//
//	//int counter = 0;
//	//for (int i = 0; i < bang; i++)
//	//{
//	//	y[i] = output[counter];
//	//	counter = counter + 2;
//	//}
//
//	//fp1 = fopen(fileToWrite, "wb");
//
//	//fwrite(y, 1, bang, fp1);
//
//	//fclose(fp1);
//
//	return 0;
//}

//int main() /*pretvaranje originalne slike iz 422 u 444*/
//{
//	double SCALE_FACTOR = ROUND1DEC(SF);
//
//	FILE* fp1;
//	FILE* fp2;
//	uint8_t* bufferIn;
//	uint8_t* bufferYUYV;
//	uint8_t* bufferOut;
//
//	uint8_t* y1;
//	uint8_t* y2;
//	uint8_t* u;
//	uint8_t* v;
//
//	uint32_t frameSize;
//	uint32_t frameCount;
//	uint32_t bufferSize = 0;
//
//	char* fileToOpen;
//	char* fileToWrite;
//	char* fileToWrite2;
//	char* fileToWrite3;
//	char* fileToWrite4;
//
//	YUV** yuv;
//	YUV** yuvOutput;
//	YUV** yuvOutput2;
//	YUV** yuvOutput3;
//
//	YUV* yuvArray;
//
//	fileToOpen = "C:\\Users\\kelava\\Desktop\\Dummy5_LINEAR_YUYV444.bin";
//	fileToWrite = "C:\\Users\\kelava\\Desktop\\Dummy5_BILINEAR_YUYV222_pyhoutOutput.bin";
//
//	frameSize = (WIDTH * HEIGHT * 2 * SF); //YUV422 format
//	bufferSize = (WIDTH * HEIGHT / 2);
//	frameCount = getFrameCount(fileToOpen, frameSize);
//
//	fp1 = fopen(fileToOpen, "rb");
//	fp2 = fopen(fileToWrite, "wb");
//
//	int width = (int)(WIDTH * SCALE_FACTOR);
//	int height = (int)(HEIGHT * SCALE_FACTOR);
//
//	allocateBuffer(&bufferIn, 1280 * 720 * 3);
//	allocateBuffer(&bufferYUYV, frameSize);
//	createYUYV(bufferIn, bufferYUYV, WIDTH, HEIGHT);
//
//	bufferIn = getFrameFromVideo(fileToOpen, frameSize, 36);
//	fread(bufferIn, 1, width*height * 3, fp1);
//
//	uint8_t* output;
//	allocateBuffer(&output, width * height * 2);
//
//	int counter = 0;
//	for (int i = 0; i < width * height *2; i = i + 4)
//	{
//		output[i] = bufferIn[counter];
//		output[i + 1] = bufferIn[counter + 1];
//		output[i + 2] = bufferIn[counter + 3];
//		output[i + 3] = bufferIn[counter + 5];
//		counter = counter + 6;
//	}
//
//	fp2 = fopen(fileToWrite, "wb");
//	fwrite(output, 1, width * height * 2, fp2);
//	fclose(fp2);
//
//	deallocateBuffer(bufferIn);
//	deallocateBuffer(output);
//
//	printf("Hello World! PROGRAM ENDED!\n");
//
//	return 0;
//}

//int main()
//{
//	double SCALE_FACTOR = SF;
//
//	FILE* fp1;
//	FILE* fp2;
//	uint8_t* bufferIn;
//	//uint8_t* bufferYUYV;
//	uint8_t* bufferOut;
//
//	uint8_t* y1;
//	uint8_t* y2;
//	uint8_t* u;
//	uint8_t* v;
//
//	uint32_t frameSize;
//	uint32_t frameCount;
//	uint32_t bufferSize = 0;
//
//	char* fileToOpen;
//	char* fileToWrite;
//	char* fileToWrite2;
//	char* fileToWrite3;
//	//char* fileToWrite4;
//
//	YUV** yuv;
//	YUV** yuvOutput;
//	YUV** yuvOutput2;
//	YUV** yuvOutput3;
//	//YUV** yuvOutput4;
//
//	YUV* yuvArray;
//
//	//fileToOpen = "C:\\Users\\kelava\\Desktop\\Frame4.bin";
//	fileToOpen = "C:\\Users\\kelava\\Desktop\\Dummy5.bin";
//	//fileToOpen = "C:\\Users\\kelava\\Desktop\\dummy1.bin";
//	//fileToOpen = "C:\\Users\\Kelava\\Desktop\\Dummy2.bin";
//	//fileToOpen = "C:\\Users\\Kelava\\Desktop\\video.bin";
//	fileToWrite = "C:\\Users\\kelava\\Desktop\\ftv_nearest.bin";
//	fileToWrite2 = "C:\\Users\\kelava\\Desktop\\ftv2_bilinear.bin";
//	fileToWrite3 = "C:\\Users\\kelava\\Desktop\\ftv3_bicubic.bin";
//	//fileToWrite4 = "C:\\Users\\kelava\\Desktop\\ftv4_diff.bin";
//
//	frameSize = (WIDTH * HEIGHT * 2); //YUV422 format
//	bufferSize = (WIDTH * HEIGHT / 2);
//	//frameCount = getFrameCount(fileToOpen, frameSize);
//
//	fp1 = fopen(fileToOpen, "rb");
//	fp2 = fopen(fileToWrite, "wb");
//
//	allocateBuffer(&bufferIn, frameSize);
//	//allocateBuffer(&bufferYUYV, frameSize);
//	//createYUYV(bufferIn, bufferYUYV, WIDTH, HEIGHT);
//
//	//bufferIn = getFrameFromVideo(fileToOpen, frameSize, 36);
//	fread(bufferIn, 1, frameSize, fp1);
//
//	allocateBuffer(&y1, bufferSize);
//	allocateBuffer(&y2, bufferSize);
//	allocateBuffer(&u, bufferSize);
//	allocateBuffer(&v, bufferSize);
//
//	fillBuffer(bufferIn, frameSize, y1, 0);
//	fillBuffer(bufferIn, frameSize, y2, 2);
//	fillBuffer(bufferIn, frameSize, u, 1);
//	fillBuffer(bufferIn, frameSize, v, 3);
//
//	allocateMatrix(&yuv, WIDTH, HEIGHT, 1);
//	fillMatrix(yuv, y1, y2, u, v, WIDTH, HEIGHT);
//
//	allocateMatrix(&yuvOutput, WIDTH, HEIGHT, SCALE_FACTOR);
//	allocateMatrix(&yuvOutput2, WIDTH, HEIGHT, SCALE_FACTOR);
//	allocateMatrix(&yuvOutput3, WIDTH, HEIGHT, SCALE_FACTOR);
//
//	nearestNeighbourInterpolation(yuv, yuvOutput, WIDTH, HEIGHT, SCALE_FACTOR);
//	printf("NEAREST OK\n");
//
//	bilinearInterpolation(yuv, yuvOutput2, WIDTH, HEIGHT, SCALE_FACTOR);
//	printf("BILINEAR OK \n");
//
//	bicubicInterpolation(yuv, yuvOutput3, WIDTH, HEIGHT, SCALE_FACTOR);
//	printf("BICUBIC OK\n");
//
//	allocateYUVBuffer(&yuvArray, WIDTH * HEIGHT * SCALE_FACTOR * SCALE_FACTOR);
//	fillYUVBuffer(yuvArray, yuvOutput, WIDTH * SCALE_FACTOR, HEIGHT * SCALE_FACTOR);
//
//	allocateBuffer(&bufferOut, frameSize * SCALE_FACTOR * SCALE_FACTOR);
//	createOutput(bufferOut, yuvArray, frameSize * SCALE_FACTOR * SCALE_FACTOR);
//
//	/*creating new image data*/
//	//fwrite(bufferOut, 1, frameSize, fp2);
//	fwrite(bufferOut, 1, frameSize * SCALE_FACTOR * SCALE_FACTOR, fp2);
//	fclose(fp1);
//	fclose(fp2);
//
//	fillYUVBuffer(yuvArray, yuvOutput2, WIDTH * SCALE_FACTOR, HEIGHT * SCALE_FACTOR);
//	createOutput(bufferOut, yuvArray, frameSize * SCALE_FACTOR * SCALE_FACTOR);
//
//	fp2 = fopen(fileToWrite2, "wb");
//	fwrite(bufferOut, 1, frameSize * SCALE_FACTOR * SCALE_FACTOR, fp2);
//	fclose(fp2);
//
//	fillYUVBuffer(yuvArray, yuvOutput3, WIDTH * SCALE_FACTOR, HEIGHT * SCALE_FACTOR);
//	createOutput(bufferOut, yuvArray, frameSize * SCALE_FACTOR * SCALE_FACTOR);
//
//	fp2 = fopen(fileToWrite3, "wb");
//	fwrite(bufferOut, 1, frameSize * SCALE_FACTOR * SCALE_FACTOR, fp2);
//	fclose(fp2);
//
//	//fp2 = fopen(fileToWrite2, "wb");
//	//fwrite(bufferIn, 1, frameSize, fp2);
//	//fclose(fp2);
//
//	deallocateMatrix(yuv, HEIGHT);
//
//	deallocateMatrix(yuvOutput, HEIGHT * SCALE_FACTOR);
//	deallocateMatrix(yuvOutput2, HEIGHT * SCALE_FACTOR);
//	deallocateMatrix(yuvOutput3, HEIGHT * SCALE_FACTOR);
//
//	deallocateBuffer(y1);
//	deallocateBuffer(y2);
//	deallocateBuffer(u);
//	deallocateBuffer(v);
//
//
//	printf("Hello World! PROGRAM ENDED!\n");
//
//	return 0;
//}

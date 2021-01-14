#include "yuv.h"

#define WIDTH 640 //row
#define HEIGHT 360 //column
#define SF 2

int main()
{
	double SCALE_FACTOR = ROUND1DEC(SF);

	FILE* fp1;
	FILE* fp2;
	uint8_t* bufferIn;
	//uint8_t* bufferYUYV;
	uint8_t* bufferOut;

	uint8_t* y1;
	uint8_t* y2;
	uint8_t* u;
	uint8_t* v;

	uint32_t frameSize;
	uint32_t frameCount;
	uint32_t bufferSize = 0;

	char* fileToOpen;
	char* fileToWrite;
	char* fileToWrite2;
	char* fileToWrite3;
	char* fileToWrite4;

	YUV** yuv;
	YUV** yuvOutput;
	YUV** yuvOutput2;
	YUV** yuvOutput3;
	YUV** yuvOutput4;

	YUV* yuvArray;

	fileToOpen = "C:\\Users\\kelava\\Desktop\\Dummy5.bin";
	//fileToOpen = "C:\\Users\\kelava\\Desktop\\dummy1.bin";
	//fileToOpen = "C:\\Users\\Kelava\\Desktop\\Dummy2.bin";
	//fileToOpen = "C:\\Users\\Kelava\\Desktop\\video.bin";
	fileToWrite = "C:\\Users\\kelava\\Desktop\\ftv_nearest.bin";
	fileToWrite2 = "C:\\Users\\kelava\\Desktop\\ftv3_bilinear.bin";
	fileToWrite3 = "C:\\Users\\kelava\\Desktop\\ftv2_bicubic.bin";
	fileToWrite4 = "C:\\Users\\kelava\\Desktop\\ftv4_diff.bin";

	frameSize = (WIDTH * HEIGHT * 2); //YUV422 format
	bufferSize = (WIDTH * HEIGHT / 2);
	//frameCount = getFrameCount(fileToOpen, frameSize);

	fp1 = fopen(fileToOpen, "rb");
	fp2 = fopen(fileToWrite, "wb");

	allocateBuffer(&bufferIn, frameSize);
	//allocateBuffer(&bufferYUYV, frameSize);
	//createYUYV(bufferIn, bufferYUYV, WIDTH, HEIGHT);

	//bufferIn = getFrameFromVideo(fileToOpen, frameSize, 36);
	fread(bufferIn, 1, frameSize, fp1);

	allocateBuffer(&y1, bufferSize);
	allocateBuffer(&y2, bufferSize);
	allocateBuffer(&u, bufferSize);
	allocateBuffer(&v, bufferSize);

	fillBuffer(bufferIn, frameSize, y1, 0);
	fillBuffer(bufferIn, frameSize, y2, 2);
	fillBuffer(bufferIn, frameSize, u, 1);
	fillBuffer(bufferIn, frameSize, v, 3);

	allocateMatrix(&yuv, WIDTH, HEIGHT, 1);
	fillMatrix(yuv, y1, y2, u, v, WIDTH, HEIGHT);

	allocateMatrix(&yuvOutput, WIDTH, HEIGHT, SCALE_FACTOR);
	allocateMatrix(&yuvOutput2, WIDTH, HEIGHT, SCALE_FACTOR);
	allocateMatrix(&yuvOutput3, WIDTH, HEIGHT, SCALE_FACTOR);
	allocateMatrix(&yuvOutput4, WIDTH, HEIGHT, SCALE_FACTOR);

	nearestNeighbourInterpolation(yuv, yuvOutput, WIDTH, HEIGHT, SCALE_FACTOR);
	printf("NEAREST OK\n");

	bilinearInterpolation(yuv, yuvOutput2, WIDTH, HEIGHT, SCALE_FACTOR);
	printf("BILINEAR OK \n");

	bicubicInterpolation(yuv, yuvOutput3, WIDTH, HEIGHT, SCALE_FACTOR);
	printf("BICUBIC OK\n");

	allocateYUVBuffer(&yuvArray, WIDTH * HEIGHT * SCALE_FACTOR * SCALE_FACTOR);
	fillYUVBuffer(yuvArray, yuvOutput, WIDTH * SCALE_FACTOR, HEIGHT * SCALE_FACTOR);

	allocateBuffer(&bufferOut, frameSize * SCALE_FACTOR * SCALE_FACTOR);
	createOutput(bufferOut, yuvArray, frameSize * SCALE_FACTOR * SCALE_FACTOR);

	/*creating new image data*/
	//fwrite(bufferOut, 1, frameSize, fp2);
	fwrite(bufferOut, 1, frameSize * SCALE_FACTOR * SCALE_FACTOR, fp2);
	fclose(fp1);
	fclose(fp2);

	fillYUVBuffer(yuvArray, yuvOutput2, WIDTH * SCALE_FACTOR, HEIGHT * SCALE_FACTOR);
	createOutput(bufferOut, yuvArray, frameSize * SCALE_FACTOR * SCALE_FACTOR);

	fp2 = fopen(fileToWrite2, "wb");
	fwrite(bufferOut, 1, frameSize * SCALE_FACTOR * SCALE_FACTOR, fp2);
	fclose(fp2);

	fillYUVBuffer(yuvArray, yuvOutput3, WIDTH * SCALE_FACTOR, HEIGHT * SCALE_FACTOR);
	createOutput(bufferOut, yuvArray, frameSize * SCALE_FACTOR * SCALE_FACTOR);

	fp2 = fopen(fileToWrite3, "wb");
	fwrite(bufferOut, 1, frameSize * SCALE_FACTOR * SCALE_FACTOR, fp2);
	fclose(fp2);

	for (int i = 0; i < HEIGHT * SCALE_FACTOR; i++)
	{
		for (int j = 0; j < WIDTH * SCALE_FACTOR; j++)
		{
			yuvOutput4[i][j].y = yuvOutput3[i][j].y - yuvOutput[i][j].y;
			yuvOutput4[i][j].u = yuvOutput3[i][j].u - yuvOutput[i][j].u;
			yuvOutput4[i][j].v = yuvOutput3[i][j].v - yuvOutput[i][j].v;
		}
	}

	fillYUVBuffer(yuvArray, yuvOutput4, WIDTH * SCALE_FACTOR, HEIGHT * SCALE_FACTOR);
	createOutput(bufferOut, yuvArray, frameSize * SCALE_FACTOR * SCALE_FACTOR);

	fp2 = fopen(fileToWrite4, "wb");
	fwrite(bufferOut, 1, (int)frameSize * SCALE_FACTOR * SCALE_FACTOR, fp2);
	fclose(fp2);


	//fp2 = fopen(fileToWrite2, "wb");
	//fwrite(bufferIn, 1, frameSize, fp2);
	//fclose(fp2);

	deallocateMatrix(yuv, HEIGHT);

	deallocateMatrix(yuvOutput, HEIGHT * SCALE_FACTOR);
	deallocateMatrix(yuvOutput2, HEIGHT * SCALE_FACTOR);
	deallocateMatrix(yuvOutput3, HEIGHT * SCALE_FACTOR);

	deallocateBuffer(y1);
	deallocateBuffer(y2);
	deallocateBuffer(u);
	deallocateBuffer(v);


	printf("Hello World! PROGRAM ENDED!\n");

	return 0;
}

//int main()
//{
//	YUV** mat;
//	YUV** output;
//
//	allocateMatrix(&mat, 4, 4, 1);
//	allocateMatrix(&output, 4, 4, 2);
//
//	mat[0][0].y = 1;
//	mat[0][1].y = 2;
//	mat[0][2].y = 3;
//	mat[0][3].y = 4;
//	mat[1][0].y = 3;
//	mat[1][1].y = 4;
//	mat[1][2].y = 5;
//	mat[1][3].y = 6;
//	mat[2][0].y = 6;
//	mat[2][1].y = 7;
//	mat[2][2].y = 8;
//	mat[2][3].y = 9;
//	mat[3][0].y = 2;
//	mat[3][1].y = 4;
//	mat[3][2].y = 6;
//	mat[3][3].y = 8;
//
//	mat[0][0].u = 0;
//	mat[0][1].u = 0;
//	mat[0][2].u = 0;
//	mat[0][3].u = 0;
//	mat[1][0].u = 0;
//	mat[1][1].u = 0;
//	mat[1][2].u = 0;
//	mat[1][3].u = 0;
//	mat[2][0].u = 0;
//	mat[2][1].u = 0;
//	mat[2][2].u = 0;
//	mat[2][3].u = 0;
//	mat[3][0].u = 0;
//	mat[3][1].u = 0;
//	mat[3][2].u = 0;
//	mat[3][3].u = 0;
//
//	mat[0][0].v = 0;
//	mat[0][1].v = 0;
//	mat[0][2].v = 0;
//	mat[0][3].v = 0;
//	mat[1][0].v = 0;
//	mat[1][1].v = 0;
//	mat[1][2].v = 0;
//	mat[1][3].v = 0;
//	mat[2][0].v = 0;
//	mat[2][1].v = 0;
//	mat[2][2].v = 0;
//	mat[2][3].v = 0;
//	mat[3][0].v = 0;
//	mat[3][1].v = 0;
//	mat[3][2].v = 0;
//	mat[3][3].v = 0;
//
//	bicubicInterpolation(mat, output, 4, 4, 2);
//
//	printf("MATRIX\n");
//	for (int i = 0; i < 8; i++)
//	{
//		for (int j = 0; j < 8; j++)
//		{
//			printf("%d ", output[i][j].y);
//		}
//		printf("\n");
//	}
//
//	return 0;
//}

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
//	uint32_t size = 1280 * 720 * 2;
//
//	char* fileToOpen1 = "C:\\Users\\kelava\\Desktop\\ftv_nearest.bin";
//	char* fileToOpen2 = "C:\\Users\\kelava\\Desktop\\pynearestYUYV.bin";
//	char* fileToWrite = "C:\\Users\\kelava\\Desktop\\diffnearestYUYV.bin";
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
//	}
//
//	fp1 = fopen(fileToWrite, "wb");
//
//	fwrite(output, 1, 1280 * 720 * 2, fp1);
//
//	fclose(fp1);
//
//	return 0;
//}

//int main()
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
//	char* fileToOpen = "C:\\Users\\kelava\\Desktop\\pyoutcubic.bin";
//	char* fileToWrite = "C:\\Users\\kelava\\Desktop\\pybicubicYUYV.bin";
//
//	YUV** yuv;
//
//	frameSize = (1280*720 * 3); //YUV422 format
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
//	fclose(fp1);
//
//	uint8_t* output;
//	allocateBuffer(&output, 1280 * 720 * 2);
//
//	int counter = 0;
//	for (int i = 0; i < 1280 * 720 * 2; i=i+4)
//	{
//		//printf("%d %d\n", i, counter);
//		output[i] = bufferIn[counter];
//		output[i + 1] = bufferIn[counter + 1];
//		output[i + 2] = bufferIn[counter + 3];
//		output[i + 3] = bufferIn[counter + 5];
//		counter = counter + 6;
//	}
//
//	fwrite(output, 1, 1280 * 720 * 2, fp2);
//	fclose(fp2);
//
//	//allocateBuffer(&y1, bufferSize);
//	//allocateBuffer(&y2, bufferSize);
//	//allocateBuffer(&u, bufferSize);
//	//allocateBuffer(&v, bufferSize);
//
//	//fillBuffer(bufferIn, frameSize, y1, 0);
//	//fillBuffer(bufferIn, frameSize, y2, 2);
//	//fillBuffer(bufferIn, frameSize, u, 1);
//	//fillBuffer(bufferIn, frameSize, v, 3);
//
//	//allocateMatrix(&yuv, WIDTH, HEIGHT, 1);
//	//fillMatrix(yuv, y1, y2, u, v, WIDTH, HEIGHT);
//
//	//uint8_t* output;
//	//allocateBuffer(&output, WIDTH * HEIGHT * 3);
//	//createMess(yuv, output, WIDTH, HEIGHT);
//
//	//fp2 = fopen("C:\\Users\\kelava\\Desktop\\yuv444.bin", "wb");
//	////	fwrite(bufferOut, 1, frameSize * SCALE_FACTOR * SCALE_FACTOR, fp2);
//	//fwrite(output, 1, WIDTH * HEIGHT * 3, fp2);
//	//fclose(fp2);
//
//	//deallocateMatrix(yuv, HEIGHT);
//
//	//deallocateBuffer(y1);
//	//deallocateBuffer(y2);
//	//deallocateBuffer(u);
//	//deallocateBuffer(v);
//
//
//	//printf("Hello World! PROGRAM ENDED!\n");
//
//	//return 0;
//}
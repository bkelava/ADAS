#include "yuv.h"

#define WIDTH 640 //row
#define HEIGHT 360 //column
#define SF 2

int main()
{
	YUV** yuv;

	allocateMatrix(&yuv, 4.0, 4.0, 1.0);

	yuv[0][0].y = 1;
	yuv[0][1].y = 2;
	yuv[0][2].y = 3;
	yuv[0][3].y = 4;
	yuv[1][0].y = 2;
	yuv[1][1].y = 3;
	yuv[1][2].y = 4;
	yuv[1][3].y = 5;
	yuv[2][0].y = 5;
	yuv[2][1].y = 6;
	yuv[2][2].y = 7;
	yuv[2][3].y = 8;
	yuv[3][0].y = 1;
	yuv[3][1].y = 3;
	yuv[3][2].y = 5;
	yuv[3][3].y = 7;


	for (int i=0;i<4;i++)
		for (int j = 0; j < 4; j++)
		{
			yuv[i][j].u = 0;
			yuv[i][j].v = 0;
		}

	YUV** res;
	allocateMatrix(&res, 4.0, 4.0, 2.0);

	bilinearInterpolation(yuv, res, 4.0, 4.0, 2.0);
	//bicubicInterpolation(yuv, res, 4.0, 4.0, 2.0);

	return 0;
}

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
//	char* fileToOpen1 = "C:\\Users\\kelava\\Desktop\\ftv2_bilinear.bin";
//	char* fileToOpen2 = "C:\\Users\\kelava\\Desktop\\Dummy5_BILINEAR_YUYV222_pyhoutOutput.bin";
//	char* fileToWrite = "C:\\Users\\kelava\\Desktop\\Dummy5_DIFF_BILINEAR_Y.bin";
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
//	//bicubicInterpolation(yuv, yuvOutput3, WIDTH, HEIGHT, SCALE_FACTOR);
//	//printf("BICUBIC OK\n");
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

#include "yuv.h"

int getFrameCount(char* filename, int frame_size) {
	FILE* fp = fopen(filename, "r");
	fseek(fp, 0, SEEK_END);
	int file_size = ftell(fp);
	int frame_count = (int)(file_size / frame_size);
	fclose(fp);
	return frame_count;
}

void allocateMatrix(YUV * **matrix, double WIDTH, double HEIGHT, double FACTOR)
{
	int height_new = (int)(HEIGHT * FACTOR);
	int width_new = (int)(WIDTH * FACTOR);

	printf("allocating matrix uint8 type %d %d\n", height_new, width_new);

	*matrix = (YUV * *)malloc(sizeof(YUV*) * height_new);
	for (int i = 0; i < height_new; i++)
	{
		*(*matrix + i) = (YUV*)malloc(sizeof(YUV) * width_new);
	}
}

void allocateMatrixTypeDouble(YUV_Double * **matrix, double WIDTH, double HEIGHT, double FACTOR)
{
	int height_new = (int)(HEIGHT * FACTOR);
	int width_new = (int)(WIDTH * FACTOR);

	printf("allocating matrix double type %d %d\n", height_new, width_new);

	*matrix = (YUV_Double * *)malloc(sizeof(YUV_Double*) * height_new);
	for (int i = 0; i < height_new; i++)
	{
		*(*matrix + i) = (YUV_Double*)malloc(sizeof(YUV_Double) * width_new);
	}
}

void deallocateMatrix(YUV * *matrix, double HEIGHT) {
	int height = (int)HEIGHT;
	for (int i = 0; i < height; i++) {
		free(matrix[i]);
	}
	free(matrix);
}

void deallocateMatrixTypeDouble(YUV_Double * *matrix, double HEIGHT) {
	int height = (int)HEIGHT;
	for (int i = 0; i < height; i++) {
		free(matrix[i]);
	}
	free(matrix);
}

void allocateBuffer(uint8_t * *data, double SIZE)
{
	int size = (int)SIZE;
	uint8_t* p;
	p = malloc(size * sizeof(uint8_t));
	*data = p;
}

void deallocateBuffer(uint8_t * data)
{
	free(data);
}

void allocateYUVBuffer(YUV * *data, double SIZE)
{
	int size = (int)SIZE;
	YUV* p;
	p = malloc(size * sizeof(YUV));
	*data = p;
}

void deallocateYUVBuffer(YUV * data)
{
	free(data);
}

void fillBuffer(uint8_t * data, double DATASIZE, uint8_t * buffer, double START)
{
	int start = (int)START;
	int dataSize = (int)DATASIZE;
	int counter = 0;
	for (int i = start; i < dataSize; i = i + 4)
	{
		buffer[counter] = data[i];
		counter++;
	}
}

void createYUYV(uint8_t * input, uint8_t * output, double WIDTH, double HEIGHT)
{
	int width = (int)WIDTH;
	int height = (int)HEIGHT;
	for (int i = 0; i < height * width * 2; i = i + 4)
	{
		output[i] = input[i + 1];
		output[i + 1] = input[i];
		output[i + 2] = input[i + 3];
		output[i + 3] = input[i + 2];
	}
}

void fillMatrix(YUV * *yuv, uint8_t * y1, uint8_t * y2, uint8_t * u, uint8_t * v, double WIDTH, double HEIGHT)
{
	int width = (int)WIDTH;
	int height = (int)HEIGHT;
	int m = 0;
	int n = 0;
	int o = 0;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j = j + 2)
		{
			yuv[i][j].y = y1[m];
			m++;
			yuv[i][j].u = u[n];
			yuv[i][j].v = v[n];
			yuv[i][j + 1].y = y2[o];
			o++;
			yuv[i][j + 1].u = u[n];
			yuv[i][j + 1].v = v[n];
			n++;
		}
	}
}

void createMess(YUV** matrix, uint8_t* output, int width, int height)
{
	int counter = 0;

	YUV* buffer;
	allocateYUVBuffer(&buffer, width * height);
	fillYUVBuffer(buffer, matrix, width, height);

	for (int i = 0; i < height*width*3; i=i+3)
	{
		output[i] = buffer[counter].y;
		output[i + 1] = buffer[counter].u;
		output[i + 2] = buffer[counter].v;

		counter++;
	}
}

void fillYUVBuffer(YUV * yuvArray, YUV * *yuv, double WIDTH, double HEIGHT)
{
	int width = (int)WIDTH;
	int height = (int)HEIGHT;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			yuvArray[i * width + j].y = yuv[i][j].y;
			yuvArray[i * width + j].u = yuv[i][j].u;;
			yuvArray[i * width + j].v = yuv[i][j].v;
		}
	}
}

void createOutput(uint8_t * bufferOut, YUV * yuvArray, double SIZE)
{
	int size = (int)SIZE;
	int counter = 0;
	for (int i = 0; i < size; i = i + 4)
	{
		bufferOut[i] = yuvArray[counter].y;
		bufferOut[i + 1] = yuvArray[counter].u;
		bufferOut[i + 2] = yuvArray[counter + 1].y;
		bufferOut[i + 3] = yuvArray[counter + 1].v;

		counter = counter + 2;
	}
}

void nearestNeighbourInterpolation(YUV * *originalMatrix, YUV * *matrix, double WIDTH, double HEIGHT, double FACTOR)
{
	int iCord = 0;
	int jCord = 0;

	int height_new = (int)(HEIGHT * FACTOR);
	int width_new = (int)(WIDTH * FACTOR);

	for (int i = 0; i < height_new; i++)
	{
		for (int j = 0; j < width_new; j++)
		{
			iCord = (int)(i / FACTOR);
			jCord = (int)(j / FACTOR);

			matrix[i][j].y = originalMatrix[iCord][jCord].y;
			matrix[i][j].u = originalMatrix[iCord][jCord].u;
			matrix[i][j].v = originalMatrix[iCord][jCord].v;
		}
	}
}

double calculateBilinearValue(YUV** yuv, double I, double J, double SF, double WIDTH, double HEIGHT, char channel)
{
	int width = (int)WIDTH;
	int height = (int)HEIGHT;
	
	int q11 = 0, q12 = 0, q21 = 0, q22 = 0;
	
	double xScale = (WIDTH * SF) / (WIDTH - 1.00);
	double yScale = (HEIGHT * SF) / (HEIGHT - 1.00);
	
	double W = -(((I / yScale) - floor(I / yScale)) - 1);
	double H = -(((J / xScale) - floor(J / xScale)) - 1);
	
	double iCordFloor = floor(I / yScale);
	double jCordFloor = floor(J / xScale);
	double iCordCeil = ceil(I / yScale);
	double jCordCeil = ceil(J / xScale);
	
	if (channel == 'y')
	{
		q11 = yuv[(int)iCordFloor][(int)jCordFloor].y;
		q12 = yuv[(int)iCordCeil][(int)jCordFloor].y;
		q21 = yuv[(int)iCordFloor][(int)jCordCeil].y;
		q22 = yuv[(int)iCordCeil][(int)jCordCeil].y;
	}
	else if (channel == 'u')
	{
		q11 = yuv[(int)iCordFloor][(int)jCordFloor].u;
		q12 = yuv[(int)iCordCeil][(int)jCordFloor].u;
		q21 = yuv[(int)iCordFloor][(int)jCordCeil].u;
		q22 = yuv[(int)iCordCeil][(int)jCordCeil].u;
	}
	else if (channel == 'v')
	{
		q11 = yuv[(int)iCordFloor][(int)jCordFloor].v;
		q12 = yuv[(int)iCordCeil][(int)jCordFloor].v;
		q21 = yuv[(int)iCordFloor][(int)jCordCeil].v;
		q22 = yuv[(int)iCordCeil][(int)jCordCeil].v;
	}
	else
	{
		printf("WRONG CHANNEL \n");
		exit(0);
	}

	double result = ((1 - W) * (1 - H) * q22) + (W * (1 - H) * q21) + ((1 - W) * H * q12) + (W * H * q11);

	if (channel == 'y')
		printf("%d %d -- %.4f \n", (int)I, (int)J, result);

	return result;
}

void bilinearInterpolation(YUV * *originalMatrix, YUV * *matrix, double WIDTH, double HEIGHT, double FACTOR)
{
	int height_new = (int)(HEIGHT * FACTOR);
	int width_new = (int)(WIDTH * FACTOR);

	for (int i = 0; i < height_new; i++)
	{
		for (int j = 0; j < width_new; j++)
		{
			matrix[i][j].y = calculateBilinearValue(originalMatrix, (double)i, (double)j, FACTOR, WIDTH, HEIGHT, 'y');
			matrix[i][j].u = calculateBilinearValue(originalMatrix, (double)i, (double)j, FACTOR, WIDTH, HEIGHT, 'u');
			matrix[i][j].v = calculateBilinearValue(originalMatrix, (double)i, (double)j, FACTOR, WIDTH, HEIGHT, 'v');
		}
	}
}

void convertYUVtoYUVDouble(YUV * *yuv, YUV_Double * *yuvDouble, int width, int height)
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			yuvDouble[i][j].y = yuv[i][j].y;
			yuvDouble[i][j].u = yuv[i][j].u;
			yuvDouble[i][j].v = yuv[i][j].v;
		}
	}
}

void setBetaValue(double* q, YUV_Double * *yuv, int startPosition, int iCordFloor, int jCordFloor, int iCordCeil, int jCordCeil, char channel)
{
	if (channel == 'y')
	{
		q[startPosition] = yuv[iCordFloor][jCordFloor].y;
		q[startPosition + 1] = yuv[iCordFloor][jCordCeil].y;
		q[startPosition + 2] = yuv[iCordCeil][jCordFloor].y;
		q[startPosition + 3] = yuv[iCordCeil][jCordCeil].y;
	}
	else if (channel == 'u')
	{
		q[startPosition] = yuv[iCordFloor][jCordFloor].u;
		q[startPosition + 1] = yuv[iCordFloor][jCordCeil].u;
		q[startPosition + 2] = yuv[iCordCeil][jCordFloor].u;
		q[startPosition + 3] = yuv[iCordCeil][jCordCeil].u;
	}
	else if (channel == 'v')
	{
		q[startPosition] = yuv[iCordFloor][jCordFloor].v;
		q[startPosition + 1] = yuv[iCordFloor][jCordCeil].v;
		q[startPosition + 2] = yuv[iCordCeil][jCordFloor].v;
		q[startPosition + 3] = yuv[iCordCeil][jCordCeil].v;
	}
	else
	{
		printf("WRONG CHANNEL TYPE\n");
		exit(0);
	}
}

double calculateBicubicValue(YUV** yuvOrigin, YUV_Double * *yuv, YUV_Double * *Ix, YUV_Double * *Iy, YUV_Double * *Ixy, double WIDTH, double HEIGHT, double I, double J, double SF, char channel)
{
	double xScale = (WIDTH * SF) / (WIDTH - 1.00);
	double yScale = (HEIGHT * SF) / (HEIGHT - 1.00);

	int width = (int)WIDTH;
	int height = (int)HEIGHT;

	double alphaArr[16];
	double* alpha;
	double beta[16];

	double iCordCeil = ceil((I / yScale));
	double jCordCeil = ceil((J / xScale));
	double iCordFloor = floor((I / yScale));
	double jCordFloor = floor((J / xScale));

	double W = -(((I / yScale) - floor(I / yScale)) - 1.00);
	double H = -(((J / xScale) - floor(J / xScale)) - 1.00);


	setBetaValue(beta, yuv, 0, (int)iCordFloor, (int)jCordFloor, (int)iCordCeil, (int)jCordCeil, channel);
	setBetaValue(beta, Ix, 4, (int)iCordFloor, (int)jCordFloor, (int)iCordCeil, (int)jCordCeil, channel);
	setBetaValue(beta, Iy, 8, (int)iCordFloor, (int)jCordFloor, (int)iCordCeil, (int)jCordCeil, channel);
	setBetaValue(beta, Ixy, 12, (int)iCordFloor, (int)jCordFloor, (int)iCordCeil, (int)jCordCeil, channel);

	alpha = getAlpha(beta, alphaArr);

	double temp = 0;
	double w_temp;
	double h_temp;
	for (int f = 0; f < 16; f++)
	{
		w_temp = floor((double)f / 4);
		h_temp = fmod((double)f, 4);

		temp = temp + alpha[f] * (pow(1 - W, w_temp) * pow(1 - H, h_temp));
	}

	if (channel == 'y')
		printf("%.0f %.0f %f\n",I, J, temp);

	return temp;
}

void bicubicInterpolation(YUV * *originalMatrix, YUV * *matrix, double WIDTH, double HEIGHT, double SF)
{
	int height_new = (int)(HEIGHT * SF);
	int width_new = (int)(WIDTH * SF);

	YUV_Double** Ix;
	YUV_Double** Iy;
	YUV_Double** Ixy;
	YUV_Double** yuvDouble;

	allocateMatrixTypeDouble(&yuvDouble, WIDTH, HEIGHT, 1.00);
	allocateMatrixTypeDouble(&Ix, WIDTH, HEIGHT, 1.00);
	allocateMatrixTypeDouble(&Iy, WIDTH, HEIGHT, 1.00);
	allocateMatrixTypeDouble(&Ixy, WIDTH, HEIGHT, 1.00);

	createDerivative(Ix, Iy, Ixy, originalMatrix, (int)WIDTH, (int)HEIGHT);
	convertYUVtoYUVDouble(originalMatrix, yuvDouble, (int)WIDTH, (int)HEIGHT);

	for (int i = 0; i < height_new; i++)
	{
		for (int j = 0; j < width_new; j++)
		{
			matrix[i][j].y = (uint8_t)calculateBicubicValue(originalMatrix, yuvDouble, Ix, Iy, Ixy, WIDTH, HEIGHT, (double)i, (double)j, SF, 'y');
			matrix[i][j].u = (uint8_t)calculateBicubicValue(originalMatrix, yuvDouble, Ix, Iy, Ixy, WIDTH, HEIGHT, (double)i, (double)j, SF, 'u');
			matrix[i][j].v = (uint8_t)calculateBicubicValue(originalMatrix, yuvDouble, Ix, Iy, Ixy, WIDTH, HEIGHT, (double)i, (double)j, SF, 'v');
		}
	}

	deallocateMatrixTypeDouble(Ix, HEIGHT);
	deallocateMatrixTypeDouble(Iy, HEIGHT);
	deallocateMatrixTypeDouble(Ixy, HEIGHT);
	deallocateMatrixTypeDouble(yuvDouble, HEIGHT);
}

double* getAlpha(double* beta, double* alpha)
{
	double mult[256] = { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				-3, 3, 0, 0, -2, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				2, -2, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, -3, 3, 0, 0, -2, -1, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 2, -2, 0, 0, 1, 1, 0, 0,
				-3, 0, 3, 0, 0, 0, 0, 0, -2, 0, -1, 0, 0, 0, 0, 0,
				0, 0, 0, 0, -3, 0, 3, 0, 0, 0, 0, 0, -2, 0, -1, 0,
				9, -9, -9, 9, 6, 3, -6, -3, 6, -6, 3, -3, 4, 2, 2, 1,
				-6, 6, 6, -6, -3, -3, 3, 3, -4, 4, -2, 2, -2, -2, -1, -1,
				2, 0, -2, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 2, 0, -2, 0, 0, 0, 0, 0, 1, 0, 1, 0,
				-6, 6, 6, -6, -4, -2, 4, 2, -3, 3, -3, 3, -2, -1, -2, -1,
				4, -4, -4, 4, 2, 2, -2, -2, 2, -2, 2, -2, 1, 1, 1, 1 };

	int i = 0;
	for (int j = 0; j < 16; j++)
	{
		alpha[j] = 0;
		alpha[j] = alpha[j]
			+ mult[i] * beta[0]
			+ mult[i + 1] * beta[1]
			+ mult[i + 2] * beta[2]
			+ mult[i + 3] * beta[3]
			+ mult[i + 4] * beta[4]
			+ mult[i + 5] * beta[5]
			+ mult[i + 6] * beta[6]
			+ mult[i + 7] * beta[7]
			+ mult[i + 8] * beta[8]
			+ mult[i + 9] * beta[9]
			+ mult[i + 10] * beta[10]
			+ mult[i + 11] * beta[11]
			+ mult[i + 12] * beta[12]
			+ mult[i + 13] * beta[13]
			+ mult[i + 14] * beta[14]
			+ mult[i + 15] * beta[15];
		i = i + 16;
		//printf("%.2f   ", alpha[j]);
	}
	//printf("\n");
	return alpha;
}

void createDerivative(YUV_Double * *Ix, YUV_Double * *Iy, YUV_Double * *Ixy, YUV * *yuv, int width, int height)
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if ((j == 0) || (j == (width - 1)))
			{
				Ix[i][j].y = 0;
				Ix[i][j].u = 0;
				Ix[i][j].v = 0;
			}
			else
			{
				Ix[i][j].y = (0.5) * ((double)yuv[i][j + 1].y - (double)yuv[i][j - 1].y);
				Ix[i][j].u = (0.5) * ((double)yuv[i][j + 1].u - (double)yuv[i][j - 1].u);
				Ix[i][j].v = (0.5) * ((double)yuv[i][j + 1].v - (double)yuv[i][j - 1].v);
			}

			if ((i == 0) || (i == (height - 1)))
			{
				Iy[i][j].y = 0;
				Iy[i][j].u = 0;
				Iy[i][j].v = 0;
			}
			else
			{
				Iy[i][j].y = (0.5) * ((double)yuv[i + 1][j].y - (double)yuv[i - 1][j].y);
				Iy[i][j].u = (0.5) * ((double)yuv[i + 1][j].u - (double)yuv[i - 1][j].u);
				Iy[i][j].v = (0.5) * ((double)yuv[i + 1][j].v - (double)yuv[i - 1][j].v);
			}

			if ((i == 0) || (i == (height - 1) || (j == 0) || (j == (width - 1))))
			{
				Ixy[i][j].y = 0;
				Ixy[i][j].u = 0;
				Ixy[i][j].v = 0;
			}
			else
			{
				Ixy[i][j].y = (0.25) * (((double)yuv[i + 1][j + 1].y + (double)yuv[i - 1][j - 1].y) - ((double)yuv[i + 1][j - 1].y + (double)yuv[i - 1][j + 1].y));
				Ixy[i][j].u = (0.25) * (((double)yuv[i + 1][j + 1].u + (double)yuv[i - 1][j - 1].u) - ((double)yuv[i + 1][j - 1].u + (double)yuv[i - 1][j + 1].u));
				Ixy[i][j].v = (0.25) * (((double)yuv[i + 1][j + 1].v + (double)yuv[i - 1][j - 1].v) - ((double)yuv[i + 1][j - 1].v + (double)yuv[i - 1][j + 1].v));
			}
		}
	}
}

uint8_t * getFrameFromVideo(char* fileForRead, int frameSize, int frameNumber) {
	uint8_t* frame = malloc(frameSize);
	FILE* file = fopen(fileForRead, "rb");
	fseek(file, frameNumber * frameSize, 0);
	fread(frame, 1, frameSize, file);
	fclose(file);

	return frame;
}



//
//if (channel == 'y')
//{
//	q11 = yuv[iCordFloor][jCordFloor].y;
//	q12 = yuv[iCordCeil][jCordFloor].y;
//	q21 = yuv[iCordFloor][jCordCeil].y;
//	q22 = yuv[iCordCeil][jCordCeil].y;
//}
//else if (channel == 'u')
//{
//	q11 = yuv[iCordFloor][jCordFloor].u;
//	q12 = yuv[iCordCeil][jCordFloor].u;
//	q21 = yuv[iCordFloor][jCordCeil].u;
//	q22 = yuv[iCordCeil][jCordCeil].u;
//}
//else if (channel == 'v')
//{
//	q11 = yuv[iCordFloor][jCordFloor].v;
//	q12 = yuv[iCordCeil][jCordFloor].v;
//	q21 = yuv[iCordFloor][jCordCeil].v;
//	q22 = yuv[iCordCeil][jCordCeil].v;
//}
//else
//{
//	printf("WRONG CHANNEL \n");
//	exit(0);
//}


//double calculateBilinearValue(YUV** yuv, double I, double J, double SF, double WIDTH, double HEIGHT, char channel)
//{
//	int width = (int)WIDTH;
//	int height = (int)HEIGHT;
//
//	double q11 = 0, q12 = 0, q21 = 0, q22 = 0;
//
//	double xScale = (WIDTH * SF) / (WIDTH - 1.00);
//	double yScale = (HEIGHT * SF) / (HEIGHT - 1.00);
//
//	double W = -(((I / yScale) - floor(I / yScale)) - 1);
//	double H = -(((J / xScale) - floor(J / xScale)) - 1);
//
//	double iCordFloor = floor(I / yScale);
//	double jCordFloor = floor(J / xScale);
//	double iCordCeil = ceil(I / yScale);
//	double jCordCeil = ceil(J / xScale);
//
//	if (channel == 'y')
//	{
//		q11 = yuv[(int)iCordFloor][(int)jCordFloor].y;
//		q12 = yuv[(int)iCordCeil][(int)jCordFloor].y;
//		q21 = yuv[(int)iCordFloor][(int)jCordCeil].y;
//		q22 = yuv[(int)iCordCeil][(int)jCordCeil].y;
//	}
//	else if (channel == 'u')
//	{
//		q11 = yuv[(int)iCordFloor][(int)jCordFloor].u;
//		q12 = yuv[(int)iCordCeil][(int)jCordFloor].u;
//		q21 = yuv[(int)iCordFloor][(int)jCordCeil].u;
//		q22 = yuv[(int)iCordCeil][(int)jCordCeil].u;
//	}
//	else if (channel == 'v')
//	{
//		q11 = yuv[(int)iCordFloor][(int)jCordFloor].v;
//		q12 = yuv[(int)iCordCeil][(int)jCordFloor].v;
//		q21 = yuv[(int)iCordFloor][(int)jCordCeil].v;
//		q22 = yuv[(int)iCordCeil][(int)jCordCeil].v;
//	}
//	else
//	{
//		printf("WRONG CHANNEL \n");
//		exit(0);
//	}
//
//	double result = (1 - W) * (1 - H) * q22 + W * (1 - H) * q21 + (1 - W) * H * q12 + W * H * q11;
//
//	return result;
//}

//double calculateBilinearValue(YUV** yuv, double I, double J, double SF, double WIDTH, double HEIGHT, char channel)
//{
//	int width = (int)WIDTH; /*potential*/
//	int height = (int)HEIGHT;
//
//	double q11 = 0, q12 = 0, q21 = 0, q22 = 0;
//
//	double xScale = (WIDTH * SF) / (WIDTH - 1.00);
//	double yScale = (HEIGHT * SF) / (HEIGHT - 1.00);
//
//	double W = -(((I / yScale) - floor(I / yScale)) - 1);
//	double H = -(((J / xScale) - floor(J / xScale)) - 1);
//
//	int iCordFloor = (int)floor(I / SF);
//	int jCordFloor = (int)floor(J / SF);
//	int iCordCeil = (int)ceil(I / SF);
//	int jCordCeil = (int)ceil(I / SF);
//
//	if (iCordCeil >= height)
//	{
//		iCordCeil = height - 1;
//	}
//	if (channel == 'y')
//	{
//		q11 = yuv[iCordFloor][jCordFloor].y;
//		q12 = yuv[iCordCeil][jCordFloor].y;
//		q21 = yuv[iCordFloor][jCordCeil].y;
//		q22 = yuv[iCordCeil][jCordCeil].y;
//	}
//	else if (channel == 'u')
//	{
//		q11 = yuv[iCordFloor][jCordFloor].u;
//		q12 = yuv[iCordCeil][jCordFloor].u;
//		q21 = yuv[iCordFloor][jCordCeil].u;
//		q22 = yuv[iCordCeil][jCordCeil].u;
//	}
//	else if (channel == 'v')
//	{
//		q11 = yuv[iCordFloor][jCordFloor].v;
//		q12 = yuv[iCordCeil][jCordFloor].v;
//		q21 = yuv[iCordFloor][jCordCeil].v;
//		q22 = yuv[iCordCeil][jCordCeil].v;
//	}
//	else
//	{
//		printf("WRONG CHANNEL \n");
//		exit(0);
//	}
//
//	double result = (1 - W) * (1 - H) * q22 + W * (1 - H) * q21 + (1 - W) * H * q12 + W * H * q11;
//
//	return result;
//}
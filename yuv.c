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

void createMess(YUV * *matrix, uint8_t * output, int width, int height)
{
	int counter = 0;

	YUV* buffer;
	allocateYUVBuffer(&buffer, width * height);
	fillYUVBuffer(buffer, matrix, width, height);

	for (int i = 0; i < height * width * 3; i = i + 3)
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
	double iCord = 0.0;
	double jCord = 0.0;

	double xScale = (WIDTH * FACTOR) / (WIDTH - 1.00);
	double yScale = (HEIGHT * FACTOR) / (HEIGHT - 1.00);

	int height_new = (int)(HEIGHT * FACTOR);
	int width_new = (int)(WIDTH * FACTOR);

	for (int i = 0; i < height_new; i++)
	{
		for (int j = 0; j < width_new; j++)
		{
			double I = (double)i;
			double J = (double)j;

			iCord = round(I / yScale);
			jCord = round(J / xScale);

			matrix[i][j].y = originalMatrix[(int)iCord][(int)jCord].y;
			matrix[i][j].u = originalMatrix[(int)iCord][(int)jCord].u;
			matrix[i][j].v = originalMatrix[(int)iCord][(int)jCord].v;
		}
	}
}

double calculateBilinearValue(YUV * *yuv, double I, double J, double xScale, double yScale, char channel)
{
	double q11 = 0, q12 = 0, q21 = 0, q22 = 0;
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

	double result = (1 - W) * (1 - H) * q22 + W * (1 - H) * q21 + (1 - W) * H * q12 + W * H * q11;

	return result;
}

void bilinearInterpolation(YUV * *originalMatrix, YUV * *matrix, double WIDTH, double HEIGHT, double FACTOR)
{
	double xScale = (WIDTH * FACTOR) / (WIDTH - 1.00);
	double yScale = (HEIGHT * FACTOR) / (HEIGHT - 1.00);

	int height_new = (int)(HEIGHT * FACTOR);
	int width_new = (int)(WIDTH * FACTOR);

	for (int i = 0; i < height_new; i++)
	{
		for (int j = 0; j < width_new; j++)
		{
			matrix[i][j].y = calculateBilinearValue(originalMatrix, (double)i, (double)j, xScale, yScale, 'y');
			matrix[i][j].u = calculateBilinearValue(originalMatrix, (double)i, (double)j, xScale, yScale, 'u');
			matrix[i][j].v = calculateBilinearValue(originalMatrix, (double)i, (double)j, xScale, yScale, 'v');
		}
	}
}

void convertYUVtoYUVDouble(uint8_t** yuv, double** yuvDouble, int width, int height)
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			yuvDouble[0][i * width + j] = (double)yuv[0][i * width + j];
			yuvDouble[1][i * width + j] = (double)yuv[1][i * width + j];
			yuvDouble[2][i * width + j] = (double)yuv[2][i * width + j];
		}
	}
}

void setBetaValue(double* q, double** yuv, int width, int startPosition, int iCordFloor, int jCordFloor, int iCordCeil, int jCordCeil, char channel)
{
	if (channel == 'y')
	{
		q[startPosition] = yuv[0][iCordFloor * width + jCordFloor];
		q[startPosition + 1] = yuv[0][iCordFloor * width + jCordCeil];
		q[startPosition + 2] = yuv[0][iCordCeil * width + jCordFloor];
		q[startPosition + 3] = yuv[0][iCordCeil * width + jCordCeil];
	}
	else if (channel == 'u')
	{
		q[startPosition] = yuv[1][iCordFloor * width + jCordFloor];
		q[startPosition + 1] = yuv[1][iCordFloor * width + jCordCeil];
		q[startPosition + 2] = yuv[1][iCordCeil * width + jCordFloor];
		q[startPosition + 3] = yuv[1][iCordCeil * width + jCordCeil];
	}
	else if (channel == 'v')
	{
		q[startPosition] = yuv[2][iCordFloor * width + jCordFloor];
		q[startPosition + 1] = yuv[2][iCordFloor * width + jCordCeil];
		q[startPosition + 2] = yuv[2][iCordCeil * width + jCordFloor];
		q[startPosition + 3] = yuv[2][iCordCeil * width + jCordCeil];
	}
	else
	{
		printf("WRONG CHANNEL TYPE\n");
		exit(0);
	}
}

double calculateBicubicValue(uint8_t** yuvOrigin, double** yuv, double** Ix, double** Iy, double** Ixy, double WIDTH, double HEIGHT, double I, double J, double SF, char channel)
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


	setBetaValue(beta, yuv, width, 0, (int)iCordFloor, (int)jCordFloor, (int)iCordCeil, (int)jCordCeil, channel);
	setBetaValue(beta, Ix, width, 4, (int)iCordFloor, (int)jCordFloor, (int)iCordCeil, (int)jCordCeil, channel);
	setBetaValue(beta, Iy, width, 8, (int)iCordFloor, (int)jCordFloor, (int)iCordCeil, (int)jCordCeil, channel);
	setBetaValue(beta, Ixy, width, 12, (int)iCordFloor, (int)jCordFloor, (int)iCordCeil, (int)jCordCeil, channel);

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

	temp = clip(temp);

	return temp;
}

void bicubicInterpolation(uint8_t** originalMatrix, uint8_t** matrix, double WIDTH, double HEIGHT, double SF)
{
	int height_new = (int)(HEIGHT * SF);
	int width_new = (int)(WIDTH * SF);

	int width = (int)WIDTH;
	int height = (int)HEIGHT;

#pragma region Ix

	double* yix;
	yix = (double*)malloc(width * height * sizeof(double));
	double* uix;
	uix = (double*)malloc(width * height * sizeof(double));
	double* vix;
	vix = (double*)malloc(width * height * sizeof(double));

	double* Ix[3];
	Ix[0] = yix;
	Ix[1] = uix;
	Ix[2] = vix;

#pragma endregion

#pragma region Iy

	double* yiy;
	yiy = (double*)malloc(width * height * sizeof(double));
	double* uiy;
	uiy = (double*)malloc(width * height * sizeof(double));
	double* viy;
	viy = (double*)malloc(width * height * sizeof(double));

	double* Iy[3];
	Iy[0] = yiy;
	Iy[1] = uiy;
	Iy[2] = viy;

#pragma endregion

#pragma region Ixy

	double* yixy;
	yixy = (double*)malloc(width * height * sizeof(double));
	double* uixy;
	uixy = (double*)malloc(width * height * sizeof(double));
	double* vixy;
	vixy = (double*)malloc(width * height * sizeof(double));

	double* Ixy[3];
	Ixy[0] = yixy;
	Ixy[1] = uixy;
	Ixy[2] = vixy;

#pragma endregion

#pragma region yuvDouble

	double* yD;
	yD = (double*)malloc(width * height * sizeof(double));
	double* uD;
	uD = (double*)malloc(width * height * sizeof(double));
	double* vD;
	vD = (double*)malloc(width * height * sizeof(double));

	double* yuvDouble[3];
	yuvDouble[0] = yD;
	yuvDouble[1] = uD;
	yuvDouble[2] = vD;

#pragma endregion

	convertYUVtoYUVDouble(originalMatrix, yuvDouble, width, height);
	createDerivative(Ix, Iy, Ixy, yuvDouble, width, height);

	printf("%d %d\n", height_new, width_new);
	for (int i = 0; i < height_new; i++)
	{
		for (int j = 0; j < width_new; j++)
		{
			matrix[0][i * width_new + j] = (uint8_t)calculateBicubicValue(originalMatrix, yuvDouble, Ix, Iy, Ixy, WIDTH, HEIGHT, (double)i, (double)j, SF, 'y');
			matrix[1][i * width_new + j] = (uint8_t)calculateBicubicValue(originalMatrix, yuvDouble, Ix, Iy, Ixy, WIDTH, HEIGHT, (double)i, (double)j, SF, 'u');
			matrix[2][i * width_new + j] = (uint8_t)calculateBicubicValue(originalMatrix, yuvDouble, Ix, Iy, Ixy, WIDTH, HEIGHT, (double)i, (double)j, SF, 'v');
		}
	}
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

void createDerivative(double** Ix, double** Iy, double** Ixy, double** yuv, int width, int height)
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if ((j == 0) || (j == (width - 1)))
			{
				Ix[0][i * width + j] = 0;
				Ix[1][i * width + j] = 0;
				Ix[2][i * width + j] = 0;
			}
			else
			{
				Ix[0][i * width + j] = (0.5) * (yuv[0][i * width + j + 1] - yuv[0][i * width + j - 1]);
				Ix[1][i * width + j] = (0.5) * (yuv[1][i * width + j + 1] - yuv[1][i * width + j - 1]);
				Ix[2][i * width + j] = (0.5) * (yuv[2][i * width + j + 1] - yuv[2][i * width + j - 1]);
			}

			if ((i == 0) || (i == (height - 1)))
			{
				Iy[0][i * width + j] = 0;
				Iy[1][i * width + j] = 0;
				Iy[2][i * width + j] = 0;
			}
			else
			{
				Iy[0][i * width + j] = (0.5) * (yuv[0][(i + 1) * width + j] - yuv[0][(i - 1) * width + j]);
				Iy[1][i * width + j] = (0.5) * (yuv[1][(i + 1) * width + j] - yuv[1][(i - 1) * width + j]);
				Iy[2][i * width + j] = (0.5) * (yuv[2][(i + 1) * width + j] - yuv[2][(i - 1) * width + j]);
			}

			if ((i == 0) || (i == (height - 1) || (j == 0) || (j == (width - 1))))
			{
				Ixy[0][i * width + j] = 0;
				Ixy[1][i * width + j] = 0;
				Ixy[2][i * width + j] = 0;
			}
			else
			{
				Ixy[0][i * width + j] = (0.25) * ((yuv[0][(i + 1) * width + j + 1] + yuv[0][(i - 1) * width + j - 1]) - (yuv[0][(i + 1) * width + j - 1] + yuv[0][(i - 1) * width + j + 1]));
				Ixy[1][i * width + j] = (0.25) * ((yuv[1][(i + 1) * width + j + 1] + yuv[1][(i - 1) * width + j - 1]) - (yuv[1][(i + 1) * width + j - 1] + yuv[1][(i - 1) * width + j + 1]));
				Ixy[2][i * width + j] = (0.25) * ((yuv[2][(i + 1) * width + j + 1] + yuv[2][(i - 1) * width + j - 1]) - (yuv[2][(i + 1) * width + j - 1] + yuv[2][(i - 1) * width + j + 1]));
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
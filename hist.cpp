#include <cv.h>
#include <highgui.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <stdlib.h>
#include <fstream>
using namespace cv;
using namespace std;

int main(int argc, char *argv[])
{
	char *input = argv[1];
	char *output = argv[2];
	if (argc != 3)
	{
		cerr << "<exe> <input-file> <out-file>" << endl;
		return EXIT_FAILURE;
	}
	Mat image = imread(input, CV_LOAD_IMAGE_COLOR);
	ofstream PupartionInfo;
	PupartionInfo.open("image_data.txt", ios::app);
	int cols = image.cols;//width
	int rows = image.rows;//height
	//printf("%d,%d", cols, rows);
	double meanR, meanG, meanB;
	int i, j, m, l;
	int part;
	part = 8;

	int p = 0;

	for (j = 0; j < cols; j = j + cols / part)//垂直切-1
	{
		//for (i = 0; i < rows; i++)
		{
			meanR = 0;
			meanG = 0;
			meanB = 0;
			for (m = 0; m < cols / part; m++)
			{
				for (l = 0; l < rows; l++)
				{
					if ((j + m) < cols)
					{
						meanR += (double)image.at<Vec3b>(l, j + m)[0] / (cols / part) / rows;
						meanG += (double)image.at<Vec3b>(l, j + m)[1] / (cols / part) / rows;
						meanB += (double)image.at<Vec3b>(l, j + m)[2] / (cols / part) / rows;
					}
				}
			}
			PupartionInfo << (double)meanR << " " << (double)meanG << " " << (double)meanB << " ";//輸出平均值到txt檔
			PupartionInfo << "\n";
		}
	}


	//for (j = 0; j < cols; j++)//水平切-1
	{
		for (i = 0; i < rows; i = i + rows / part)
		{
			meanR = 0;
			meanG = 0;
			meanB = 0;
			for (m = 0; m < cols; m++)
			{
				for (l = 0; l < rows / part; l++)
				{
					if ((i + l) < rows)
					{
						meanR += (double)image.at<Vec3b>(l + i, m)[0] / (cols / part) / rows;
						meanG += (double)image.at<Vec3b>(l, m)[1] / (cols / part) / rows;
						meanB += (double)image.at<Vec3b>(l, m)[2] / (cols / part) / rows;
					}
				}
			}
			PupartionInfo << (double)meanR << " " << (double)meanG << " " << (double)meanB << " ";//輸出平均值到txt檔
			PupartionInfo << "\n";
		}
	}

	
	PupartionInfo.close();
	
	//imwrite(output, image);
	system("pause");
	return 0;
}
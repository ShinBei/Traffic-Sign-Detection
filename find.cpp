#include <stdio.h>
#include <math.h>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;
using namespace std;
char filename[100];
char windowname[100];

int main(int argc, char *argv[])
{
	
	ifstream in("image_data.txt");
	double s;
	double Control_Group[1000];
	int i = 0;
	if (!in.is_open())
	{
		cout << "Error opening file"; exit(1);
	}
	while (!in.eof())
	{
		while (in >> s)
		{
			Control_Group[i] = s;
			i++;
			/*cout << i << "\t";
			cout << Control_Group[i-1] << "\n";//576*/
		}
	}
	Mat image = imread("diff.jpg", CV_LOAD_IMAGE_COLOR);
	cvNamedWindow("原圖", 0);
	imshow("原圖", image);


	int cols = image.cols;//width
	int rows = image.rows;//height
	//printf("%d,%d", cols, rows);
	double meanR, meanG, meanB;
	int j, m, l;
	int part;
	part = 8;
	double data[100];
	double datas[100];


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
			data[p] = meanR;
			data[p+1] = meanG;
			data[p+2] = meanB;
			p = p + 3;
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
						meanR += (double)image.at<Vec3b>(l+i, m)[0] / (cols / part) / rows;
						meanG += (double)image.at<Vec3b>(l, m)[1] / (cols / part) / rows;
						meanB += (double)image.at<Vec3b>(l, m)[2] / (cols / part) / rows;
					}
				}
			}
			data[p] = meanR;
			data[p + 1] = meanG;
			data[p + 2] = meanB;
			p = p + 3;
		}
	}
	

	double min = 100000;
	double difference;
	double d[12];
	int num[12];
	int n = 0;

	for (int s = 0; s < 12; s++)
	{
		difference = 0;
		for (i = 0; i < 48; i++)
		{
			difference = double(difference + fabs(data[i] - Control_Group[n]));
			/*cout << difference << " " << data[i] << " " << Control_Group[n] << " ";*/
			n++;
		}
		//cout << endl;
		d[s] = difference;
		num[s] = s+1;
		//cout << d[s] << endl;
		/*if (difference < min)
		{
			min = difference;
			printf("%d,%f\n", s+1, min);
		}*/
	}

	for (int n = 11; n > 0; n--)
	{
		for (int m = 0; m < n; m++)
		{
			if (d[m] > d[m + 1])
			{
				int h;
				h = d[m];
				d[m] = d[m + 1];
				d[m + 1] = h;

				int h0;
				h0 = num[m];
				num[m] = num[m + 1];
				num[m + 1] = h0;
			}
		}
	}//cout << num[n] << input << endl;

	

	for (int i = 0; i < 5; i++)
	{
		int a = num[i];
		printf("%f\n", d[i]);
		sprintf(filename, "%d.jpg", a);
		sprintf(windowname, "圖片%d排名%d", a, i+1);
		IplImage* pScr = cvLoadImage(filename, 1);
		cvNamedWindow(windowname,0);
		cvResizeWindow(windowname, 300, 300);
		cvShowImage(windowname, pScr);

	}

	waitKey(0);
	//system("pause");
	
	return 0;
}
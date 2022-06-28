#include <opencv2/opencv.hpp> 
#include <iostream>
#include <math.h>

using namespace cv;
using namespace std;


double generateGaussianNoise(double m, double sigma);
Mat addGaussianNoise(Mat &srcImag);

int main(int argc,char** argv)
{
	Mat srcImage = imread("D:/41.jpg");
	if (!srcImage.data)
	{
		cout << "����ͼƬ����" << endl;
		system("pause");
		return -1;
	}
	imshow("ԭͼ��", srcImage);
	Mat dstImage = addGaussianNoise(srcImage);
	imshow("��Ӹ�˹�������ͼ��", dstImage);
	waitKey();
	imwrite("D:/42.jpg", dstImage);
	return 0;

}


//���ɸ�˹����
double generateGaussianNoise(double mu, double sigma)
{
	//����Сֵ
	const double epsilon = numeric_limits<double>::min();
	static double z0, z1;
	static bool flag = false;
	flag = !flag;
	//flagΪ�ٹ����˹�������X
	if (!flag)
		return z1 * sigma + mu;
	double u1, u2;
	//�����������
	do
	{
		u1 = rand() * (1.0 / RAND_MAX);
		u2 = rand() * (1.0 / RAND_MAX);
	} while (u1 <= epsilon);
	//flagΪ�湹���˹�������
	z0 = sqrt(-2.0*log(u1))*cos(2 * CV_PI*u2);
	z1 = sqrt(-2.0*log(u1))*sin(2 * CV_PI*u2);
	return z0*sigma + mu;
}
 
//Ϊͼ����Ӹ�˹����
Mat addGaussianNoise(Mat &srcImag)
{
	Mat dstImage = srcImag.clone();
	int channels = dstImage.channels();
	int rowsNumber = dstImage.rows;
	int colsNumber = dstImage.cols*channels;
	//�ж�ͼ���������
	if (dstImage.isContinuous())
	{
		colsNumber *= rowsNumber;
		rowsNumber = 1;
	}
	for (int i = 0; i < rowsNumber; i++)
	{
		for (int j = 0; j < colsNumber; j++)
		{
			//��Ӹ�˹����
			int val = dstImage.ptr<uchar>(i)[j] +
				generateGaussianNoise(2, 0.8) * 32;
			if (val < 0)
				val = 0;
			if (val>255)
				val = 255;
			dstImage.ptr<uchar>(i)[j] = (uchar)val;
		}
	}
	return dstImage;
}

////#include <cstdio>
////
////#include "opencv.hpp" //opencv 的头文件
////
////using namespace cv; //opencv 的命名空间
////
////int main()
////{
////
////
////	Mat img = imread("E:\\图像处理\\OpenCV_Test\\cat.jpg");  
////	namedWindow("Original Image");
////	imshow("Original Image", img);
////	Mat result;
////	flip(img, result, 1);
////	namedWindow("Output Image");
////	imshow("Output Image", result);
////	Mat ima(240, 320, CV_8U, Scalar(100));
////	namedWindow("1");
////	imshow("1", result);
////	waitKey(0);
////
////
////	return 0;
////}
////
////#include<iostream>
////#include<Windows.h>
////#include<malloc.h>
////#include<stdlib.h>
////#include<stdio.h>
////#include<string.h>
////using namespace std;
////void main()
////{
////	char fileName[] = "E:\\图像处理\\OpenCV_Test\\cat_8bit.bmp";                        //定义打开图像名字
////	BYTE *buf;                                //定义文件读取缓冲区
////	BYTE *p;
////	int r, g, b, pix;
////	HWND wnd;                                 //窗口句柄
////	HDC dc;                                   //绘图设备环境句柄
////	FILE *fp;                                 //定义文件指针
////	FILE *fpw;                                //定义保存文件指针
////	DWORD w, h;                                //定义读取图像的长和宽
////	DWORD bitCorlorUsed;                      //定义
////	DWORD bitSize;                            //定义图像的大小
////	BITMAPFILEHEADER bf;                      //图像文件头
////	BITMAPINFOHEADER bi;                      //图像文件头信息
////	
////
////	if ((fp = fopen(fileName, "rb")) == NULL)
////	{
////		cout << "文件未找到！";
////		exit(0);
////	}
////	fread(&bf, sizeof(BITMAPFILEHEADER), 1, fp);//读取BMP文件头文件
////	fread(&bi, sizeof(BITMAPINFOHEADER), 1, fp);//读取BMP文件头文件信息
////	w = bi.biWidth;                            //获取图像的宽
////	h = bi.biHeight;                           //获取图像的高
////	bitSize = bi.biSizeImage;                  //获取图像的size
////	int bitCount = bi.biBitCount;
////	int byteNum = bitCount / 8;
////	buf = (BYTE*)malloc(w*h * byteNum);                //分配缓冲区大小
////	RGBQUAD* colorTable = new RGBQUAD[256];
////	if (byteNum == 1) 
////	{	
////		fread(colorTable, sizeof(RGBQUAD), 255, fp);
////	}
////	fseek(fp, bf.bfOffBits, SEEK_SET);//14+40+255*4
////	fread(buf, 1, w*h * byteNum, fp);                   //开始读取数据
////	wnd = GetForegroundWindow();               //获取窗口句柄
////	dc = GetDC(wnd);                           //获取绘图设备
////	int x = 40;
////	int y = 40;
////	p = buf;
////	if (byteNum == 1)//8位图像，每个像素1个Byte
////	{
////		//int linenum = (w * 1 + 3) / 4 * 4;
////		//int ex = linenum - w * 1;         //每一行的填充字节
////		//fseek(fp, bf.bfOffBits, SEEK_SET);
////	
////		//	for (int i = 0; i < h; i++)
////		//	{
////		//	    fread(p+ i *w, sizeof(BYTE), w, fp);			
////		//		fseek(fp, ex, SEEK_CUR);
////		//	}
////		for (int j = 0; j < h; j++)
////		{
////			for (int i = 0; i < w; i++)
////			{
////				int np = *p++;
////				r = (colorTable+np)->rgbRed;
////				g = (colorTable + np)->rgbGreen;
////				b = (colorTable + np)->rgbBlue;
////				pix = RGB(r,g,b);
////				SetPixel(dc, x + i, y + h - j, pix);
////			}
////		}
////
////	}
////	else if(byteNum==2)//16位图像，每个像素2个Byte
////	{ 
////		if (bi.biCompression == 0)//555
////		{
////			WORD pixel;
////			for (int j = 0; j < h; j++)
////			{
////				for (int i = 0; i < w; i++)
////				{
////					pixel = *(WORD*)(p);
////					r = ((0x7C00 & pixel) >> 10) << 3;
////					g = ((0x03E0 & pixel) >> 5) << 3;
////					b = ((0x001F & pixel) >> 0) << 3;
////					pix = RGB(r, g, b);
////					SetPixel(dc, x + i, y + h - j, pix);
////					p += 2;
////				}
////			}
////		}
////	}
////	else if (byteNum == 3)//24位图像，每个像素3个Byte
////	{
////		for (int j = 0; j < h; j++)
////		{
////			for (int i = 0; i < w; i++)
////			{
////				b = *p++; g = *p++; r = *p++; 
////				pix = RGB(r, g, b);
////				SetPixel(dc, x + i, y + h - j, pix);
////			}
////		}
////	}
////	else if (byteNum == 4)//32位图像，每个像素4个Byte
////	{
////		for (int j = 0; j < h; j++)
////		{
////			for (int i = 0; i < w; i++)
////			{
////				b = *p++; g = *p++; r = *p++; p++;
////				pix = RGB(r, g, b);
////				SetPixel(dc, x + i, y + h - j, pix);
////			}
////		}
////	}
////	//fpw = fopen("Cat11.bmp", "wb");
////	//fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, fpw);  //写入文件头
////	//fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, fpw);  //写入文件头信息
////	//p = buf;
////	//for (int j = 0; j < h; j++)
////	//{
////	//	for (int i = 0; i < w * 3; i++)
////	//	{
////	//		fwrite(p++, 1, 1, fpw);
////	//	}
////	//}
////	//fclose(fpw);
////	fclose(fp);
////	//return fp;
////	system("pause");
////}
////#include<opencv2/opencv.hpp>
////#include<time.h>
////#include<iostream>
////
////using namespace std;
////using namespace cv;
////
////int main() {
////	system("color 2F");
////
////	载入原图，转化为 HSV 颜色模型
////	Mat srcImage, hsvImage;
////	srcImage = imread("E:\\图像处理\\OpenCV_Test\\cat_24bit.bmp");
////	cvtColor(srcImage, hsvImage, COLOR_BGR2HSV);
////
////	将色调量化为 30 个等级，将饱和度量化为 32 个等级
////	int hueBinNum = 30;		//色调的直方图直条数量
////	int saturationBinNum = 32;		//饱和度的直方图直条数量
////	int histSize[] = { hueBinNum,saturationBinNum };
////	定义色调的变化范围为 0 到 179
////	float hueRanges[] = { 0,180 };
////	定义饱和度的变化范围为 0（黑、白、灰）到 255（纯光谱颜色）
////	float saturationRanges[] = { 0,256 };
////	const float* ranges[] = { hueRanges,saturationRanges };
////	MatND dstHist;	//Mat 一般指二维矩阵，MatND 指多维矩阵（ > 2 )
////	calcHist 函数中将计算第 0 通道和第 1 通道的直方图
////	int channels[] = { 0,1 };
////
////	正式调用 calcHist ，进行直方图计算
////	calcHist(
////		&hsvImage,	//输入的数组
////		1,		//数组个数为 1
////		channels,	//通道索引
////		Mat(),		//不使用掩膜
////		dstHist,	//输出的目标直方图
////		2,		//需要计算的直方图的维度为 2
////		histSize,	//存放每个维度的直方图尺寸的数组
////		ranges,		//每一维数值的取值范围数组
////		true,		//指示直方图是否均匀的标识符，true 表示均匀的直方图
////		false		//累计标识符，false 表示直方图在配置阶段会被清零
////	);
////
////	为绘制直方图准备参数
////	double  maxValue = 0;	//最大值
////	查找数组和子数组的全局最小值和最大值存入 maxValue 中
////	minMaxLoc(dstHist, 0, &maxValue, 0, 0);
////	int scale = 10;		//直方图放大倍数
////	Mat histImage = Mat::zeros(saturationBinNum * scale, hueBinNum * 10, CV_8UC3);
////
////	双重循环，实现直方图绘制
////	for (int hue = 0; hue < hueBinNum; hue++) {
////		for (int saturation = 0; saturation < saturationBinNum; saturation++) {
////			直方图直条的值
////			float binValue = dstHist.at<float>(hue, saturation);
////			int intensity = cvRound(binValue * 255 / maxValue);		//强度
////
////			正式进行绘制
////			rectangle(
////				histImage,
////				Point(hue * scale, saturation * scale),
////				Point((hue + 1) * scale - 1, (saturation + 1) * scale - 1),
////				Scalar::all(intensity),
////				FILLED
////			);
////		}
////	}
////	imshow("素材图", srcImage);
////	imshow("H-S 直方图", histImage);
////
////	waitKey(0);
////	return 0;
////}
////
////#include<opencv2/opencv.hpp>
////#include<time.h>
////#include<iostream>
////
////using namespace std;
////using namespace cv;
////
////int main() {
////	system("color 2F");
////
////	Mat srcImage = imread("E:\\图像处理\\OpenCV_Test\\cat_24bit.bmp");
////	imshow("素材图", srcImage);
////	if (!srcImage.data) {
////		printf("图像读取失败!");
////		return 0;
////	}
////
////	int bins = 256;
////	int hist_size[] = { bins };
////	float range[] = { 0,256 };
////	const float *ranges[] = { range };
////	MatND redHist, greenHist, blueHist;
////	int channels_r[] = { 0 };
////
////	//进行直方图的计算（红色分量部分）
////	calcHist(&srcImage, 1, channels_r, Mat(),	//不使用掩膜
////		redHist, 1, hist_size, ranges, true, false);
////
////	//进行直方图计算（绿色分量部分）
////	int channels_g[] = { 1 };
////	calcHist(&srcImage, 1, channels_g, Mat(),
////		greenHist, 1, hist_size, ranges, true, false);
////
////	//进行直方图计算（蓝色分量部分）
////	int channels_b[] = { 2 };
////	calcHist(&srcImage, 1, channels_b, Mat(),
////		blueHist, 1, hist_size, ranges, true, false);
////
////	//准备参数绘制三色直方图
////	double maxValue_red, maxValue_green, maxValue_blue;
////	minMaxLoc(redHist, 0, &maxValue_red, 0, 0);
////	minMaxLoc(greenHist, 0, &maxValue_green, 0, 0);
////	minMaxLoc(blueHist, 0, &maxValue_blue, 0, 0);
////	int scale = 1;
////	int histHeight = 256;
////	//bins * 3 是因为要绘制三个通道,每个通道的像素取值在 0-bins
////	Mat histImage = Mat::zeros(histHeight, bins * 3, CV_8UC3);
////
////	//开始绘制
////	for (int i = 0; i < bins; i++) {
////		float binValue_red = redHist.at<float>(i);
////		float binValue_green = greenHist.at<float>(i);
////		float binValue_blue = blueHist.at<float>(i);
////
////		//计算高度时的乘除与下面绘图的 histHeight - intensity 是为了便于显示，否则有的色度很低
////		//要绘制的高度
////		int intensity_red = cvRound(binValue_red * histHeight / maxValue_red);
////		int intensity_green = cvRound(binValue_green * histHeight / maxValue_green);
////		int intensity_blue = cvRound(binValue_blue * histHeight / maxValue_blue);
////		//绘制红色分量直方图
////		rectangle(histImage, Point(i * scale, histHeight - 1),
////			Point((i + 1) * scale - 1, histHeight - intensity_red),
////			Scalar(255, 0, 0));
////
////		//绘制绿色分量直方图
////		rectangle(histImage, Point((i + bins) * scale, histHeight - 1),
////			Point((i + bins + 1) * scale - 1, histHeight - intensity_green),
////			Scalar(0, 255, 0));
////
////		//绘制分量直方图
////		rectangle(histImage, Point((i + bins * 2) * scale, histHeight - 1),
////			Point((i + bins * 2 + 1) * scale - 1, histHeight - intensity_blue),
////			Scalar(0, 0, 255));
////	}
////
////	imshow("图像的 RGB 直方图", histImage);
////
////	waitKey(0);
////	return 0;
////}
//#include<opencv2/opencv.hpp>
//#include<time.h>
//#include<iostream>
//
//using namespace std;
//using namespace cv;
//
//int main() {
//	/*system("color 2F");*/
//
//	Mat srcImage = imread("E:\\图像处理\\OpenCV_Test\\cat_24bit.bmp", 0);
//	imshow("原图", srcImage);
//	if (!srcImage.data) {
//		printf("图像读取失败!");
//		return 0;
//	}
//
//	MatND dstHist;
//	int dims = 1;
//	float hranges[] = { 0,255 };
//	const float *ranges[] = { hranges };	//这里需为 const 类型 
//	int size = 256;
//	int channels = 0;
//
//	//计算图像的直方图
//	calcHist(&srcImage, 1, &channels, Mat(), dstHist, dims, &size, ranges);
//	int scale = 1;
//
//	Mat dstImage(size * scale, size, CV_8U, Scalar(0));
//
//	//获取最大值和最小值
//	double minValue = 0;
//	double maxValue = 0;
//	minMaxLoc(dstHist, &minValue, &maxValue, 0, 0);
//
//	//绘制出直方图
//	int hpt = saturate_cast<int>(0.9 * size);
//	for (int i = 0; i < 256; i++) {
//		float binValue = dstHist.at<float>(i);	//注意 hist 中是 float 类型
//		int realValue = saturate_cast<int>(binValue * hpt / maxValue);
//		rectangle(dstImage, Point(i * scale, size - 1),
//			Point((i + 1) * scale - 1, size - realValue), Scalar(255));
//	}
//	imshow("一维直方图", dstImage);
//
//	waitKey(0);
//	return 0;
//}
//#include<stdio.h>
//#include<iostream>
//int main()
//{
//	char nfileName []= "..//Joey.bmp";
//	char *fileName = new char[strlen(nfileName)];
//	strcpy(fileName, nfileName);
//	strlen(fileName);
//
//}
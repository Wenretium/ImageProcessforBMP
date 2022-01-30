////#include <cstdio>
////
////#include "opencv.hpp" //opencv ��ͷ�ļ�
////
////using namespace cv; //opencv �������ռ�
////
////int main()
////{
////
////
////	Mat img = imread("E:\\ͼ����\\OpenCV_Test\\cat.jpg");  
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
////	char fileName[] = "E:\\ͼ����\\OpenCV_Test\\cat_8bit.bmp";                        //�����ͼ������
////	BYTE *buf;                                //�����ļ���ȡ������
////	BYTE *p;
////	int r, g, b, pix;
////	HWND wnd;                                 //���ھ��
////	HDC dc;                                   //��ͼ�豸�������
////	FILE *fp;                                 //�����ļ�ָ��
////	FILE *fpw;                                //���屣���ļ�ָ��
////	DWORD w, h;                                //�����ȡͼ��ĳ��Ϳ�
////	DWORD bitCorlorUsed;                      //����
////	DWORD bitSize;                            //����ͼ��Ĵ�С
////	BITMAPFILEHEADER bf;                      //ͼ���ļ�ͷ
////	BITMAPINFOHEADER bi;                      //ͼ���ļ�ͷ��Ϣ
////	
////
////	if ((fp = fopen(fileName, "rb")) == NULL)
////	{
////		cout << "�ļ�δ�ҵ���";
////		exit(0);
////	}
////	fread(&bf, sizeof(BITMAPFILEHEADER), 1, fp);//��ȡBMP�ļ�ͷ�ļ�
////	fread(&bi, sizeof(BITMAPINFOHEADER), 1, fp);//��ȡBMP�ļ�ͷ�ļ���Ϣ
////	w = bi.biWidth;                            //��ȡͼ��Ŀ�
////	h = bi.biHeight;                           //��ȡͼ��ĸ�
////	bitSize = bi.biSizeImage;                  //��ȡͼ���size
////	int bitCount = bi.biBitCount;
////	int byteNum = bitCount / 8;
////	buf = (BYTE*)malloc(w*h * byteNum);                //���仺������С
////	RGBQUAD* colorTable = new RGBQUAD[256];
////	if (byteNum == 1) 
////	{	
////		fread(colorTable, sizeof(RGBQUAD), 255, fp);
////	}
////	fseek(fp, bf.bfOffBits, SEEK_SET);//14+40+255*4
////	fread(buf, 1, w*h * byteNum, fp);                   //��ʼ��ȡ����
////	wnd = GetForegroundWindow();               //��ȡ���ھ��
////	dc = GetDC(wnd);                           //��ȡ��ͼ�豸
////	int x = 40;
////	int y = 40;
////	p = buf;
////	if (byteNum == 1)//8λͼ��ÿ������1��Byte
////	{
////		//int linenum = (w * 1 + 3) / 4 * 4;
////		//int ex = linenum - w * 1;         //ÿһ�е�����ֽ�
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
////	else if(byteNum==2)//16λͼ��ÿ������2��Byte
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
////	else if (byteNum == 3)//24λͼ��ÿ������3��Byte
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
////	else if (byteNum == 4)//32λͼ��ÿ������4��Byte
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
////	//fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, fpw);  //д���ļ�ͷ
////	//fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, fpw);  //д���ļ�ͷ��Ϣ
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
////	����ԭͼ��ת��Ϊ HSV ��ɫģ��
////	Mat srcImage, hsvImage;
////	srcImage = imread("E:\\ͼ����\\OpenCV_Test\\cat_24bit.bmp");
////	cvtColor(srcImage, hsvImage, COLOR_BGR2HSV);
////
////	��ɫ������Ϊ 30 ���ȼ��������Ͷ�����Ϊ 32 ���ȼ�
////	int hueBinNum = 30;		//ɫ����ֱ��ͼֱ������
////	int saturationBinNum = 32;		//���Ͷȵ�ֱ��ͼֱ������
////	int histSize[] = { hueBinNum,saturationBinNum };
////	����ɫ���ı仯��ΧΪ 0 �� 179
////	float hueRanges[] = { 0,180 };
////	���履�Ͷȵı仯��ΧΪ 0���ڡ��ס��ң��� 255����������ɫ��
////	float saturationRanges[] = { 0,256 };
////	const float* ranges[] = { hueRanges,saturationRanges };
////	MatND dstHist;	//Mat һ��ָ��ά����MatND ָ��ά���� > 2 )
////	calcHist �����н������ 0 ͨ���͵� 1 ͨ����ֱ��ͼ
////	int channels[] = { 0,1 };
////
////	��ʽ���� calcHist ������ֱ��ͼ����
////	calcHist(
////		&hsvImage,	//���������
////		1,		//�������Ϊ 1
////		channels,	//ͨ������
////		Mat(),		//��ʹ����Ĥ
////		dstHist,	//�����Ŀ��ֱ��ͼ
////		2,		//��Ҫ�����ֱ��ͼ��ά��Ϊ 2
////		histSize,	//���ÿ��ά�ȵ�ֱ��ͼ�ߴ������
////		ranges,		//ÿһά��ֵ��ȡֵ��Χ����
////		true,		//ָʾֱ��ͼ�Ƿ���ȵı�ʶ����true ��ʾ���ȵ�ֱ��ͼ
////		false		//�ۼƱ�ʶ����false ��ʾֱ��ͼ�����ý׶λᱻ����
////	);
////
////	Ϊ����ֱ��ͼ׼������
////	double  maxValue = 0;	//���ֵ
////	����������������ȫ����Сֵ�����ֵ���� maxValue ��
////	minMaxLoc(dstHist, 0, &maxValue, 0, 0);
////	int scale = 10;		//ֱ��ͼ�Ŵ���
////	Mat histImage = Mat::zeros(saturationBinNum * scale, hueBinNum * 10, CV_8UC3);
////
////	˫��ѭ����ʵ��ֱ��ͼ����
////	for (int hue = 0; hue < hueBinNum; hue++) {
////		for (int saturation = 0; saturation < saturationBinNum; saturation++) {
////			ֱ��ͼֱ����ֵ
////			float binValue = dstHist.at<float>(hue, saturation);
////			int intensity = cvRound(binValue * 255 / maxValue);		//ǿ��
////
////			��ʽ���л���
////			rectangle(
////				histImage,
////				Point(hue * scale, saturation * scale),
////				Point((hue + 1) * scale - 1, (saturation + 1) * scale - 1),
////				Scalar::all(intensity),
////				FILLED
////			);
////		}
////	}
////	imshow("�ز�ͼ", srcImage);
////	imshow("H-S ֱ��ͼ", histImage);
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
////	Mat srcImage = imread("E:\\ͼ����\\OpenCV_Test\\cat_24bit.bmp");
////	imshow("�ز�ͼ", srcImage);
////	if (!srcImage.data) {
////		printf("ͼ���ȡʧ��!");
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
////	//����ֱ��ͼ�ļ��㣨��ɫ�������֣�
////	calcHist(&srcImage, 1, channels_r, Mat(),	//��ʹ����Ĥ
////		redHist, 1, hist_size, ranges, true, false);
////
////	//����ֱ��ͼ���㣨��ɫ�������֣�
////	int channels_g[] = { 1 };
////	calcHist(&srcImage, 1, channels_g, Mat(),
////		greenHist, 1, hist_size, ranges, true, false);
////
////	//����ֱ��ͼ���㣨��ɫ�������֣�
////	int channels_b[] = { 2 };
////	calcHist(&srcImage, 1, channels_b, Mat(),
////		blueHist, 1, hist_size, ranges, true, false);
////
////	//׼������������ɫֱ��ͼ
////	double maxValue_red, maxValue_green, maxValue_blue;
////	minMaxLoc(redHist, 0, &maxValue_red, 0, 0);
////	minMaxLoc(greenHist, 0, &maxValue_green, 0, 0);
////	minMaxLoc(blueHist, 0, &maxValue_blue, 0, 0);
////	int scale = 1;
////	int histHeight = 256;
////	//bins * 3 ����ΪҪ��������ͨ��,ÿ��ͨ��������ȡֵ�� 0-bins
////	Mat histImage = Mat::zeros(histHeight, bins * 3, CV_8UC3);
////
////	//��ʼ����
////	for (int i = 0; i < bins; i++) {
////		float binValue_red = redHist.at<float>(i);
////		float binValue_green = greenHist.at<float>(i);
////		float binValue_blue = blueHist.at<float>(i);
////
////		//����߶�ʱ�ĳ˳��������ͼ�� histHeight - intensity ��Ϊ�˱�����ʾ�������е�ɫ�Ⱥܵ�
////		//Ҫ���Ƶĸ߶�
////		int intensity_red = cvRound(binValue_red * histHeight / maxValue_red);
////		int intensity_green = cvRound(binValue_green * histHeight / maxValue_green);
////		int intensity_blue = cvRound(binValue_blue * histHeight / maxValue_blue);
////		//���ƺ�ɫ����ֱ��ͼ
////		rectangle(histImage, Point(i * scale, histHeight - 1),
////			Point((i + 1) * scale - 1, histHeight - intensity_red),
////			Scalar(255, 0, 0));
////
////		//������ɫ����ֱ��ͼ
////		rectangle(histImage, Point((i + bins) * scale, histHeight - 1),
////			Point((i + bins + 1) * scale - 1, histHeight - intensity_green),
////			Scalar(0, 255, 0));
////
////		//���Ʒ���ֱ��ͼ
////		rectangle(histImage, Point((i + bins * 2) * scale, histHeight - 1),
////			Point((i + bins * 2 + 1) * scale - 1, histHeight - intensity_blue),
////			Scalar(0, 0, 255));
////	}
////
////	imshow("ͼ��� RGB ֱ��ͼ", histImage);
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
//	Mat srcImage = imread("E:\\ͼ����\\OpenCV_Test\\cat_24bit.bmp", 0);
//	imshow("ԭͼ", srcImage);
//	if (!srcImage.data) {
//		printf("ͼ���ȡʧ��!");
//		return 0;
//	}
//
//	MatND dstHist;
//	int dims = 1;
//	float hranges[] = { 0,255 };
//	const float *ranges[] = { hranges };	//������Ϊ const ���� 
//	int size = 256;
//	int channels = 0;
//
//	//����ͼ���ֱ��ͼ
//	calcHist(&srcImage, 1, &channels, Mat(), dstHist, dims, &size, ranges);
//	int scale = 1;
//
//	Mat dstImage(size * scale, size, CV_8U, Scalar(0));
//
//	//��ȡ���ֵ����Сֵ
//	double minValue = 0;
//	double maxValue = 0;
//	minMaxLoc(dstHist, &minValue, &maxValue, 0, 0);
//
//	//���Ƴ�ֱ��ͼ
//	int hpt = saturate_cast<int>(0.9 * size);
//	for (int i = 0; i < 256; i++) {
//		float binValue = dstHist.at<float>(i);	//ע�� hist ���� float ����
//		int realValue = saturate_cast<int>(binValue * hpt / maxValue);
//		rectangle(dstImage, Point(i * scale, size - 1),
//			Point((i + 1) * scale - 1, size - realValue), Scalar(255));
//	}
//	imshow("һάֱ��ͼ", dstImage);
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
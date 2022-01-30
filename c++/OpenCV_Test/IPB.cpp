#include"Ipb.h"
//构造函数，构造新Ipb对象
Ipb::Ipb(const char* nfileName)
{
	fileName = new char[strlen(nfileName) + 1]; //+1，留一个字节给'\0'，否则报错：heap corruption detected 
	strcpy(fileName, nfileName);

	if ((fp = fopen(fileName, "rb")) == NULL) //图片读取失败
	{
		std::cout << "文件未找到！";
		exit(0);
	}
	else valid = true;  //图片读取成功
	fread(&bf, sizeof(BITMAPFILEHEADER), 1, fp);  //读取BMP文件头文件
	fread(&bi, sizeof(BITMAPINFOHEADER), 1, fp);  //读取BMP文件头文件信息
	width = bi.biWidth;  //获取图像的宽
	height = bi.biHeight;  //获取图像的高
	bitSize = bi.biSizeImage;  //获取图像的size
	bitCount = bi.biBitCount;  //获取图像的像素所占位数
	byteNum = float(bitCount) / 8;  //计算图像的像素所占字节数
	sizeofColormap = (bf.bfOffBits - sizeof(BITMAPFILEHEADER) - sizeof(BITMAPINFOHEADER)) / 4;  //计算调色板大小

	fseek(fp, sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER), 0);  //定位到调色板开始位置
	//对1 4 8位位图：根据各自调色板大小，开辟调色板内存，读取调色板数据
	if (bitCount == 1)
	{
		colorTable = new RGBQUAD[sizeofColormap];
		fread(colorTable, sizeof(RGBQUAD), sizeofColormap, fp);
		/*for (int i = 0; i < 2; i++)  //调试用代码
			std::cout << int((colorTable + i)->rgbRed) << " " << int((colorTable + i)->rgbGreen) << " " << int((colorTable + i)->rgbBlue) << std::endl;*/
	}
	else if (bitCount == 4)
	{
		colorTable = new RGBQUAD[sizeofColormap];  //实践发现，4位图片调色板的大小并不等于16，在已尝试的图片中都等于9？是ps算法问题还是？
		fread(colorTable, sizeof(RGBQUAD), sizeofColormap, fp);
		/*	for(int i=0;i<16;i++)  //调试用代码
			std::cout << int((colorTable+i)->rgbRed) << " "<< int((colorTable + i)->rgbGreen )<< " " << int((colorTable + i)->rgbBlue)<< std::endl;*/
	}
	else if (bitCount == 8)
	{
		colorTable = new RGBQUAD[sizeofColormap];
		fread(colorTable, sizeof(RGBQUAD), sizeofColormap, fp);
	}

	//图像每一行的字节数必须是4的整数倍
	int linenum = int((width * byteNum + 3) / 4) * 4;  //一行像素的字节总数，包括填充字节									
	int ex = linenum - width * byteNum;  //每一行的填充字节
	//分配缓冲区大小：linenum*height（大于实际大小：width*height*byteNum，避免出现非整数）
	buf = new BYTE[linenum*height];

	fseek(fp, bf.bfOffBits, SEEK_SET);  //定位到像素起始位置

	//开始读取像素值
	if (buf != NULL)
	{
		for (int i = 0; i < height; i++)
		{
			fread(buf + i * (linenum - ex), 1, linenum - ex, fp);
			//用 i * (linenum - ex)：1 4位像素所占字节数为非整数，i*width*bitCount/8可能为非整数 		
			fseek(fp, ex, SEEK_CUR);  //跳过ex个字节（填充字节）
		}
	}

	fclose(fp);
}

//析构函数
Ipb::~Ipb()
{
	delete[] buf;
	delete[] fileName;
}

//判断是否已读取图片
bool Ipb::isValid()
{
	return valid;
}

//加载图像
void Ipb::loadImage(const char* nfileName)
{
	if (valid == 0) //释放原内容所开辟的内存
	{
		delete[] buf;
		delete[] fileName;
	}

	fileName = new char[strlen(nfileName)+1]; //+1，留一个字节给'\0'，否则报错：heap corruption detected 
	strcpy(fileName, nfileName);

	if ((fp = fopen(fileName, "rb")) == NULL) //图片读取失败
	{
		std::cout << "文件未找到！";
		exit(0);
	}
	else valid = true;  //图片读取成功
	fread(&bf, sizeof(BITMAPFILEHEADER), 1, fp);  //读取BMP文件头文件
	fread(&bi, sizeof(BITMAPINFOHEADER), 1, fp);  //读取BMP文件头文件信息
	width = bi.biWidth;  //获取图像的宽
	height = bi.biHeight;  //获取图像的高
	bitSize = bi.biSizeImage;  //获取图像的size
	bitCount = bi.biBitCount;  //获取图像的像素所占位数
	byteNum = float(bitCount) / 8;  //计算图像的像素所占字节数
	sizeofColormap = (bf.bfOffBits - sizeof(BITMAPFILEHEADER) - sizeof(BITMAPINFOHEADER)) / 4;  //计算调色板大小
	
	fseek(fp, sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER), 0);  //定位到调色板开始位置
	//对1 4 8位位图：根据各自调色板大小，开辟调色板内存，读取调色板数据
	if (bitCount == 1)
	{
		colorTable = new RGBQUAD[sizeofColormap];
		fread(colorTable, sizeof(RGBQUAD), sizeofColormap, fp);
		/*for (int i = 0; i < 2; i++)  //调试用代码
			std::cout << int((colorTable + i)->rgbRed) << " " << int((colorTable + i)->rgbGreen) << " " << int((colorTable + i)->rgbBlue) << std::endl;*/
	}
	else if (bitCount == 4)
	{
		colorTable = new RGBQUAD[sizeofColormap];  //实践发现，4位图片调色板的大小并不等于16，在已尝试的图片中都等于9？是ps算法问题还是？
		fread(colorTable, sizeof(RGBQUAD), sizeofColormap, fp);
		/*	for(int i=0;i<16;i++)  //调试用代码
			std::cout << int((colorTable+i)->rgbRed) << " "<< int((colorTable + i)->rgbGreen )<< " " << int((colorTable + i)->rgbBlue)<< std::endl;*/
	}
	else if (bitCount == 8)
	{
		colorTable = new RGBQUAD[sizeofColormap];
		fread(colorTable, sizeof(RGBQUAD), sizeofColormap, fp);
	}

	//图像每一行的字节数必须是4的整数倍
	int linenum = int((width * byteNum + 3) / 4) * 4;  //一行像素的字节总数，包括填充字节									
	int ex = linenum - width * byteNum;  //每一行的填充字节
	//分配缓冲区大小：linenum*height（大于实际大小：width*height*byteNum，避免出现非整数）
	buf = new BYTE[linenum*height];               
	
	fseek(fp, bf.bfOffBits, SEEK_SET);  //定位到像素起始位置

	//开始读取像素值
	if (buf != NULL)
	{
		for (int i = 0; i < height; i++)
		{
			fread(buf + i * (linenum - ex), 1, linenum - ex, fp);
			//用 i * (linenum - ex)：1 4位像素所占字节数为非整数，i*width*bitCount/8可能为非整数 		
			fseek(fp, ex, SEEK_CUR);  //跳过ex个字节（填充字节）
		}
	}

	fclose(fp);
}

//图像另存为，储存新图像
void Ipb::saveImageAs(const char* fileName_save)
{
	FILE *fpw;  //存储文件
	fpw = fopen(fileName_save, "wb");  //打开或新建一个二进制文件fileName_save，只允许写数据
	fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, fpw);  //写入文件头
	fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, fpw);  //写入文件头信息
	BYTE* p = buf;  //避免改动buf的值

	 //1 4 8位图片：写入调色板
	if (bitCount == 1)
	{
		fwrite(colorTable, 4, 2, fpw);
	}
	else if (bitCount == 4)
	{
		fwrite(colorTable, 4, sizeofColormap, fpw);
	}
	if (bitCount == 8) 
	{
		fwrite(colorTable, 4, sizeofColormap, fpw);
	}

	BYTE* ex=NULL;
	int linenum = int((width * byteNum + 3) / 4 )* 4;  //一行像素的字节总数，包括填充字节
	int extend = linenum- width * byteNum;  //每一行的填充字节
	if (extend)  //需填充字节
	{
		ex = new BYTE[extend];  //填充数组大小为extend（0~3）
		memset(ex, 0, extend);  //在填充数组内写入extend个0
	}
	
	//写入各像素颜色
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i <linenum-extend ; i++)
		{
			fwrite(p++, 1, 1, fpw);
		}
		if (extend) fwrite((void *)ex, 1, extend, fpw);  //像素行末，进行填充
	}

	fclose(fpw);

	if (extend)
		delete[] ex;
}

//显示图像
void Ipb::printImage()
{
	HWND wnd = GetForegroundWindow();  //获取窗口句柄
	HDC dc = GetDC(wnd);  //获取绘图设备
	int x = 40;  //左上角坐标位置
	int y = 40;
	int r, g, b, pix;
	BYTE* p = buf;  //避免改动buf的值
	
	switch (bitCount)
	{		
	case 1:
		for (int j = 0; j < height; j++)
		{
			for (int i = 0; i < width;)
			{
				BYTE b = *p++;	
				int n[8];  //获得字节中每个位数
				n[0] = (b & 0x01) == 0x01 ? 1 : 0;
				n[1] = (b & 0x02) == 0x02 ? 1 : 0;
				n[2] = (b & 0x04) == 0x04 ? 1 : 0;
				n[3] = (b & 0x08) == 0x08 ? 1 : 0;
				n[4] = (b & 0x10) == 0x10 ? 1 : 0;
				n[5] = (b & 0x20) == 0x20 ? 1 : 0;
				n[6] = (b & 0x40) == 0x40 ? 1 : 0;
				n[7] = (b & 0x80) == 0x80 ? 1 : 0;
				for(int k = 7; k>=0; k--)
				{
					/*np = (a << k) >> 7 + k;*/		//尝试自己写，结果失败了			
					/*if (np == 1) count++;
					else if (np == 0)count2++;
					else count3++;*/
					r = (colorTable + n[k])->rgbRed;
					g = (colorTable + n[k])->rgbGreen;
					b = (colorTable + n[k])->rgbBlue;
					pix = RGB(r, g, b);
					SetPixel(dc, x + i, y + height - j, pix);
					i++;
					if (i >= width)break;
				}		
			}
		}
		break;
	case 4:
		for (int j = 0; j < height; j++)
		{
			for (int i = 0; i < width; i++)
			{
				BYTE a = *p++;
				int np1 = (a & 0xf0) >> 4;  //将一个字节进行位运算，取出前后4位
				int np2 = a & 0x0f;
				r = (colorTable + np1)->rgbRed;
				g = (colorTable + np1)->rgbGreen;
				b = (colorTable + np1)->rgbBlue;
				pix = RGB(r, g, b);
				SetPixel(dc, x + i, y + height - j, pix); //从左下角开始画
				i++;
				r = (colorTable + np2)->rgbRed;
				g = (colorTable + np2)->rgbGreen;
				b = (colorTable + np2)->rgbBlue;
				pix = RGB(r, g, b);
				SetPixel(dc, x + i, y + height - j, pix);
			}
		}
		break;
	case 8:
		for (int j = 0; j < height; j++)
		{
			for (int i = 0; i < width; i++)
			{			
				int np = *p++;  //每个字节为一个像素
				r = (colorTable + np)->rgbRed;
				g = (colorTable + np)->rgbGreen;
				b = (colorTable + np)->rgbBlue;
				pix = RGB(r, g, b);
				SetPixel(dc, x + i, y + height - j, pix); //从左下角开始画
			}		
		}
		break;
	case 16:
		if (bi.biCompression == 0)//555，将两个字节拆为5、5、5位
		{
			WORD pixel;
			for (int j = 0; j < height; j++)
			{
				for (int i = 0; i < width; i++)
				{
					pixel = *(WORD*)p;
					r = ((0x7C00 & pixel) >> 10) << 3;
					g = ((0x03E0 & pixel) >> 5) << 3;
					b = ((0x001F & pixel) >> 0) << 3;
					pix = RGB(r, g, b);
					SetPixel(dc, x + i, y + height - j, pix);
					p += 2;
				}
			}
		}
		break;
	case 24:
		for (int j = 0; j < height; j++)
		{
			for (int i = 0; i < width; i++)
			{			
				b = *p++;  //3个字节为一像素
				g = *p++; 
				r = *p++;
				pix = RGB(r, g, b);
				SetPixel(dc, x + i, y + height - j, pix);
			}
		}
		break;
	case 32:
		for (int j = 0; j < height; j++)
		{
			for (int i = 0; i < width; i++)
			{
				b = *p++; //4个字节为一像素
				g = *p++; 
				r = *p++;
				p++;
				pix = RGB(r, g, b);
				SetPixel(dc, x + i, y + height - j, pix);
			}
		}
	}
}

//绘制直方图
void Ipb::printHist()
{
	cv::Mat srcImage = cv::imread(fileName, 0);
	//cv::imshow("原图", srcImage);
	if (!srcImage.data) 
	{
		printf("图像读取失败!");		
	}

	cv::MatND dstHist;
	int dims = 1;
	float hranges[] = { 0,255 };
	const float *ranges[] = { hranges };	//这里需为 const 类型 
	int size = 256;
	int channels = 0;

	//计算图像的直方图
	calcHist(&srcImage, 1, &channels, cv::Mat(), dstHist, dims, &size, ranges);
	int scale = 1;

	cv::Mat dstImage(size * scale, size, CV_8U, cv::Scalar(0));

	//获取最大值和最小值
	double minValue = 0;
	double maxValue = 0;
	minMaxLoc(dstHist, &minValue, &maxValue, 0, 0);

	//绘制出直方图
	int hpt =cv::saturate_cast<int>(0.9 * size);
	for (int i = 0; i < 256; i++) {
		float binValue = dstHist.at<float>(i);	//注意 hist 中是 float 类型
		int realValue = cv::saturate_cast<int>(binValue * hpt / maxValue);
		cv::rectangle(dstImage, cv::Point(i * scale, size - 1),
			cv::Point((i + 1) * scale - 1, size - realValue), cv::Scalar(255));
	}
	cv::imshow("一维直方图", dstImage);
	cv::waitKey(0);
}

//存储为txt文档
void Ipb::saveAsFile(const char* fileName_txt)
{
	std::ofstream of;
	of.open(fileName_txt);  //打开或新建一个二进制文件fileName_txt，只允许写数据
	int r, g, b;
	BYTE* p = buf;  //避免改动buf的值

	switch (bitCount)
	{
	case 1:
		for (int j = 0; j < height; j++)
		{
			for (int i = 0; i < width;)
			{
				BYTE b = *p++;
				int n[8];  //获得字节中每个位数
				n[0] = (b & 0x01) == 0x01 ? 1 : 0;
				n[1] = (b & 0x02) == 0x02 ? 1 : 0;
				n[2] = (b & 0x04) == 0x04 ? 1 : 0;
				n[3] = (b & 0x08) == 0x08 ? 1 : 0;
				n[4] = (b & 0x10) == 0x10 ? 1 : 0;
				n[5] = (b & 0x20) == 0x20 ? 1 : 0;
				n[6] = (b & 0x40) == 0x40 ? 1 : 0;
				n[7] = (b & 0x80) == 0x80 ? 1 : 0;

				for (int k = 7; k >= 0; k--)
				{							
					r = (colorTable + n[k])->rgbRed;
					g = (colorTable + n[k])->rgbGreen;
					b = (colorTable + n[k])->rgbBlue;
					std::string bb=std::to_string(b);	//b后面总是带一个'\0',造成输出错误（仅1位图现象）			
					of << "(" << r << "," << g << "," << bb << ")" << " ";
					i++;
					if (i >= width)break;
				}
			}
		}
		break;
	case 4:
		for (int j = 0; j < height; j++)
		{
			for (int i = 0; i < width; i++)
			{
				BYTE a = *p++;
				int np1 = (a & 0xf0) >> 4;
				int np2 = a & 0x0f;
				r = (colorTable + np1)->rgbRed;
				g = (colorTable + np1)->rgbGreen;
				b = (colorTable + np1)->rgbBlue;
				of << "(" << r << "," << g << "," << b << ")" << " ";
				i++;
				r = (colorTable + np2)->rgbRed;
				g = (colorTable + np2)->rgbGreen;
				b = (colorTable + np2)->rgbBlue;
				of << "(" << r << "," << g << "," << b << ")" << " ";
			}
		}
		break;
	case 8:
		for (int j = 0; j < height; j++)
		{
			for (int i = 0; i < width; i++)
			{
				int np = *p++;
				r = (colorTable + np)->rgbRed;
				g = (colorTable + np)->rgbGreen;
				b = (colorTable + np)->rgbBlue;
				of << "(" << r << "," << g << "," << b << ")" << " ";
			}
		}
		break;
	case 16:
		if (bi.biCompression == 0)//555
		{
			WORD pixel;
			for (int j = 0; j < height; j++)
			{
				for (int i = 0; i < width; i++)
				{
					pixel = *(WORD*)p;
					r = ((0x7C00 & pixel) >> 10) << 3;
					g = ((0x03E0 & pixel) >> 5) << 3;
					b = ((0x001F & pixel) >> 0) << 3;
					of << "(" << r << "," << g << "," << b << ")" << " ";
					p += 2;
				}
			}
		}
		break;
	case 24:
		for (int j = 0; j < height; j++)
		{
			for (int i = 0; i < width; i++)
			{
				b = *p++;
				g = *p++;
				r = *p++;
				of << "(" << r << "," << g << "," << b << ")" << " ";
			}
		}
		break;
	case 32:
		for (int j = 0; j < height; j++)
		{
			for (int i = 0; i < width; i++)
			{
				b = *p++;
				g = *p++;
				r = *p++;
				p++;
				of << "(" << r << "," << g << "," << b << ")" << " ";
			}
		}
	}

	of.close();
}


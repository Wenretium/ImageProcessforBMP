#include"Ipb.h"
//���캯����������Ipb����
Ipb::Ipb(const char* nfileName)
{
	fileName = new char[strlen(nfileName) + 1]; //+1����һ���ֽڸ�'\0'�����򱨴�heap corruption detected 
	strcpy(fileName, nfileName);

	if ((fp = fopen(fileName, "rb")) == NULL) //ͼƬ��ȡʧ��
	{
		std::cout << "�ļ�δ�ҵ���";
		exit(0);
	}
	else valid = true;  //ͼƬ��ȡ�ɹ�
	fread(&bf, sizeof(BITMAPFILEHEADER), 1, fp);  //��ȡBMP�ļ�ͷ�ļ�
	fread(&bi, sizeof(BITMAPINFOHEADER), 1, fp);  //��ȡBMP�ļ�ͷ�ļ���Ϣ
	width = bi.biWidth;  //��ȡͼ��Ŀ�
	height = bi.biHeight;  //��ȡͼ��ĸ�
	bitSize = bi.biSizeImage;  //��ȡͼ���size
	bitCount = bi.biBitCount;  //��ȡͼ���������ռλ��
	byteNum = float(bitCount) / 8;  //����ͼ���������ռ�ֽ���
	sizeofColormap = (bf.bfOffBits - sizeof(BITMAPFILEHEADER) - sizeof(BITMAPINFOHEADER)) / 4;  //�����ɫ���С

	fseek(fp, sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER), 0);  //��λ����ɫ�忪ʼλ��
	//��1 4 8λλͼ�����ݸ��Ե�ɫ���С�����ٵ�ɫ���ڴ棬��ȡ��ɫ������
	if (bitCount == 1)
	{
		colorTable = new RGBQUAD[sizeofColormap];
		fread(colorTable, sizeof(RGBQUAD), sizeofColormap, fp);
		/*for (int i = 0; i < 2; i++)  //�����ô���
			std::cout << int((colorTable + i)->rgbRed) << " " << int((colorTable + i)->rgbGreen) << " " << int((colorTable + i)->rgbBlue) << std::endl;*/
	}
	else if (bitCount == 4)
	{
		colorTable = new RGBQUAD[sizeofColormap];  //ʵ�����֣�4λͼƬ��ɫ��Ĵ�С��������16�����ѳ��Ե�ͼƬ�ж�����9����ps�㷨���⻹�ǣ�
		fread(colorTable, sizeof(RGBQUAD), sizeofColormap, fp);
		/*	for(int i=0;i<16;i++)  //�����ô���
			std::cout << int((colorTable+i)->rgbRed) << " "<< int((colorTable + i)->rgbGreen )<< " " << int((colorTable + i)->rgbBlue)<< std::endl;*/
	}
	else if (bitCount == 8)
	{
		colorTable = new RGBQUAD[sizeofColormap];
		fread(colorTable, sizeof(RGBQUAD), sizeofColormap, fp);
	}

	//ͼ��ÿһ�е��ֽ���������4��������
	int linenum = int((width * byteNum + 3) / 4) * 4;  //һ�����ص��ֽ���������������ֽ�									
	int ex = linenum - width * byteNum;  //ÿһ�е�����ֽ�
	//���仺������С��linenum*height������ʵ�ʴ�С��width*height*byteNum��������ַ�������
	buf = new BYTE[linenum*height];

	fseek(fp, bf.bfOffBits, SEEK_SET);  //��λ��������ʼλ��

	//��ʼ��ȡ����ֵ
	if (buf != NULL)
	{
		for (int i = 0; i < height; i++)
		{
			fread(buf + i * (linenum - ex), 1, linenum - ex, fp);
			//�� i * (linenum - ex)��1 4λ������ռ�ֽ���Ϊ��������i*width*bitCount/8����Ϊ������ 		
			fseek(fp, ex, SEEK_CUR);  //����ex���ֽڣ�����ֽڣ�
		}
	}

	fclose(fp);
}

//��������
Ipb::~Ipb()
{
	delete[] buf;
	delete[] fileName;
}

//�ж��Ƿ��Ѷ�ȡͼƬ
bool Ipb::isValid()
{
	return valid;
}

//����ͼ��
void Ipb::loadImage(const char* nfileName)
{
	if (valid == 0) //�ͷ�ԭ���������ٵ��ڴ�
	{
		delete[] buf;
		delete[] fileName;
	}

	fileName = new char[strlen(nfileName)+1]; //+1����һ���ֽڸ�'\0'�����򱨴�heap corruption detected 
	strcpy(fileName, nfileName);

	if ((fp = fopen(fileName, "rb")) == NULL) //ͼƬ��ȡʧ��
	{
		std::cout << "�ļ�δ�ҵ���";
		exit(0);
	}
	else valid = true;  //ͼƬ��ȡ�ɹ�
	fread(&bf, sizeof(BITMAPFILEHEADER), 1, fp);  //��ȡBMP�ļ�ͷ�ļ�
	fread(&bi, sizeof(BITMAPINFOHEADER), 1, fp);  //��ȡBMP�ļ�ͷ�ļ���Ϣ
	width = bi.biWidth;  //��ȡͼ��Ŀ�
	height = bi.biHeight;  //��ȡͼ��ĸ�
	bitSize = bi.biSizeImage;  //��ȡͼ���size
	bitCount = bi.biBitCount;  //��ȡͼ���������ռλ��
	byteNum = float(bitCount) / 8;  //����ͼ���������ռ�ֽ���
	sizeofColormap = (bf.bfOffBits - sizeof(BITMAPFILEHEADER) - sizeof(BITMAPINFOHEADER)) / 4;  //�����ɫ���С
	
	fseek(fp, sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER), 0);  //��λ����ɫ�忪ʼλ��
	//��1 4 8λλͼ�����ݸ��Ե�ɫ���С�����ٵ�ɫ���ڴ棬��ȡ��ɫ������
	if (bitCount == 1)
	{
		colorTable = new RGBQUAD[sizeofColormap];
		fread(colorTable, sizeof(RGBQUAD), sizeofColormap, fp);
		/*for (int i = 0; i < 2; i++)  //�����ô���
			std::cout << int((colorTable + i)->rgbRed) << " " << int((colorTable + i)->rgbGreen) << " " << int((colorTable + i)->rgbBlue) << std::endl;*/
	}
	else if (bitCount == 4)
	{
		colorTable = new RGBQUAD[sizeofColormap];  //ʵ�����֣�4λͼƬ��ɫ��Ĵ�С��������16�����ѳ��Ե�ͼƬ�ж�����9����ps�㷨���⻹�ǣ�
		fread(colorTable, sizeof(RGBQUAD), sizeofColormap, fp);
		/*	for(int i=0;i<16;i++)  //�����ô���
			std::cout << int((colorTable+i)->rgbRed) << " "<< int((colorTable + i)->rgbGreen )<< " " << int((colorTable + i)->rgbBlue)<< std::endl;*/
	}
	else if (bitCount == 8)
	{
		colorTable = new RGBQUAD[sizeofColormap];
		fread(colorTable, sizeof(RGBQUAD), sizeofColormap, fp);
	}

	//ͼ��ÿһ�е��ֽ���������4��������
	int linenum = int((width * byteNum + 3) / 4) * 4;  //һ�����ص��ֽ���������������ֽ�									
	int ex = linenum - width * byteNum;  //ÿһ�е�����ֽ�
	//���仺������С��linenum*height������ʵ�ʴ�С��width*height*byteNum��������ַ�������
	buf = new BYTE[linenum*height];               
	
	fseek(fp, bf.bfOffBits, SEEK_SET);  //��λ��������ʼλ��

	//��ʼ��ȡ����ֵ
	if (buf != NULL)
	{
		for (int i = 0; i < height; i++)
		{
			fread(buf + i * (linenum - ex), 1, linenum - ex, fp);
			//�� i * (linenum - ex)��1 4λ������ռ�ֽ���Ϊ��������i*width*bitCount/8����Ϊ������ 		
			fseek(fp, ex, SEEK_CUR);  //����ex���ֽڣ�����ֽڣ�
		}
	}

	fclose(fp);
}

//ͼ�����Ϊ��������ͼ��
void Ipb::saveImageAs(const char* fileName_save)
{
	FILE *fpw;  //�洢�ļ�
	fpw = fopen(fileName_save, "wb");  //�򿪻��½�һ���������ļ�fileName_save��ֻ����д����
	fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, fpw);  //д���ļ�ͷ
	fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, fpw);  //д���ļ�ͷ��Ϣ
	BYTE* p = buf;  //����Ķ�buf��ֵ

	 //1 4 8λͼƬ��д���ɫ��
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
	int linenum = int((width * byteNum + 3) / 4 )* 4;  //һ�����ص��ֽ���������������ֽ�
	int extend = linenum- width * byteNum;  //ÿһ�е�����ֽ�
	if (extend)  //������ֽ�
	{
		ex = new BYTE[extend];  //��������СΪextend��0~3��
		memset(ex, 0, extend);  //�����������д��extend��0
	}
	
	//д���������ɫ
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i <linenum-extend ; i++)
		{
			fwrite(p++, 1, 1, fpw);
		}
		if (extend) fwrite((void *)ex, 1, extend, fpw);  //������ĩ���������
	}

	fclose(fpw);

	if (extend)
		delete[] ex;
}

//��ʾͼ��
void Ipb::printImage()
{
	HWND wnd = GetForegroundWindow();  //��ȡ���ھ��
	HDC dc = GetDC(wnd);  //��ȡ��ͼ�豸
	int x = 40;  //���Ͻ�����λ��
	int y = 40;
	int r, g, b, pix;
	BYTE* p = buf;  //����Ķ�buf��ֵ
	
	switch (bitCount)
	{		
	case 1:
		for (int j = 0; j < height; j++)
		{
			for (int i = 0; i < width;)
			{
				BYTE b = *p++;	
				int n[8];  //����ֽ���ÿ��λ��
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
					/*np = (a << k) >> 7 + k;*/		//�����Լ�д�����ʧ����			
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
				int np1 = (a & 0xf0) >> 4;  //��һ���ֽڽ���λ���㣬ȡ��ǰ��4λ
				int np2 = a & 0x0f;
				r = (colorTable + np1)->rgbRed;
				g = (colorTable + np1)->rgbGreen;
				b = (colorTable + np1)->rgbBlue;
				pix = RGB(r, g, b);
				SetPixel(dc, x + i, y + height - j, pix); //�����½ǿ�ʼ��
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
				int np = *p++;  //ÿ���ֽ�Ϊһ������
				r = (colorTable + np)->rgbRed;
				g = (colorTable + np)->rgbGreen;
				b = (colorTable + np)->rgbBlue;
				pix = RGB(r, g, b);
				SetPixel(dc, x + i, y + height - j, pix); //�����½ǿ�ʼ��
			}		
		}
		break;
	case 16:
		if (bi.biCompression == 0)//555���������ֽڲ�Ϊ5��5��5λ
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
				b = *p++;  //3���ֽ�Ϊһ����
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
				b = *p++; //4���ֽ�Ϊһ����
				g = *p++; 
				r = *p++;
				p++;
				pix = RGB(r, g, b);
				SetPixel(dc, x + i, y + height - j, pix);
			}
		}
	}
}

//����ֱ��ͼ
void Ipb::printHist()
{
	cv::Mat srcImage = cv::imread(fileName, 0);
	//cv::imshow("ԭͼ", srcImage);
	if (!srcImage.data) 
	{
		printf("ͼ���ȡʧ��!");		
	}

	cv::MatND dstHist;
	int dims = 1;
	float hranges[] = { 0,255 };
	const float *ranges[] = { hranges };	//������Ϊ const ���� 
	int size = 256;
	int channels = 0;

	//����ͼ���ֱ��ͼ
	calcHist(&srcImage, 1, &channels, cv::Mat(), dstHist, dims, &size, ranges);
	int scale = 1;

	cv::Mat dstImage(size * scale, size, CV_8U, cv::Scalar(0));

	//��ȡ���ֵ����Сֵ
	double minValue = 0;
	double maxValue = 0;
	minMaxLoc(dstHist, &minValue, &maxValue, 0, 0);

	//���Ƴ�ֱ��ͼ
	int hpt =cv::saturate_cast<int>(0.9 * size);
	for (int i = 0; i < 256; i++) {
		float binValue = dstHist.at<float>(i);	//ע�� hist ���� float ����
		int realValue = cv::saturate_cast<int>(binValue * hpt / maxValue);
		cv::rectangle(dstImage, cv::Point(i * scale, size - 1),
			cv::Point((i + 1) * scale - 1, size - realValue), cv::Scalar(255));
	}
	cv::imshow("һάֱ��ͼ", dstImage);
	cv::waitKey(0);
}

//�洢Ϊtxt�ĵ�
void Ipb::saveAsFile(const char* fileName_txt)
{
	std::ofstream of;
	of.open(fileName_txt);  //�򿪻��½�һ���������ļ�fileName_txt��ֻ����д����
	int r, g, b;
	BYTE* p = buf;  //����Ķ�buf��ֵ

	switch (bitCount)
	{
	case 1:
		for (int j = 0; j < height; j++)
		{
			for (int i = 0; i < width;)
			{
				BYTE b = *p++;
				int n[8];  //����ֽ���ÿ��λ��
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
					std::string bb=std::to_string(b);	//b�������Ǵ�һ��'\0',���������󣨽�1λͼ����			
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


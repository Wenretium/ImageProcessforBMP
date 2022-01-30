#pragma once
#include<Windows.h>
#include<iostream>
#include<opencv2/opencv.hpp>
#include<string>
#include<fstream>
class Ipb
{
private:
	bool valid; //�Ƿ��Ѷ�ȡͼƬ
	BITMAPFILEHEADER bf;  //ͼ���ļ�ͷ
	BITMAPINFOHEADER bi;  //ͼ���ļ�ͷ��Ϣ
	DWORD bitSize;  //����ͼ��Ĵ�С
	char* fileName;  //����ȡͼƬ���ļ���
	FILE *fp;  //��ȡ�ļ���ָ��
	DWORD width, height;  //��ȡͼ��ĳ��Ϳ�
	BYTE *buf;  //�ļ���ȡ������
	int bitCount;  //ÿ��������ռλ��
	float byteNum;  //ÿ��������ռ�ֽ���
	RGBQUAD* colorTable = NULL;  //��ɫ�壨1 4 8 λͼ�����õ���
	int sizeofColormap;  //��ɫ��Ĵ�С
public:
	Ipb() : valid(false) {} //Ĭ�Ϲ��캯��
	Ipb(const char* nfileName); //���캯��
	~Ipb(); //��������
	bool isValid(); //�ж��Ƿ��Ѷ�ȡͼƬ
	int getWidth() { return width; } //��ȡͼ����
	int getHeight() { return height; } //��ȡͼƬ�߶�
	void loadImage(const char* nFileName); //����ͼ��
	void saveImageAs(const char* nfileName); //ͼ�����Ϊ��������ͼ��
	void printImage(); //��ʾͼ��
	void printHist(); //����ֱ��ͼ
	void saveAsFile(const char* fileName_txt);
};

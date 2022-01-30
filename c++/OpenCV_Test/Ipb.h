#pragma once
#include<Windows.h>
#include<iostream>
#include<opencv2/opencv.hpp>
#include<string>
#include<fstream>
class Ipb
{
private:
	bool valid; //是否已读取图片
	BITMAPFILEHEADER bf;  //图像文件头
	BITMAPINFOHEADER bi;  //图像文件头信息
	DWORD bitSize;  //定义图像的大小
	char* fileName;  //所读取图片的文件名
	FILE *fp;  //读取文件的指针
	DWORD width, height;  //读取图像的长和宽
	BYTE *buf;  //文件读取缓冲区
	int bitCount;  //每个像素所占位数
	float byteNum;  //每个像素所占字节数
	RGBQUAD* colorTable = NULL;  //调色板（1 4 8 位图像需用到）
	int sizeofColormap;  //调色板的大小
public:
	Ipb() : valid(false) {} //默认构造函数
	Ipb(const char* nfileName); //构造函数
	~Ipb(); //析构函数
	bool isValid(); //判断是否已读取图片
	int getWidth() { return width; } //获取图像宽度
	int getHeight() { return height; } //获取图片高度
	void loadImage(const char* nFileName); //加载图像
	void saveImageAs(const char* nfileName); //图像另存为，储存新图像
	void printImage(); //显示图像
	void printHist(); //绘制直方图
	void saveAsFile(const char* fileName_txt);
};

#include"Ipb.h"
int main()
{
	int pictures_bits[] = { 1,4,8,16,24,32 }; //分别代表1、4、8、16、24、32位图
	std::string begin = "..//cat";
	std::string end = ".bmp"; //准备构造fileName字符串
	std::string begin_save = "..//save//test";
	std::string end_save = "_save.bmp"; //准备构造fileName_save字符串
	std::string begin_txt = "..//txt//test";
	std::string end_txt = ".txt"; //准备构造fileName_txt字符串

	Ipb ip; //调用默认构造函数，暂时不读取图片
	for (int k = 0; k < 6; k++)
	{
		std::string sbit = std::to_string(pictures_bits[k]); //将整型数字转换成string
		std::string sfileName = begin + sbit + end; //构造fileName字符串，代表待读取图片名
		const char* fileName = sfileName.data(); //将string类型字符串转换成char类型字符数组

		ip.loadImage(fileName); //传入参数fileName，读取相应图像

		ip.printImage(); //在控制台显示图像

		std::string sfileName_save = begin_save + sbit + end_save; //构造fileName_save字符串，代表待存储图片名
		const char* fileName_save = sfileName_save.data(); //将string类型字符串转换成char类型字符数组

		ip.saveImageAs(fileName_save); //传入参数fileName_save，作为图片名存储新图像

		ip.printHist(); //显示相应图片的直方图

		std::string sfileName_txt = begin_txt + sbit + end_txt; //构造fileName_save字符串，代表待存储图片名
		const char* fileName_txt = sfileName_txt.data(); //将string类型字符串转换成char类型字符数组
		ip.saveAsFile(fileName_txt);

		system("cls"); //清屏
	}
	Sleep(1000); //暂停1s
	std::cout << "演示完毕" << std::endl; //演示完毕
	Sleep(1000); //暂停1s
	return 0; //结束
}
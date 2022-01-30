#include"Ipb.h"
int main()
{
	int pictures_bits[] = { 1,4,8,16,24,32 }; //�ֱ����1��4��8��16��24��32λͼ
	std::string begin = "..//cat";
	std::string end = ".bmp"; //׼������fileName�ַ���
	std::string begin_save = "..//save//test";
	std::string end_save = "_save.bmp"; //׼������fileName_save�ַ���
	std::string begin_txt = "..//txt//test";
	std::string end_txt = ".txt"; //׼������fileName_txt�ַ���

	Ipb ip; //����Ĭ�Ϲ��캯������ʱ����ȡͼƬ
	for (int k = 0; k < 6; k++)
	{
		std::string sbit = std::to_string(pictures_bits[k]); //����������ת����string
		std::string sfileName = begin + sbit + end; //����fileName�ַ������������ȡͼƬ��
		const char* fileName = sfileName.data(); //��string�����ַ���ת����char�����ַ�����

		ip.loadImage(fileName); //�������fileName����ȡ��Ӧͼ��

		ip.printImage(); //�ڿ���̨��ʾͼ��

		std::string sfileName_save = begin_save + sbit + end_save; //����fileName_save�ַ�����������洢ͼƬ��
		const char* fileName_save = sfileName_save.data(); //��string�����ַ���ת����char�����ַ�����

		ip.saveImageAs(fileName_save); //�������fileName_save����ΪͼƬ���洢��ͼ��

		ip.printHist(); //��ʾ��ӦͼƬ��ֱ��ͼ

		std::string sfileName_txt = begin_txt + sbit + end_txt; //����fileName_save�ַ�����������洢ͼƬ��
		const char* fileName_txt = sfileName_txt.data(); //��string�����ַ���ת����char�����ַ�����
		ip.saveAsFile(fileName_txt);

		system("cls"); //����
	}
	Sleep(1000); //��ͣ1s
	std::cout << "��ʾ���" << std::endl; //��ʾ���
	Sleep(1000); //��ͣ1s
	return 0; //����
}
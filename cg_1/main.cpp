#include "image.h"

int main()
{
	// ������ ������������� ������� ����������� � ���������� �����������
	Image image1;
	image1.isRead("D:/Downloads/11.jpg");
	// ... ��������� ����������� � ������� isRead()
	Image image2;
	image2.isRead("D:/Downloads/11.jpg");

	// ��������� ����������� �����������
	image1.equalizeHistogram();
	image1.isWrite("D:/Downloads/new_equal.png");

	// ��������� ����������� ���������� �����������
	image2.stretchHistogram();
	image2.isWrite("D:/Downloads/new_stretch.png");
}

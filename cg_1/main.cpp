#include "image.h"

int main()
{
	// Пример использования методов эквализации и растяжения гистограммы
	Image image1;
	image1.isRead("D:/Downloads/11.jpg");
	// ... Загрузить изображение с помощью isRead()
	Image image2;
	image2.isRead("D:/Downloads/11.jpg");

	// Применить эквализацию гистограммы
	image1.equalizeHistogram();
	image1.isWrite("D:/Downloads/new_equal.png");

	// Применить равномерное растяжение гистограммы
	image2.stretchHistogram();
	image2.isWrite("D:/Downloads/new_stretch.png");
}

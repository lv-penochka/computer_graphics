#include "image.h"
#include "Histogram.h"

int main() 
{
	using namespace ImageTransformation;

	Image image;
	std::cout << image.isRead("images/1.jpg");
	// ... Загрузить изображение с помощью isRead()

	Histogram hist{ image };

	// Применить эквализацию гистограммы
	auto eq = hist.generateEqualized();
	std::cout << eq.isWrite("images/eq.png");

	// Применить равномерное растяжение гистограммы
	auto st = hist.generateStretched();
	std::cout << st.isWrite("images/st.png");
}

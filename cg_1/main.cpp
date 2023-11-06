#include "image.h"
#include "Histogram.h"

int main() 
{
	Image<ColorTypeTrait8_t> image;
	std::cout << image.isRead("images/1.jpg");
	// ... Загрузить изображение с помощью isRead()

	Histogram<ColorTypeTrait8_t> hist{ image };
	hist.show();
	// Применить эквализацию гистограммы
	auto eq = hist.generateEqualized();
	std::cout << eq.isWrite("images/eq.png");
	Histogram<ColorTypeTrait8_t>(eq).show();

	// Применить равномерное растяжение гистограммы
	auto st = hist.generateStretched();
	std::cout << st.isWrite("images/st.png");
	Histogram<ColorTypeTrait8_t>(st).show();

}

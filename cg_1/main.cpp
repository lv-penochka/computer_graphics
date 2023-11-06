#include "image.h"
#include "Histogram.h"

int main() 
{
	Image<ColorTypeTrait8_t> image;
	std::cout << image.isRead("images/1.jpg");
	// ... ��������� ����������� � ������� isRead()

	Histogram<ColorTypeTrait8_t> hist{ image };
	hist.show();
	// ��������� ����������� �����������
	auto eq = hist.generateEqualized();
	std::cout << eq.isWrite("images/eq.png");
	Histogram<ColorTypeTrait8_t>(eq).show();

	// ��������� ����������� ���������� �����������
	auto st = hist.generateStretched();
	std::cout << st.isWrite("images/st.png");
	Histogram<ColorTypeTrait8_t>(st).show();

}

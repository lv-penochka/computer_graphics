#include "image.h"
#include "Histogram.h"

int main() 
{
	using namespace ImageTransformation;

	Image image;
	std::cout << image.isRead("images/1.jpg");
	// ... ��������� ����������� � ������� isRead()

	Histogram hist{ image };
	hist.show();
	// ��������� ����������� �����������
	auto eq = hist.generateEqualized();
	std::cout << eq.isWrite("images/eq.png");
	Histogram(eq).show();

	// ��������� ����������� ���������� �����������
	auto st = hist.generateStretched();
	std::cout << st.isWrite("images/st.png");
	Histogram(st).show();

}

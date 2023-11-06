#include "image.h"
#include "Histogram.h"

int main() 
{
	using namespace ImageTransformation;

	Image image;
	std::cout << image.isRead("images/1.jpg");
	// ... ��������� ����������� � ������� isRead()

	Histogram hist{ image };

	// ��������� ����������� �����������
	auto eq = hist.generateEqualized();
	std::cout << eq.isWrite("images/eq.png");

	// ��������� ����������� ���������� �����������
	auto st = hist.generateStretched();
	std::cout << st.isWrite("images/st.png");
}

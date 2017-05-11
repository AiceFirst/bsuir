#include <iostream>
#include <string.h>

using namespace std;

struct Cord
{
	int x;
	int y;
};

struct Rectangle
{
	Cord leftbottom;
	Cord righttop;
};


class Rectangles
{
public:
	Rectangles();
	Rectangles(Rectangle rect1, Rectangle rect2);
	~Rectangles();
	void Move(int number, int moveX, int moveY);	//������� ��������� �� ������ ������������� �� � ��� �
	void Resize(int number, int x1, int y1, int x2, int y2);		//������ ����� ���������� ��� ��������� ���������������
	Rectangle IntersectionRectangle();				//������� ����������� ���������������
	Rectangle UnionRectangle();						//������� ����������, ��� �������� ���
	void ViewRectangles();							//�������� ������� ���������������

private:
	Rectangle rectangles[2];
	void SwapRectangles();							//������ ��������������, ��� �� ������ ��� �����
};
#include <iostream>
#include "CVector2D.h"

void DumbStop();
void TestVector(CVector2D &TestingVector);

std::ostream& operator<<(std::ostream& OutputStream, const CVector2D& Vector)
{
	OutputStream << "< " << Vector.GetX() << ", " << Vector.GetY() << ">";
	return OutputStream;
}

int main() {

	DumbStop();
}



void TestVector(CVector2D & TestingVector)
{
	short Options = 0;
	printf("\n Testing vector chose operation");
	while (true)
	{
		switch (Options)
		{
		case 1:

			break;


		default:
			break;
		}
	}



}

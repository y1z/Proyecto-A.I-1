#pragma once
#include <iostream>


/*! To see the values of the vectors */
static std::ostream& operator<<(std::ostream& OutputStream, const CVector2D& Vector)
{
	OutputStream << "< " << Vector.GetX() << ", " << Vector.GetY() << ">";
	return OutputStream;
}

static void DumbStop()
{
	std::cin.ignore();
	std::cin.get();
}
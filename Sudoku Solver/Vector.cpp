#include "Vector.h"

Vector::Vector()
	:X(0),
	Y(0)
{
}
Vector::Vector(unsigned int X, unsigned int Y)
	:X(X),
	Y(Y)
{
}

Vector Vector::operator +(Vector One) const
{
	return Vector(this->X+One.X, this->Y+One.Y);
}
Vector Vector::operator -(Vector One) const
{
	return Vector(this->X-One.X, this->Y-One.Y);
}
void Vector::operator =(Vector One)
{
	this->X=One.X;
	this->Y=One.Y;
}
bool Vector::operator ==(Vector One) const
{
	return ((this->X==One.X) && (this->Y==One.Y));
}
bool Vector::operator !=(Vector One) const
{
	return !(*this==One);
}
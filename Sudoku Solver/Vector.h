#ifndef _VECTOR_H
#define _VECTOR_H

class Vector
{
public:
	Vector();
	Vector(unsigned int X, unsigned int Y);

	unsigned int X, Y;

	Vector operator +(Vector One) const;
	Vector operator -(Vector One) const;
	void operator =(Vector One);
	bool operator ==(Vector One) const;
	bool operator!=(Vector One) const;
};

#endif
/* supradefinirea operatorilor foosind functii prietene */
#include <iostream.h>
class complex {
	float re, im;
public:
	//cosntructor
	complex(float r = 0, float i = 0)
	{
		re = r;
		im = i;
	}
	void afisare()
	{
		cout << " re="<<re;
		cout << ",im="<<im<<"\n";
	}
	friend complex operator+(complex,complex);
};

complex operator+(complex a, complex b)
{
	complex c;
	c.re = a.re + b.re;
	c.im=a.im+b.im;
	return c;
}

void main()
{
	complex c1(1,1);
	c1.afisare();
	complex c2(2,2);
	c2.afisare();
	complex r1, r2;
	r1 = c1+c2;
	r1.afisare();
	r2 = c1 + c2 + r1;
	r2.afisare();
}
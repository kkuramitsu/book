#include"mymagic.h"

typedef struct Shape {
	double (*area)(struct Shape *this);
} Shape;

typedef struct Triangle {
	struct Shape super;
	double width;
	double height;
} Triangle;

typedef struct Circle {
	struct Shape super;
	double radius;
} Circle;

double Triangle_area(Triangle *this)
{
	return this->width * this->height / 2.0;
}

double Circle_area(Circle *this)
{
	return 3.14159 * this->radius * this->radius;
}

Triangle newTriangle(double w, double h) {
	Triangle *triangle = Tmalloc(Triangle);
	triangle->super.area = Triangle_area;
	triangle->height = w;
	triangle->width = h;
}
Circle new_Circle(double r) {
	Circle *circle = Tmalloc(Circle);
	circle->super.area = Circle_area;
	circle->radius = r;
	return circle;
}

int main()
{
	Shape *s1 = (Shape*)new_Triangle(10.0, 12.0);
	Shape *s2 = (Shape*)new_Circle(18.0);
	printf("%s: area=%f\n", Tname(s1), s1->area(s1));
	printf("%s: area=%f\n", Tname(s2), s2->area(s2));
	return 1;
}

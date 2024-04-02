#include "geo.h"

// -------point-------------

Point Point :: operator=(const Point& p) {
        x = p.x;
        y = p.y;
        return *this;
    }

Point :: Point(const Point& p){
        x = p.x;
        y = p.y;
    }

double Point::getX() const {
        return x;
    }

double Point::getY() const {
        return y;
    }
	
void Point::distanceBetweenPoints(const Point& other, double& d) const {
    double deltaX = other.getX() - x;
    double deltaY = other.getY() - y;
    d =  sqrt(deltaX * deltaX + deltaY * deltaY);
}
	
// --------circle-----------------------
	

Circle::Circle(const Point& c, double r) : center(c), radius(r) {}

Circle::Circle(const Circle& other){
        radius = other.radius;
        center = other.center;
    }

double Circle::getRadius() {
        return radius;
    }

Point Circle::getCenter() {
        return center;
    }

void Circle::findIntersection_circle(const Circle& other, Point& intersection1, Point& intersection2) const {
        // первая окружность с центром (0,0), вторая с центром (x2, y2)
        double a, b, c;
        a = -2 * (other.center.getX()-center.getX());
        b = -2 * (other.center.getY() - center.getY());
        c = (other.center.getX() - center.getX()) * (other.center.getX() - center.getX()) + (other.center.getY() - center.getY()) * (other.center.getY() - center.getY()) + radius*radius - other.radius*other.radius;

        double x0 = -a*c/(a*a+b*b),  y0 = -b*c/(a*a+b*b);

        double d = radius*radius - c*c/(a*a + b*b);
        double mult = sqrt(d / (a*a + b*b));
        intersection1 = Point(x0 + b * mult,y0 - a * mult);
        intersection2 = Point( x0 - b * mult, y0 + a * mult);
    }
	
void Circle::findIntersection_line(Line& line, Point& intersection1, Point& intersection2) const{
	
	double a, b, c;
    a = line.getA();
    b = line.getB();
    c = line.getC();
    double A = 1 + (a * a / (b * b));
    double B = center.getX() - (a * (center.getY() + c / b) / b);
    double C = pow((c / b + center.getY()), 2) - radius * radius + center.getX() * center.getX();
    double d = B * B - A * C;
    double x1 = (B + pow(d, 0.5)) / A;
    double x2 = (B - pow(d, 0.5)) / A;
    double y1 = ((a * x1) / b + c / b)*(-1);
    double y2 = ((a * x2) / b + c / b)*(-1);
    intersection1 = Point(x1, y1);
    intersection2 = Point(x2, y2);
}

Circle Circle :: operator =(const Circle& p) {
        radius = p.radius;
        center = p.center;
        return *this;
    }
	
	
//-----------line--------------------	
	
Line::Line(const Point& p1, const Point& p2){
	a = p2.getY() - p1.getY();
    b = p1.getX() - p2.getX();
    c = p2.getX() * p1.getY() - p1.getX() * p2.getY();
}

double Line::getA() const {
        return a;
}

double Line::getB() const {
        return b;
}

double Line::getC() const {
        return c;
}

Line::Line(const Line& other){
        a = other.a;
        b = other.b;
    }

void Line::per(const Point& A, const Point& B, const Point& D){
	
    Line AB(A, B);
	
    double dAD;
	A.distanceBetweenPoints(D, dAD);
     
    // Создаем окружность с центром в точке D и радиусом равным расстоянию между А и D
    Circle circleD(D,dAD) ;

  
    // Находим точки пересечения окружности D и прямой AB
    Point intersection1, intersection2;
	circleD.findIntersection_line(AB, intersection1, intersection2);
	cout << intersection1.getX() << "  " << intersection1.getY() << endl;
	cout << intersection2.getX() << "  " << intersection2.getY() << endl;
	
	// Находим расстояние между точками пересечения
	double d;
	intersection1.distanceBetweenPoints(intersection2, d);
	
	// Создаем окружности с центрами в точках пересечения и радиусом dAD
	Circle circleIntersection1(intersection1, dAD);
	Circle circleIntersection2(intersection2, dAD);
	

	// Находим точки пересечения этих окружностей
	Point finalIntersection1, finalIntersection2;
	
	circleIntersection1.findIntersection_circle(circleIntersection2, finalIntersection1, finalIntersection2);
	
	Line perpendicular(finalIntersection1, finalIntersection2);
	
	
	
	
	
	
	//----------print-----------
	
	ofstream file("file.txt");
	
	//file << "%point\n";
	file << D.getX() << " " << D.getY() << "\n";
	file << D.getX() << " " << D.getY() << "\n\n";
    
   
	//file << "%line_1\n";
	file << A.getX() << " " << A.getY() << "\n";
	file << B.getX() << " " << B.getY() << "\n\n";
	
	//file << "%circle1\n";
	double eps = 0.01;       
	int numPoints = static_cast<int>(2 * M_PI * dAD/ eps);
	for(int i = 0; i < numPoints; ++i){
		double angle = i * 2 * M_PI / numPoints;
		double x = D.getX() + dAD * cos(angle);
		double y = D.getY() + dAD * sin(angle);
		file << x << " " << y << "\n";
	}
	
	file << "\n";
	
	
	file << "\n";
	//file << "%circle2\n";

		
	numPoints = static_cast<int>(2 * M_PI * dAD / eps);
	for(int i = 0; i < numPoints; ++i){
		double angle = i * 2 * M_PI / numPoints;
		double x = intersection1.getX() + dAD * cos(angle);
		double y = intersection1.getY() + dAD * sin(angle);
		file << x << " " << y << "\n";
	}

	file << "\n";
	//file << "%circle3\n";
	
	numPoints = static_cast<int>(2 * M_PI * dAD / eps);
	for(int i = 0; i < numPoints; ++i){
		double angle = i * 2 * M_PI / numPoints;
		double x = intersection2.getX() + dAD * cos(angle);
		double y = intersection2.getY() + dAD * sin(angle);
		file << x << " " << y << "\n";
	}
	
	file << "\n";
	
	
	//file <<"%line2\n";
	file << finalIntersection1.getX() << "  " <<  finalIntersection1.getY()<< "\n";
	file << finalIntersection2.getX() << "  " <<  finalIntersection2.getY()<< "\n";
	file.close();
	
	
	
	
	
	
	
	
	/*
	ofstream file("file.txt");
	
	//file << "%point\n";
	file << D.getX() << " " << D.getY() << "\n";
	file << D.getX() << " " << D.getY() << "\n\n";
    
   
	//file << "%line_1\n";
	file << A.getX() << " " << A.getY() << "\n";
	file << B.getX() << " " << B.getY() << "\n\n";
	
	//file << "%circle1\n";
	double eps = 0.01;       
	int numPoints = static_cast<int>(2 * M_PI * dAD/ eps);
	for(int i = 0; i < numPoints; ++i){
		double angle = i * 2 * M_PI / numPoints;
		double x = D.getX() + dAD * cos(angle);
		double y = D.getY() + dAD * sin(angle);
		file << x << " " << y << "\n";
	}
	
	file << "\n";
	
	
	file << "\n";
	//file << "%circle2\n";

		
	numPoints = static_cast<int>(2 * M_PI * d / eps);
	for(int i = 0; i < numPoints; ++i){
		double angle = i * 2 * M_PI / numPoints;
		double x = intersection1.getX() + d * cos(angle);
		double y = intersection1.getY() + d * sin(angle);
		file << x << " " << y << "\n";
	}

	file << "\n";
	//file << "%circle3\n";
	
	numPoints = static_cast<int>(2 * M_PI * d / eps);
	for(int i = 0; i < numPoints; ++i){
		double angle = i * 2 * M_PI / numPoints;
		double x = intersection2.getX() + d * cos(angle);
		double y = intersection2.getY() + d * sin(angle);
		file << x << " " << y << "\n";
	}
	
	file << "\n";
	
	
	//file <<"%line2\n";
	file << finalIntersection1.getX() << "  " <<  finalIntersection1.getY()<< "\n";
	file << finalIntersection2.getX() << "  " <<  finalIntersection2.getY()<< "\n";  */
	file.close();
}

	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
/*
	
Line::Line(const Point& p1, const Point& p2) : point1(p1), point2(p2) {}

double Line::distanceBetweenPoints(const Point& pointA, const Point& pointB) const {
    double deltaX = pointB.getX() - pointA.getX();
    double deltaY = pointB.getY() - pointA.getY();
    return sqrt(deltaX * deltaX + deltaY * deltaY);
}

bool Line::intersectCircleLine(const Circle& circle, Point& intersection1, Point& intersection2) const {
   // Расчитываем коэффициенты уравнения прямой Ax + By + C = 0
    double A = point2.y - point1.y;
    double B = point1.x - point2.x;
    double C = point2.x * point1.y - point1.x * point2.y;

    // Расстояние от центра окружности до прямой
    double distance = fabs(A * circle.center.x + B * circle.center.y + C) / sqrt(A * A + B * B);

    // Проверяем, пересекается ли окружность с прямой
    if (distance > circle.radius) {
        return false; // Нет пересечения
    }

    // Находим координаты проекции центра окружности на прямую
    double projectionX = (B * (B * circle.center.x - A * circle.center.y) - A * C) / (A * A + B * B);
    double projectionY = (A * (-B * circle.center.x + A * circle.center.y) - B * C) / (A * A + B * B);

    // Находим точки пересечения
    double d = sqrt(circle.radius * circle.radius - distance * distance);
    intersection1.x = projectionX + d * B / sqrt(A * A + B * B);
    intersection1.y = projectionY - d * A / sqrt(A * A + B * B);
    intersection2.x = projectionX - d * B / sqrt(A * A + B * B);
    intersection2.y = projectionY + d * A / sqrt(A * A + B * B);

    return true;

}
















bool Circle::intersectCircles(const Circle& circle1, const Circle& circle2, Point& intersection1, Point& intersection2) const {
    // Расстояние между центрами окружностей
    double d = distanceBetweenPoints(circle1.center, circle2.center);

    if (d > circle1.radius + circle2.radius || d < fabs(circle1.radius - circle2.radius)) {
        // Окружности не пересекаются
        return false;
    }

    double a = (circle1.radius * circle1.radius - circle2.radius * circle2.radius + d * d) / (2.0 * d);
    double h = sqrt(circle1.radius * circle1.radius - a * a);

    // Находим точку пересечения отрезка, соединяющего центры окружностей
    double intersectionX = circle1.center.x + a * (circle2.center.x - circle1.center.x) / d;
    double intersectionY = circle1.center.y + a * (circle2.center.y - circle1.center.y) / d;

    // Находим две точки пересечения
    intersection1.x = intersectionX + h * (circle2.center.y - circle1.center.y) / d;
    intersection1.y = intersectionY - h * (circle2.center.x - circle1.center.x) / d;
    intersection2.x = intersectionX - h * (circle2.center.y - circle1.center.y) / d;
    intersection2.y = intersectionY + h * (circle2.center.x - circle1.center.x) / d;
	
    return true; 
}

*/




















/*





double Point::getX() const {
    return x;
}

double Point::getY() const {
    return y;
}

  double distanceBetweenPoints(const Point& pointA, const Point& pointB) {
    double deltaX = pointB.x - pointA.x;
    double deltaY = pointB.y - pointA.y;
    return sqrt(deltaX * deltaX + deltaY * deltaY);
}


  bool intersectCircleLine(const Circle& circle, const Line& line, Point& intersection1, Point& intersection2) {
    double A = line.point2.y - line.point1.y;
    double B = line.point1.x - line.point2.x;
    double C = line.point2.x * line.point1.y - line.point1.x * line.point2.y;

    double distance = abs(A * circle.center.x + B * circle.center.y + C) / sqrt(A * A + B * B);

    if (distance > circle.radius) {
        // Окружность и прямая не пересекаются
        return false;
    }

    // Находим координаты проекции центра окружности на прямую
    double projectionX = (B * (B * circle.center.x - A * circle.center.y) - A * C) / (A * A + B * B);
    double projectionY = (A * (-B * circle.center.x + A * circle.center.y) - B * C) / (A * A + B * B);

    // Находим две точки пересечения
    double d = sqrt(circle.radius * circle.radius - distance * distance);
    intersection1 = Point(projectionX + d * B / sqrt(A * A + B * B), projectionY - d * A / sqrt(A * A + B * B));
    intersection2 = Point(projectionX - d * B / sqrt(A * A + B * B), projectionY + d * A / sqrt(A * A + B * B));

    return true;
}



  bool intersectCircles(const Circle& circle1, const Circle& circle2, Point& intersection1, Point& intersection2) {
    double d = distanceBetweenPoints(circle1.center, circle2.center);

    if (d > circle1.radius + circle2.radius || d < abs(circle1.radius - circle2.radius)) {
        // Окружности не пересекаются
        return false;
    }

    double a = (circle1.radius * circle1.radius - circle2.radius * circle2.radius + d * d) / (2.0 * d);
    double h = sqrt(circle1.radius * circle1.radius - a * a);

    // Находим точку пересечения
    double intersectionX = circle1.center.x + a * (circle2.center.x - circle1.center.x) / d;
    double intersectionY = circle1.center.y + a * (circle2.center.y - circle1.center.y) / d;

    // Находим две точки пересечения (если окружности касаются, то они совпадут)
    intersection1 = Point(intersectionX + h * (circle2.center.y - circle1.center.y) / d, intersectionY - h * (circle2.center.x - circle1.center.x) / d);
    intersection2 = Point(intersectionX - h * (circle2.center.y - circle1.center.y) / d, intersectionY + h * (circle2.center.x - circle1.center.x) / d);

    return true;
}
*/
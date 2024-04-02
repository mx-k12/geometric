#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;


class Point {
private:
    double x, y;

public:
    Point() = default;
    Point(double trux, double truy) : x(trux), y(truy) {}
    Point(const Point& p);

    double getX() const;
    double getY() const;

    Point operator=(const Point& p);
    void distanceBetweenPoints(const Point& pointA, double& d) const;
};


class Line {
private:
    double a, b, c;

public:
    Line() = default;
    Line(const Point& p1, const Point& p2);
    Line(const Line& other);
    double getA() const;
    double getB() const;
    double getC() const;
    void per(const Point& A, const Point& B, const Point& D);

};

class Circle {
private:
    double radius;
    Point center;

public:
    Circle() = default;
    Circle(const Point& c, double r);
    Circle(const Circle& other);

    double getRadius();
    Point getCenter();

    Circle operator=(const Circle& p);

    void findIntersection_circle(const Circle& other, Point& intersection1, Point& intersection2) const;
    void findIntersection_line(Line& line, Point& intersection1, Point& intersection2) const;

};


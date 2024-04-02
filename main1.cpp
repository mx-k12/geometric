#include "geo.h"


int main() {
	
	Point D(2.0, 6.0); 
	Point A(-5.0, -5.0); 
    Point B(25.0, 23.0); 
	 Line AB(A, B);
	
	AB.per(A, B, D);
	
//	cout << finalIntersection1.getX() << "  " <<  finalIntersection1.getY()<< "\n";
	//cout << finalIntersection2.getX() << "  " <<  finalIntersection2.getY()<< "\n";
	//cout << perpendicular.getA() << "  " << perpendicular.getB() <<  "  " << perpendicular.getC();  
	//cout << dAB << "\n";
	
	return 0;
}











/* if (circleIntersection1.intersectCircles(circleIntersection1, circleIntersection2, finalIntersection1, finalIntersection2)) {
		cout << "Пересечение окружностей: (" << finalIntersection1.center.getX() << ", " << finalIntersection1.center.getY() << ") и (" << finalIntersection2.center.getX() << ", " << finalIntersection2.center.getY() << ")" << endl;
	} else {
		cout << "Окружности не пересекаются." << endl;
	}
    } else {
        cout << "Пересечение окружности и прямой не найдено." << endl;
    }
	
*/
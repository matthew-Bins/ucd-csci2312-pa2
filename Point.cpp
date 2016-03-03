//Matthew Bins
#include "Point.h"
#include<cmath>
#include <sstream>
using std::endl;

namespace Clustering {

	unsigned int Point::__idGen = 0;

	//constructor takes in one arguement
	Point::Point(int dimensions) {
		__dim = dimensions;
		__values = new double[dimensions];
		__id = __idGen++;

		for (int i = 0; i < __dim; ++i) {
			setValue(i, 0.0);
		}
	}

	//constructor takes in two arguements
	Point::Point(int dimensions, double* val) {
		__dim = dimensions;
		__values = val;
		__id = __idGen++;
	}
	
	//copy constructor
	Point::Point(const Point& point) {
		__id = point.__id;
		__dim = point.getDims();
		__values = new double[__dim];

		for (int i = 0; i < __dim; ++i)
			__values[i] = point.getValue(i);

	}

	//destructor
	Point::~Point() {
		delete[] __values;
	}

	int Point::getId() const { return __id; }
	int Point::getDims() const { return __dim; }
	void Point::setValue(int dimensions, double val) {
		__values[dimensions] = val;
	}
	double Point::getValue(int dimensions) const { return __values[dimensions]; }

	double Point::distanceTo(const Point& p) const {
		double answer = 0;

		for (int i = 0; i < __dim; ++i) {
			answer += pow((p.getValue(i) - __values[i]), 2);
		}

		return sqrt(answer);
	}

	Point& Point::operator=(const Point &p) {
		__id = p.getId();
		__dim = p.getDims();
		for (int i = 0; i < __dim; ++i)
			__values[i] = p.getValue(i);

		return *this;
	}

	double& Point::operator[](int index) { return __values[index]; }


	Point& Point::operator*=(double num) {
		for (int i = 0; i < __dim; ++i)
			__values[i] *= num;

		return *this;
	}

	Point& Point::operator/=(double num) {
		for (int i = 0; i < __dim; ++i)
			__values[i] /= num;

		return *this;
	}

	const Point Point::operator*(double num) const { return Point(*this) *= num; }

	const Point Point::operator/(double num) const { return Point(*this) /= num; }

	/////////////////////friend functions//////////////////////////

	Point &operator+=(Point& one, const Point& two) {
		for (int i = 0; i < one.getDims(); ++i)
			one[i] += two.getValue(i);

		return one;
	}

	Point &operator-=(Point& one, const Point& two) {
		for (int i = 0; i < one.getDims(); ++i)
			one[i] -= two.getValue(i);

		return one;
	}

	const Point operator+(const Point& one, const Point& two) { return Point(one) += two; }

	const Point operator-(const Point& one, const Point& two) { return Point(one) -= two; }

	bool operator==(const Point& one, const Point& two) {
		bool same = true;
		if (one.getId() != two.getId()) {
			return false;
		}
		else if (one.__dim == two.__dim) {
			for (int i = 0; i < one.getDims(); ++i)
				if (one.getValue(i) != two.getValue(i))
					same = false;
		}
		else
			return false;

		return same;
	}

	bool operator!=(const Point& one, const Point& two) { return !(one == two); }

	
	bool operator<(const Point& one, const Point& two) {

		for (int i = 0; i < one.getDims(); ++i)
			if (one.getValue(i) < two.getValue(i))
				return true;

		return false;
	}

	bool operator>(const Point& one, const Point& two) { return !(one < two); }

	bool operator<=(const Point& one, const Point& two) {

		for (int i = 0; i < one.getDims(); ++i)
			if (one.getValue(i) < two.getValue(i) || one.getValue(i) == two.getValue(i))
				return true;

		return false;
	}

	bool operator>=(const Point& one, const Point& two) {

		for (int i = 0; i < one.getDims(); ++i)
			if (one.getValue(i) > two.getValue(i) || one.getValue(i) == two.getValue(i))
				return true;

		return false;
	}

	std::ostream &operator<<(std::ostream& os, const Point& p) {
		int dis = p.getDims() - 1; 

		for (int i = 0; i < dis; ++i)
			os << p.__values[i] << ", ";
		os << p.getValue(dis) << endl;

		return os;
	}

	std::istream &operator>>(std::istream& in, Point& p) {
		double point;
		int index = 0;
		std::string line, spoint;

		while (std::getline(in, line)) {

			std::stringstream ss(line);
			while (std::getline(ss, spoint, ',')) {

				point = stod(spoint);
				p.setValue(index, point);
				++index;
			}
		}
		return in;
	}

}
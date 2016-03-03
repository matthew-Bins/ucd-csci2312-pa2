#include"Cluster.h"
#include <sstream>

namespace Clustering {

	LNode::LNode(const Point& p, LNodePtr n) : point(p), next(n) {}

	void Cluster::__del() {
		LNodePtr TheEnd = __points, next;

		for (int i = 0; i < __size; ++i) {
			next = TheEnd->next;
			delete TheEnd;
			TheEnd = next;
		}

	}

	void Cluster::__cpy(LNodePtr pts) {
		LNodePtr temp = pts;
		LNode *copy = new LNode(pts->point, nullptr);

		LNode *head = copy;
		temp = temp->next;

		while (temp != nullptr) {
			copy = copy->next = new LNode(temp->point, nullptr);
			temp = temp->next;
		}

		__points = head;
	}

	bool Cluster::__in(const Point &p) const {

		return false;
	}

	Cluster::Cluster() {
		__size = 0;
		__points = nullptr;

	}

	Cluster::Cluster(const Cluster& copy) {
		__size = copy.getSize();
		if (copy.__points != nullptr)
			__cpy(copy.__points);
	}

	Cluster& Cluster::operator=(const Cluster& c) {
		this->__size = c.__size;
		this->__cpy(c.__points);

		return *this;
	}

	Cluster::~Cluster() {
		__del();
	}

	int Cluster::getSize() const { return __size; }

	void Cluster::add(const Point& p) {
		LNode *Add = new LNode(p, nullptr);

		if (__points == nullptr){
			__points = Add;
			__size++;
			return;
		}
		else{
			LNodePtr temp = __points, prev = nullptr;

			while (temp != nullptr){
				if (p < temp->point){

					if (prev == nullptr){
						__points = Add;
						Add->next = temp;
						__size++;

						return;
					}
					else{
						prev->next = Add;
						Add->next = temp;
						__size++;
						return;
					}
				}
				prev = temp;
				temp = temp->next;
			}
			prev->next = Add;
			__size++;
		}
	}

	const Point& Cluster::remove(const Point& p) {
		int i = 0;
		bool found = false;
		LNodePtr temp = __points, prev = nullptr;

		if (temp == nullptr) {//no points in cluster
			return p;
		}

		if (temp->next == nullptr) {
			if (temp->point == p) {
				__size = 0;
				delete temp;
				__points = nullptr;
			}
		}
		else {
			prev = __points;
			temp = __points->next;

			if (__points->point == p) {
				__points = temp;
				--__size;
				delete prev, temp;
				return p;
			}

			for (; !found && temp != nullptr; temp = temp->next) {
				if (temp->point == p) {
					prev->next = temp->next;
					--__size;
					found = true;
					delete temp;
					return p;
				}

				prev = temp;
			}
		}

		return p;
	}

	bool Cluster::contains(const Point& p) {
		bool there = false;
		LNodePtr temp = __points;

		while (temp != nullptr) {
			if (temp->point == p)
				there = true;

			temp = temp->next;
		}

		return there;
	}

	const Point& Cluster::operator[](unsigned int index) const {
		this;
		LNodePtr temp = __points;
		if (__points != nullptr) {
			for (int i = 0; i < index; ++i)
				temp = temp->next;
		}
		return temp->point;
	}

	Cluster& Cluster::operator+=(const Point& p) {
		add(p);
		return *this;
	}

	Cluster& Cluster::operator-=(const Point& p) {
		remove(p);
		return *this;
	}

	Cluster& Cluster::operator+=(const Cluster& c) {
		LNodePtr temp = c.__points;

		while (temp != nullptr) {
			if (!(this->contains(temp->point)))
				add(temp->point);
			temp = temp->next;
		}
		return *this;
	}

	Cluster& Cluster::operator-=(const Cluster& c) {
		int size = c.getSize();

		for (int i = 0; i < size; ++i)
			if (this->contains(c[i]))
				this->remove(c[i]);

		return *this;
	}

	std::ostream& operator<<(std::ostream& os, const Cluster& c) {
		LNodePtr PT = c.__points;

		while (PT != nullptr) {
			os << PT->point;
			PT = PT->next;
		}
		return os;
	}

	std::istream& operator>>(std::istream& in, Cluster& c) {
		std::string line;
		int size;

		while (getline(in, line)) {
			size = count(line.begin(), line.end(), ',') + 1;
			Point *New = new Point(size);
			std::stringstream ss(line);
			ss >> *New;
			c.add(*New);
		}

		return in;
	}

	bool operator==(const Cluster& one, const Cluster& two) {
		LNodePtr oneptr = one.__points, twoptr = two.__points;

		if (one.__size == two.__size) {
			while (oneptr != nullptr) {
				if (oneptr->point != twoptr->point)
					return false;
				oneptr = oneptr->next;
				twoptr = twoptr->next;
			}
		}
		else
			return false;

		return true;
	}

	bool operator!=(const Cluster& one, const Cluster& two) { return !(one == two); }

	const Cluster operator+(const Cluster& c, const Point& p) {
		Cluster copy(c);
		copy.add(p);
		return copy;
	}

	const Cluster operator-(const Cluster& c, const Point& p) {
		Cluster copy(c);
		copy.remove(p);
		return copy;
	}

	const Cluster operator+(const Cluster& one, const Cluster& two) {
		Cluster c1(one);
		return c1 += two;
	}

	const Cluster operator-(const Cluster& one, const Cluster& two) {
		Cluster c1(one);
		return c1 -= two;
	}

}
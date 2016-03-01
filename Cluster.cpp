#include"Cluster.h"

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

	bool Cluster::__inn(const Point &p) const {

		return false;
	}

	Cluster::Cluster() {
		__size = 0;
		Point p(0);
		LNode *node = new LNode(p, nullptr);
		__points = node;

	}

	Cluster::Cluster(const Cluster& copy) {
		__size = copy.getSize();
		__cpy(copy.__points);
	}

	Cluster& Cluster::operator=(const Cluster& c) {
		this->__cpy(c.__points);

		return *this;
	}

	Cluster::~Cluster() {
		__del();
	}

	int Cluster::getSize() const { return __size; }

	void Cluster::add(const Point& point) {
		++__size;

		LNode *Add = new LNode(point, nullptr);
		LNodePtr temp = __points, prev = nullptr;

		if (__points == nullptr)
			__points = Add;
		else {
			while (temp != nullptr) {
				prev = temp;
				temp = temp->next;
			}
			Add->next = temp;
			prev->next = Add;
		}

	}

	const Point& Cluster::remove(const Point& p) {
		int i = 0;
		LNodePtr clust = __points, after = nullptr, prev = nullptr;

		prev = clust;
		while (clust != nullptr) {
			if (clust->point == p) {
				if (i == 0) {//delete the front
					after = clust->next;
					delete __points;
					__points = after;
					--__size;
					return p;
				}
				else {//delete the middle
					after = clust->next;
					delete clust;
					prev->next = after;
					--__size;
					return p;
				}
			}
			prev = clust;
			clust = clust->next;
			++i;
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
		LNodePtr temp = __points;

		for (int i = 0; i < index; ++i)
			temp = temp->next;

		return temp->point;
	}

	Cluster& Cluster::operator+=(const Point& p) {
		this->add(p);
		return *this;
	}

	Cluster& Cluster::operator-=(const Point& p) {
		this->remove(p);
		return *this;
	}

	Cluster& Cluster::operator+=(const Cluster& c) {
		int size = c.getSize();

		for (int i = 0; i < size; ++i)
			if (!this->contains(c[i]))
				this->add(c[i]);

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
			os << PT->point << std::endl;
			PT = PT->next;
		}

		return os;
	}

	std::istream& operator>>(std::istream& in, Cluster& c) {


		return in;
	}

	bool operator==(const Cluster& one, const Cluster& two) {
		LNodePtr oneptr = one.__points, twoptr = two.__points;
		while (oneptr != nullptr) {
			if (oneptr->point != twoptr->point)
				return false;
			oneptr = oneptr->next;
			twoptr = twoptr->next;
		}

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


		return one;
	}

	const Cluster operator-(const Cluster& one, const Cluster& two) {


		return one;
	}

}
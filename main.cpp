#include <cstddef>
#include <fstream>

#include "stack.hpp"
#include "priority_queue.hpp"

struct point {
	int x, y;
};

point p0;

void swap(point &a, point &b)
{
	int tmp = a.x;
	a.x = b.x;
	b.x = tmp;

	tmp = a.y;
	a.y = b.y;
	b.y = tmp;
}

std::size_t distance_square(const point& a, const point& b)
{
	return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

// -1 - clockwise orientation (right turn);
//  0 - collinear;
//  1 - counter-clockwise orientation (left turn).
int ccw(const point& a, const point& b, const point& c)
{
	int cross_product = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
	return cross_product > 0 ? 1 : cross_product < 0 ? -1 : 0;
}

struct compare {
	bool operator()(const point& a, const point& b)
	{
		int orientation = ccw(p0, a, b);

		if (orientation == 0)
			return distance_square(p0, a) < distance_square(p0, b);

		return (orientation == 1);
	}
};

point& next_to_top(lab::stack<point>& s)
{
	point tmp = s.top();
	s.pop();
	point& result = s.top();
	s.push(tmp);
	return result;
}

std::vector<point> convex_hull(std::vector<point> points)
{
	std::size_t n = points.size();

	if (n < 3)
		return points;

	// Find the pivot.
	std::size_t lowest = 0;

	for (std::size_t i = 1; i < n; i++)
		if (points[i].y < points[lowest].y ||
			(points[i].y == points[lowest].y && points[i].x < points[lowest].x))
			lowest = i;

	std::iter_swap(points.begin(), points.begin() + lowest);
	p0 = points[0];

	// Sort points by polar angle with p0.
	lab::priority_queue<point, std::vector<point>, compare> pq(points.begin() + 1, points.end());

	lab::stack<point> s;

	s.push(p0);

	s.push(pq.top());
	pq.pop();

	// Pop the last point from the stack if we don't turn counter-clockwise to reach this point.
	for (std::size_t i = 2; i < n; i++) {
		while (ccw(next_to_top(s), s.top(), pq.top()) != 1)
			s.pop();

		s.push(pq.top());
		pq.pop();
	}

	n = s.size();

	points.clear();
	for (std::size_t i = 0; i < n; i++) {
		points.push_back(s.top());
		s.pop();
	}

	return points;
}

int main()
{
	std::vector<point> points;

	std::ifstream in("points.txt");
	int x, y;
	while (in >> x >> y) {
		points.push_back({ x, y });
	}
	in.close();

	std::vector<point> result = convex_hull(points);

	std::ofstream out("convex_hull.txt");
	for (auto i = result.begin(); i != result.end(); i++) {
		out << (*i).x << " " << (*i).y << std::endl;
	}
	out.close();

	return 0;
}

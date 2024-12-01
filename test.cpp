#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

struct Point
{
    int x, y;
    bool operator<(const Point& other) const
    {
        return (x != other.x) ? x < other.x : y < other.y;
    }
};

struct Vector { long long i, j; };

Vector make_vector(Point p1, Point p2)
{ // return a vector from p1 to p2
    Vector v;
    v.i = p2.x - p1.x;
    v.j = p2.y - p1.y;
    return v;
}

    long long cross_product(Vector a, Vector b)
    { // return coefficient of k of cross product of two 2d vectors v1, v2
        return (a.i * b.j) - (a.j * b.i);
    } // clockwise < linear dependent(0) < counter-clockwise

void quickhull(vector<Point>& points, Point p1, Point p2, vector<Point>& hull)
{
    if (points.size() == 0) return;

    Point furthest = points[0];
    long long biggest_k = -1, k; // size of parallelogram
    Vector a = make_vector(p1, p2);
    for (auto p : points)
    {
        k = cross_product(a, make_vector(p1, p));
        if (biggest_k < k)
        {
            furthest = p;
            biggest_k = k;
        }
    }
    hull.push_back(furthest);

    vector<Point> s1, s2;
    for (auto& p : points)
    {
        if (0 < cross_product(make_vector(p1, furthest), make_vector(p1, p)))
            s1.push_back(p);
        else if (0 < cross_product(make_vector(furthest, p2), make_vector(furthest, p)))
            s2.push_back(p);
    }

    quickhull(s1, p1, furthest, hull);
    quickhull(s2, furthest, p2, hull);
}

int main(void)
{
    int N; cin >> N;
    vector<Point> points(N);
    for (int i = 0; i < N; i++)
    {
        cin >> points[i].x >> points[i].y;
    }

    sort(points.begin(), points.end());
    Point x_min = points.front();
    Point x_max = points.back();

    vector<Point> upper, lower;
    for (auto p : points)
    {
        long long k = cross_product(make_vector(x_min, x_max), make_vector(x_min, p));
        if (0 < k) upper.push_back(p);
        else if (k < 0) lower.push_back(p);
    }

    vector<Point> hull;
    hull.push_back(x_min);
    hull.push_back(x_max);
    quickhull(upper, x_min, x_max, hull);
    quickhull(lower, x_max, x_min, hull);

    cout << hull.size() << endl;
    return 0;
}
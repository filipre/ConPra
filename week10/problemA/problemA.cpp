#include <iostream>
#include <vector>
#include <set>
#include <cstdint>
#include <stack>
#include <queue>
#include <algorithm>
#include <functional>
#include <string>
#include <map>
#include <cmath>
#include <random>

struct Point
{
    double x;
    double y;
};

struct Line
{
    Point p1;
    Point p2;
};

typedef std::vector<Line> polygon_t;

const double epsilon = std::numeric_limits<double>::epsilon();

bool getIntersection(const Line &l1, const Line &l2, Point &p)
{
    // TODO add checks
    double denominator = (l1.p2.y - l1.p1.y) * (l2.p2.x - l2.p1.x) - (l1.p2.x - l1.p1.x) * (l2.p2.y - l2.p1.y);
    // std::cout << denominator <<  "\n";
    if (std::abs(0 - denominator) < epsilon)
    {
        return false;
    }

    double counterP_x = (l1.p2.x - l1.p1.x) * (l2.p1.x * l2.p2.y - l2.p2.x * l2.p1.y) - (l2.p2.x - l2.p1.x) * (l1.p1.x * l1.p2.y - l1.p2.x * l1.p1.y);
    double counterP_y = (l1.p2.y - l1.p1.y) * (l2.p1.x * l2.p2.y - l2.p2.x * l2.p1.y) - (l2.p2.y - l2.p1.y) * (l1.p1.x * l1.p2.y - l1.p2.x * l1.p1.y);

    double p_x = counterP_x / denominator;
    double p_y = counterP_y / denominator;

    p = {p_x, p_y};
    return true;
}

double generateRandomValue(double a, double b)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<> dis(a, b);
    return dis(gen);
}

Line generateRandomRay(Point p)
{
    // point r lies on the unit ball with Linf norm
    Point r { p.x + generateRandomValue(-1, 1), p.y + generateRandomValue(-1, 1) };

    // scale r such that coordinates are either < -1000 or > 1000
    r = { r.x, r.y };
    return { p, r };
}

bool pointOnSegmnet(const Point &p, const Line &l)
{
    // double left = (p.y - l.p1.y) * (l.p2.x - l.p1.x);
    // double right = (p.x - l.p1.x) * (l.p2.y - l.p1.y);
    // std::cout << "left: " << left << ", right: " << right << "\n";
    // return (std::abs(left - right) < epsilon);
    return ((l.p1.x <= p.x && p.x <= l.p2.x) || (l.p2.x <= p.x && p.x <= l.p1.x))
        && ((l.p1.y <= p.y && p.y <= l.p2.y) || (l.p1.y <= p.y && p.y <= l.p2.y));
}

bool pointInsidePolygon(Point &p, polygon_t &polygon)
{
    Line ray = generateRandomRay(p);
    // int intersections = 0;
    for (const auto &line : polygon)
    {
        std::cout << line.p1.x << ":" << line.p1.y << " - " << line.p2.x << ":" << line.p2.y << "\n";
        Point potentialPoint;
        bool intersects = getIntersection(ray, line, potentialPoint);
        if (intersects)
        {
            std::cout << "intersection: " << potentialPoint.x << ":" << potentialPoint.y << "\n";
        }

        // // this gives us some potentials intersections.
        // if (getIntersection(ray, line, potentialPoint))
        // {
        //     std::cout << "this could be a point: \n";
        //     std::cout << potentialPoint.x << " : " << potentialPoint.y << "\n";
        //
        //     // check that the intersection lies on the given line
        //     if (pointOnLine(potentialPoint, line))
        //     {
        //         std::cout << "indeed it is\n";
        //     }
        // }
    }
    return false;
}

int main()
{
    std::ios_base::sync_with_stdio(false);

    Point a { 0.0, 1.0 };
    Point b { 1.0, 0.0 };
    Point c { 3.0, 0.0 };
    Point d { 4.0, 1.0 };

    Line l1 { b, a };
    Line l2 { d, c };

    Point p;
    std::cout << getIntersection(l1, l2, p) << "\n";
    std::cout << p.x << " " << p.y << "\n";

    // int t;
    // std::cin >> t;
    //
    // for (int testCase=1; testCase<=t; ++testCase)
    // {
    //     std::cout << "Case #" << testCase << ": ";
    //     std::cout << "\n";
    //
    //     double xImpact, yImpact;
    //     std::cin >> xImpact;
    //     std::cin >> yImpact;
    //     Point impact { xImpact, yImpact };
    //
    //     int n;
    //     std::cin >> n;
    //
    //     polygon_t polygon;
    //     for (int i=1; i<=n; ++i)
    //     {
    //         double fromX, fromY, toX, toY;
    //         std::cin >> fromX;
    //         std::cin >> fromY;
    //         std::cin >> toX;
    //         std::cin >> toY;
    //         Point from { fromX, fromY };
    //         Point to { toX, toY };
    //         Line l { from, to };
    //         polygon.push_back(l);
    //     }
    //
    //     pointInsidePolygon(impact, polygon);
    // }

    return 0;
}

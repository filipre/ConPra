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
#include <iomanip>

const double epsilon = std::numeric_limits<double>::epsilon();

struct Point
{
    double x;
    double y;
};

// <a, b> = b^T a
double dot(Point a, Point b)
{
    return (b.x * a.x + b.y * a.y);
}

double det(Point a, Point b)
{
    return (a.x * b.y - a.y * b.x);
}

// on the line: 0
// left: > 0
// right: < 0
double ccw(Point a, Point b, Point p)
{
    return (p.y - a.y) * (b.x - a.x) - (p.x - a.x) * (b.y - a.y);
}

void calcConvexHull(std::vector<Point> points, std::vector<Point> &H)
{
    // Step 0: If points is emptz, return empty vector
    if (points.empty())
    {
        return;
    }

    // Step 1: Get lowest element
    Point minPoint = points[0];
    for (const auto &p : points)
    {
        if (p.x < minPoint.x)
        {
            minPoint = p;
        }
        else if (std::abs(p.x - minPoint.x) < epsilon)
        {
            if (p.y < minPoint.y)
            {
                minPoint = p;
            }
        }
    }

    // std::cout << "minPoint: " << minPoint.x << ":" << minPoint.y << "\n";

    // Step 2: Calculate scalar product ("angle") of each other point to min point and sort it accordingly
    sort(points.begin(), points.end(), [minPoint](const Point& lhs, const Point& rhs)
    {
        Point lhsPrime = { lhs.x - minPoint.x, lhs.y - minPoint.y };
        Point rhsPrime = { rhs.x - minPoint.x, rhs.y - minPoint.y };
        Point yVector = { 0.0, 1.0 };

        double angleLhs = std::atan2(det(lhsPrime, yVector), dot(lhsPrime, yVector));
        double angleRhs = std::atan2(det(rhsPrime, yVector), dot(rhsPrime, yVector));

        return angleLhs < angleRhs;
    });

    // for (const auto &p : points)
    // {
    //     std::cout << p.x << ":" << p.y << "\n";
    // }

    // Step 3: points is our stack Q, use empty stack H
    H[0] = points[0];
    H[1] = points[1];
    int h = 1;

    for (int i=2; i<points.size(); ++i)
    {
        // std::cout << "i: " << i << "\n";
        while (ccw(H[h-1], H[h], points[i]) >= 0.0)
        {
            // std::cout << " ... ";
            h = h - 1;
        }
        H[h+1] = points[i];
        h = h + 1;
    }

    // std::cout << "n: " << points.size() << "\n";
    // std::cout << "h: " << h << "\n";
    if (h > 2)
        H.resize(h+1); // TODO off plus one?

    // std::cout << "did not works\n";
}

// http://www.geeksforgeeks.org/area-of-a-polygon-with-given-n-ordered-vertices/
double calcAreaOfPolygon(std::vector<Point> &points)
{
    double area = 0.0;
    int j = points.size() - 1;
    for (int i=0; i<points.size(); i++)
    {
        area += (points[j].x + points[i].x) * (points[j].y - points[i].y);
        j = i;  // j is previous vertex to i
    }

    return std::abs(area / 2.0);
}

double calcConvexArea(std::vector<Point> points)
{
    // Step 1: Calculate Convex hull of points
    std::vector<Point> extremePoints (points.size(), { 0.0, 0.0 });
    calcConvexHull(points, extremePoints);
    // for (auto p : extremePoints)
    // {
    //     std::cout << p.x << ":" << p.y << "\n";
    // }

    // Step 2: Calculate area of convex polygon
    double area = calcAreaOfPolygon(extremePoints);

    // Step 3: Multiply area with 2 meters
    return area * 2.0;
}

int main()
{
    std::ios_base::sync_with_stdio(false);

    int t;
    std::cin >> t;

    for (int testCase=1; testCase<=t; ++testCase)
    {
        std::cout << "Case #" << testCase << ": ";
        // std::cout << "\n";

        int n;
        std::cin >> n;

        std::vector<Point> points;

        for (int i=1; i<=n; ++i)
        {
            double x_i, y_i;
            std::cin >> x_i;
            std::cin >> y_i;
            points.push_back({ x_i, y_i });
        }

        std::cout << std::setprecision(9) << calcConvexArea(points) << "\n";
    }

    return 0;
}

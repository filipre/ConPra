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














// https://en.wikibooks.org/wiki/Algorithm_Implementation/Geometry/Convex_hull/Monotone_chain#C.2B.2B


using namespace std;

typedef double coord_t;         // coordinate type
typedef double coord2_t;  // must be big enough to hold 2*max(|coordinate|)^2

struct Point {
	coord_t x, y;

	bool operator <(const Point &p) const {
		return x < p.x || (x == p.x && y < p.y);
	}
};

// 2D cross product of OA and OB vectors, i.e. z-component of their 3D cross product.
// Returns a positive value, if OAB makes a counter-clockwise turn,
// negative for clockwise turn, and zero if the points are collinear.
coord2_t cross(const Point &O, const Point &A, const Point &B)
{
	return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}

// Returns a list of points on the convex hull in counter-clockwise order.
// Note: the last point in the returned list is the same as the first one.
vector<Point> convex_hull(vector<Point> P)
{
	int n = P.size(), k = 0;
	if (n == 1) return P;
	vector<Point> H(2*n);

	// Sort points lexicographically
	sort(P.begin(), P.end());

	// Build lower hull
	for (int i = 0; i < n; ++i) {
		while (k >= 2 && cross(H[k-2], H[k-1], P[i]) <= 0) k--;
		H[k++] = P[i];
	}

	// Build upper hull
	for (int i = n-2, t = k+1; i >= 0; i--) {
		while (k >= t && cross(H[k-2], H[k-1], P[i]) <= 0) k--;
		H[k++] = P[i];
	}

	H.resize(k-1);
	return H;
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
    // std::vector<Point> extremePoints (points.size(), { 0.0, 0.0 });
    std::vector<Point> convexHull = convex_hull(points);
    // for (auto p : extremePoints)
    // {
    //     std::cout << p.x << ":" << p.y << "\n";
    // }

    // Step 2: Calculate area of convex polygon
    double area = calcAreaOfPolygon(convexHull);

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

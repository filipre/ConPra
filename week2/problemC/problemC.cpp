#include <iostream>
#include <vector>

// http://stackoverflow.com/questions/8300125/union-find-data-structure
class UF {
    int *id, cnt, *sz;
public:
    // Create an empty union find data structure with N isolated sets.
    UF(int N) {
        cnt = N; id = new int[N]; sz = new int[N];
        for (int i = 0; i<N; i++)  id[i] = i, sz[i] = 1; }
    ~UF() { delete[] id; delete[] sz; }

    // Return the id of component corresponding to object p.
    int find(int p) {
        int root = p;
        while (root != id[root])    root = id[root];
        while (p != root) { int newp = id[p]; id[p] = root; p = newp; }
        return root;
    }
    // Replace sets containing x and y with their union.
    void merge(int x, int y) {
        int i = find(x); int j = find(y); if (i == j) return;
        // make smaller root point to larger one
        if (sz[i] < sz[j]) { id[i] = j, sz[j] += sz[i]; }
        else { id[j] = i, sz[i] += sz[j]; }
        cnt--;
    }
    // Are objects x and y in the same set?
    bool connected(int x, int y) { return find(x) == find(y); }
    // Return the number of disjoint sets.
    int count() { return cnt; }
};


int main()
{
    std::ios_base::sync_with_stdio(false);

    int t;
    std::cin >> t;

    for (int testCase=1; testCase <= t; ++testCase)
    {
        int n;
        std::cin >> n;

        UF countries(n+1); // don't use element 0. never.
        //std::cout << "Parties: " << countries.count() - 1 << '\n';

        int m;
        std::cin >> m;

        char relation;
        int x, y;

        std::vector<int> antipathy(n+1); // default init with 0

        for (int i=0; i<m; ++i)
        {
            std::cin >> relation;
            std::cin >> x;
            std::cin >> y;

            if (relation == 'F')
            {
                // F x y
                //countries.merge(x, y);
                // TODO update graph
                int xRep = countries.find(x);
                int yRep = countries.find(y);

                if (antipathy[xRep] == 0 && antipathy[yRep] == 0)
                {
                    // just merge them...
                    countries.merge(xRep, yRep);
                }
                else if (antipathy[xRep] != 0 && antipathy[yRep] == 0)
                {
                    countries.merge(xRep, yRep);
                    antipathy[yRep] = antipathy[xRep];
                }
                else if (antipathy[xRep] == 0 && antipathy[yRep] != 0)
                {
                    countries.merge(xRep, yRep);
                    antipathy[xRep] = antipathy[yRep];
                }
                else
                {
                    countries.merge(xRep, yRep);
                    countries.merge(antipathy[xRep], antipathy[yRep]);
                }

            } else {
                // A x y
                // get representative of x and y
                // TODO necessary?
                int xRep = countries.find(x);
                int yRep = countries.find(y);

                // case 1: both do not hate others so far...
                if (antipathy[xRep] == 0 && antipathy[yRep] == 0)
                {
                    // now they hate each other at least
                    antipathy[xRep] = yRep;
                    antipathy[yRep] = xRep;
                }
                else if (antipathy[xRep] != 0 && antipathy[yRep] == 0)
                {
                    // xRep hates someone already but yRep does not.
                    // we need to merge yRep with that someone xRep hates!
                    countries.merge(yRep, antipathy[xRep]);
                    antipathy[yRep] = xRep;
                }
                else if (antipathy[xRep] == 0 && antipathy[yRep] != 0)
                {
                    countries.merge(xRep, antipathy[yRep]);
                    antipathy[xRep] = yRep;
                }
                else
                {
                    // both are not zero
                    countries.merge(yRep, antipathy[xRep]);
                    countries.merge(xRep, antipathy[yRep]);
                    // no need to update anything in the antipathy graph since all numbers will point to the right set
                }
            }

            //std::cout << "antipathy: ";
            // for (int i=1; i<n+1; ++i)
            //     std::cout << antipathy[i] << " ";
            // std::cout << "\n";

            //std::cout << "Parties: " << countries.count() - 1 << '\n';
        }

        // now we have an antipathy list.
        int counter=0;
        for(int i=1; i<n+1; ++i)
            if (countries.connected(1, i))
                ++counter;
        int half = n/2;

        if (counter > half)
            std::cout << "Case #" << testCase << ": yes" << '\n';
        else
            std::cout << "Case #" << testCase << ": no" << '\n';
    }

    return 0;
}

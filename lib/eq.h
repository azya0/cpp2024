#include <iostream>
#include <vector>
#include <map>
#include <cmath>


class Coef {
    public:
        double a, b, c;

        Coef(double const a, double const b, double const c);
};


class Eq {
    private:
        static std::vector<double> solveQuadro(Coef coef);
        static double solveLine(Coef coef);
    public:
        static std::vector<double> solve(Coef coef);
        static void print(std::vector<double> roots);
};
#include "eq.h"

Coef::Coef(double const _a, double const _b, double const _c) {
    a = _a;
    b = _b;
    c = _c;
}


std::vector<double> Eq::solveQuadro(Coef coef) {
    auto result = std::vector<double>();

    double const D = coef.b * coef.b - 4.0 * coef.a * coef.c; 

    if (D == 0) {
        result.push_back(-coef.b / 2 / coef.a);
    } else if (D > 0) {
        result.push_back((sqrt(D) - coef.b) / 2 / coef.a);
        result.push_back((-sqrt(D) - coef.b) / 2 / coef.a);
    }

    return result;
}


double Eq::solveLine(Coef coef) {
    return -coef.c / coef.b;
}


std::vector<double> Eq::solve(Coef coef) {
    if (coef.a != 0)
        return solveQuadro(coef);
    
    if (coef.b != 0)
        return std::vector<double>{ Eq::solveLine(coef) };

    return std::vector<double>();
}

void Eq::print(std::vector<double> roots) {
    switch (roots.size()) {
        case 0:
            std::cout << "No roots.";
            break;
        case 1:
            std::cout << "X = " << roots[0];
            break;
        case 2:
            for (int index = 0; index < 2; index++)
                std::cout << "X" << index + 1 << " = " << roots[index] << ((index == 0) ? "\n" : "");
            break;
        default:
            std::cout << "Error!";
            break;
    }
}
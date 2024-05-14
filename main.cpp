#include "lib/eq.h"


void print(std::vector<double> data) {
    switch (data.size()) {
        case 0:
            std::cout << "No roots";
            break;
        case 1:
            std::cout << "x = " << data[0];
            break;
        case 2:
            std::cout << "x1 = " << data[0] << '\n' << "x2 = " << data[1];
            break;
        default:
            std::cout << "Error! Array length is " << data.size();
            break;
    }
}


void print() {
    std::cout << '\n';
}


int main() {
    print(Eq::solve({ 1, 12, 1 }));
    print();
    print(Eq::solve({ 1, 2, 1 }));
    print();
    print(Eq::solve({ 0, 2, 3 }));
    print();
    print(Eq::solve({ 0, 0, 3 }));

    return 0;
}

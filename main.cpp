#include <iostream>
#include "professor/professor.h"

#include <map>

int main() {
    srand(time(NULL));

    Professor professor;
    std::vector<BadStudent*> group = {
        (BadStudent*)(new GoodStudnet("Hoai", "Thu", "Chin' Thi")),
        (BadStudent*)(new OrdinaryStudent("Nikita", "Drekalov", "Sergeevich")),
        (BadStudent*)(new OrdinaryStudent("Artur", "Zaidiev", "Il'gizovich")),
        (BadStudent*)(new OrdinaryStudent("Stanislav", "Egorkin")),
        (BadStudent*)(new OrdinaryStudent("Michail", "Tkachev")),
        (BadStudent*)(new BadStudent("Artyon", "Sokolov", "Hikolaevich"))
    };

    for (auto task : professor.getTasks()) {
        for (auto student : group) {
            BaseAnswer* answer = student->solveTask(task);

            professor.check(task, answer);

            delete answer;
        }
    }

    professor.printResults();

    return 0;
}

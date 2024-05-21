#include <vector>
#include <map>
#include <fstream>
#include <iostream>
#include "../student/student.h"

class Professor {
private:
    std::map<Task*, BaseAnswer*> tasksTable;
    std::map<BaseStudent*, int> studentTable;

public:
    Professor();

    ~Professor();

    std::vector<Task*> const getTasks();

    void const check(Task* const task, BaseAnswer* const answer);

    void const printResults();
};
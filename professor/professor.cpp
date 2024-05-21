#include "professor.h"

Professor::Professor() {
    std::ifstream fileTasks("../data/tasks.txt");
    std::ifstream fileAnswers("../data/answers.txt");

    if (!fileTasks.is_open() || !fileAnswers.is_open())
        throw std::runtime_error("Professor is ill.");
    
    std::map<int, std::vector<float>> answers;
    int id;
    float value;

    while (!fileAnswers.eof()) {
        fileAnswers >> id >> value;

        auto entry = answers.find(id);

        if (entry == answers.end())
            answers[id] = std::vector<float>({value});
        else
            entry->second.push_back(value);
    }

    fileAnswers.close();

    int counter = 1;
    while (!fileTasks.eof()) {
        std::string equation;
        getline(fileTasks, equation);
        auto* task = new Task(counter, equation);

        auto found = answers.find(counter);
        BaseAnswer* answer;

        if (found == answers.end())
            answer = new BaseAnswer(equation);
        else if (found->second.size() == 1)
            answer = new AnswerWithSingleRoot(equation, found->second[0]);
        else
            answer = new AnswerWithDoubleRoots(equation, found->second[0], found->second[1]);
        
        tasksTable[task] = answer;
        counter++;
    }

    fileTasks.close();
}

Professor::~Professor() {
    for (auto data : tasksTable) {
        delete data.first;
        delete data.second;
    }
}

std::vector<Task*> const Professor::getTasks() {
    std::vector<Task*> tasks;

    for (auto data : tasksTable)
        tasks.push_back(data.first);
    
    return tasks;
}

void const Professor::check(Task* const task, BaseAnswer* const answer) {
    if (task->getEquation() != answer->getEquation())
        return;

    auto student = answer->getAuthor();

    if (student == nullptr)
        return;

    auto foundTask = tasksTable.find(task);

    if (foundTask == tasksTable.end())
        return;

    auto foundStudent = studentTable.find(student);

    if (foundStudent == studentTable.end()) {
        studentTable[student] = 0;
    }

    if (!(*answer == foundTask->second))
        return;
    
    studentTable[student] += 1;
}

void const Professor::printResults() {
    for (auto data : studentTable) {
        std::cout << data.first->getSecondName() << ' ';
        std::cout << data.first->getFirstName();
        if (data.first->isHasPatronymic())
            std::cout << ' ' << data.first->getPatronymic();
        std::cout << " : " << data.second << '\n';
    }
}

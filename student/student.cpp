#include <fstream>
#include "student.h"
#include <iostream>

BaseAnswer* solveRight(Task* task) {
    // Представим, что те, кто знают ответ правильно на столько умны,
    // что им даже считать ничего не приходится, они просто ведают.

    std::ifstream file("../data/answers.txt");

    if (!file.is_open())
        return nullptr;
    
    std::vector<float> rightAnswer;
    int id = -1, taskId = task->getTaskId();
    float value;

    while ((id <= taskId) && (!file.eof())) {
        file >> id >> value;

        if (id != taskId)
            continue;
        
        rightAnswer.push_back(value);
    }

    file.close();

    switch (rightAnswer.size()) {
    case 0:
        return new BaseAnswer(task->getEquation());
        break;
    case 1:
        return new AnswerWithSingleRoot(task->getEquation(), rightAnswer[0]);
        break;
    default:
        return new AnswerWithDoubleRoots(task->getEquation(), rightAnswer[0], rightAnswer[1]);
        break;
    }
}

BaseAnswer::BaseAnswer() {
    data = std::vector<float>();
}

BaseAnswer::BaseAnswer(std::string _equation) : BaseAnswer() {
    equation = _equation;
}

std::vector<float> BaseAnswer::getData() {
    return data;
}

std::string BaseAnswer::getEquation() {
    return equation;
}

void BaseAnswer::addError() {
    for (int index = 0; index < data.size(); index++) {
        data[index] = data[index] + (float)((rand() % 1001) - 500) / 500;
    }
}

void const BaseAnswer::print() {
    if (author != nullptr) {
        std::cout << author->getSecondName() << ' ';
        std::cout << author->getFirstName();
        if (author->isHasPatronymic())
            std::cout << ' ' << author->getPatronymic();
        std::cout << ":\n";
    } else {
        std::cout << "anonymous:" << '\n';
    }

    std::cout << equation << "\n\n";

    if (data.empty())
        std::cout << "No roots.";

    for (int index = 0; index < data.size(); index++) {
        if (index != 0)
            std::cout << '\n';

        std::cout << 'x' << index + 1 << " = " << data[index];
    }

    std::cout << '\n';
}

bool BaseAnswer::operator==(BaseAnswer &answer) {
    auto otherData = answer.getData();

    if (data.size() != otherData.size())
        return false;
    
    for (int index = 0; index < data.size(); index++) {
        if (data[index] != otherData[index])
            return false;
    }

    return true;
}

bool BaseAnswer::operator==(BaseAnswer* const answer) {
    return operator==(*answer);
}

void BaseAnswer::setAuthor(BaseStudent* _author) {
    author = _author;
}

BaseStudent* const BaseAnswer::getAuthor() {
    return author;
}

AnswerWithDoubleRoots::AnswerWithDoubleRoots(std::string _equation, float x1, float x2) : BaseAnswer(_equation) {
    data.push_back(x1);
    data.push_back(x2);
}

AnswerWithSingleRoot::AnswerWithSingleRoot(std::string _equation, float x1) : BaseAnswer(_equation) {
    data.push_back(x1);
}

Task::Task(int _id, std::string _equation) : id(_id), equation(_equation) {}

int const Task::getTaskId() {
    return id;
}

std::string const Task::getEquation() {
    return equation;
}

BaseStudent::BaseStudent(const std::string _firstName, const std::string _secondName, const std::string _patronymic) {
    firstName = _firstName;
    secondName = _secondName;
    patronymic = _patronymic;
}

BaseStudent::BaseStudent(const std::string _firstName, const std::string _secondName) : BaseStudent(_firstName, _secondName, "") {
    hasPatronymic = false;
}

std::string const BaseStudent::getFirstName() {
    return firstName;
}

bool BaseStudent::isHasPatronymic() {
    return hasPatronymic;
}

std::string const BaseStudent::getSecondName() {
    return secondName;
}

std::string const BaseStudent::getPatronymic() {
    return patronymic;
}

GoodStudnet::GoodStudnet(const std::string _firstName, const std::string _secondName, const std::string _patronymic) :
    BaseStudent(_firstName, _secondName, _patronymic) { }

GoodStudnet::GoodStudnet(const std::string _firstName, const std::string _secondName) : BaseStudent(_firstName, _secondName) {}

BaseAnswer* const GoodStudnet::solveTask(Task* task) {
    BaseAnswer* answer = solveRight(task);

    if (answer != nullptr)
        answer->setAuthor(this);

    return answer;
}

OrdinaryStudent::OrdinaryStudent(const std::string _firstName, const std::string _secondName, const std::string _patronymic) :
    BaseStudent(_firstName, _secondName, _patronymic) { }

OrdinaryStudent::OrdinaryStudent(const std::string _firstName, const std::string _secondName) : BaseStudent(_firstName, _secondName) {}

BaseAnswer* const OrdinaryStudent::solveTask(Task* task) {
    BaseAnswer* answer = solveRight(task);
    
    if (answer != nullptr) {
        const int probability = rand() % 3;

        if (probability == 0)
            answer->addError();

        answer->setAuthor(this);
    }

    return answer;
}

BadStudent::BadStudent(const std::string _firstName, const std::string _secondName, const std::string _patronymic) :
    BaseStudent(_firstName, _secondName, _patronymic) { }

BadStudent::BadStudent(const std::string _firstName, const std::string _secondName) : BaseStudent(_firstName, _secondName) {}

BaseAnswer* const BadStudent::solveTask(Task* task) {
    BaseAnswer* answer = new AnswerWithSingleRoot(task->getEquation(), 0);
    answer->setAuthor(this);

    return answer;
}

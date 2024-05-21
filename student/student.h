#include <string>
#include <vector>


class BaseStudent;

class AbstractAnswer {
protected:
    std::string equation;
    std::vector<float> data;
    BaseStudent* author = nullptr;
};

class BaseAnswer : public AbstractAnswer {
protected:
    BaseAnswer();
public:
    BaseAnswer(std::string _equation);

    std::vector<float> getData();

    std::string getEquation();

    void addError();

    void setAuthor(BaseStudent* _author);

    BaseStudent* const getAuthor();

    void const print();

    bool operator==(BaseAnswer& answer);

    bool operator==(BaseAnswer* const answer);
};

class AnswerWithDoubleRoots : public BaseAnswer {
public:
    AnswerWithDoubleRoots(std::string _equation, float x1, float x2);
};

class AnswerWithSingleRoot : public BaseAnswer {
public:
    AnswerWithSingleRoot(std::string _equation, float x1);
};

class Task {
private:
    int id;
    std::string equation;

public:
    Task(int _id, std::string _equation);

    int const getTaskId();

    std::string const getEquation(); 
};

class AbstractStudent {
protected:
    std::string firstName;
    std::string secondName;
    std::string patronymic;
    bool hasPatronymic = true;

public:
    virtual BaseAnswer* const solveTask(Task* task) = 0;
};

class BaseStudent : public AbstractStudent {
public:
    BaseStudent(const std::string _firstName, const std::string _secondName, const std::string _patronymic);

    BaseStudent(const std::string _firstName, const std::string _secondName);

    std::string const getFirstName();

    bool isHasPatronymic();
    
    std::string const getSecondName();
    
    std::string const getPatronymic();
};

class GoodStudnet : public BaseStudent {
public:
    GoodStudnet(const std::string _firstName, const std::string _secondName, const std::string _patronymic);

    GoodStudnet(const std::string _firstName, const std::string _secondName);

    virtual BaseAnswer* const solveTask(Task* task);
};

class OrdinaryStudent : public BaseStudent {
public:
    OrdinaryStudent(const std::string _firstName, const std::string _secondName, const std::string _patronymic);

    OrdinaryStudent(const std::string _firstName, const std::string _secondName);

    virtual BaseAnswer* const solveTask(Task* task);
};

class BadStudent : public BaseStudent {
public:
    BadStudent(const std::string _firstName, const std::string _secondName, const std::string _patronymic);

    BadStudent(const std::string _firstName, const std::string _secondName);

    virtual BaseAnswer* const solveTask(Task* task);
};

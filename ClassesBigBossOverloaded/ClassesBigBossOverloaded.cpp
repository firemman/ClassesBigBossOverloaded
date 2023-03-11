#include <iostream>
#include <stdlib.h>

using namespace std;

class Departments {
public:
    virtual void infoDep() = 0;
};

class MediaDep : public Departments {
public:
    void infoDep() override {
        cout << "Сотрудник состоит в отделе Медиа.\n";
    }
};

class HrDep : public Departments {
    void infoDep() override {
        cout << "Сотрудник состоит в отделе HR.\n";
    }
};

class MechDep : public Departments {
    void infoDep() override {
        cout << "Сотрудник состоит в отеделе механиков.\n";
    }
};

class Employee {
public:
    Employee() : name("empty"), age(0), salary(0) { };
    Employee(string name, int age) { this->name = name; this->age = age; }
    Employee(string name, int age, int salary) : Employee(name, age) { this->salary = salary; }
    ~Employee() { };

    void Print();
    void setName(string name) { this->name = name; }
    void setSalary(int salary) { this->salary = salary; }
    void setAge(int age) { this->age = age; }
    void setDepartment(Departments* dep) { this->dep = dep; }

    void infoDep() {
        dep->infoDep();
    }

    string getName() { return name; }
    int getSalary() { return salary; }
    int getAge() { return age; }

protected:
    string name;
    int age;
    int salary;
    Departments* dep;
};

void Employee::Print() {
    cout << "Информация о сотруднике " << name << ": " << endl;
    cout << "Возраст: " << age << endl;
    cout << "Зар. плата: " << salary << endl;
    infoDep();
    cout << "\n";
}

class BigBoss : public Employee {
public:
    int getBonus() { return bonus; }

    int salaryBonus;

    BigBoss() : Employee() { };
    BigBoss(string name, int age, int salary) : Employee(name, age) {
        this->salary = (salary * getBonus()) + salary;
    }

    void setSalary(int salary) { this->salary = (salary * getBonus()) + salary; }

    string getName() { return name; }
    int getSalary() { return salary; }
    int getAge() { return age; }

    void Print() {
        cout << "Информация о сотруднике (Боссе)" << name << ": " << endl;
        cout << "Возраст: " << age << endl;
        cout << "Зар. плата с надбавкой: " << salary << endl;
        infoDep();
        cout << "\n";
    }

    bool operator <=(BigBoss boss) {
        double boss1 = getSalary();
        double boss2 = boss.getSalary();
        if (boss1 <= boss2)
            return true;
        else
            return false;
    }

private:
    int bonus = 0.5;
};


int main() {
    setlocale(LC_ALL, "rus");

    MediaDep mediaDep;
    HrDep hrDep;
    MechDep mechDep;

    Employee e1("Mark", 25, 35000);
    e1.setDepartment(&mediaDep);

    BigBoss b1("Ivan", 40, 100000);
    b1.setDepartment(&mediaDep);

    Employee e2("Evstahiy", 24, 20000);
    e2.setDepartment(&hrDep);

    BigBoss b2("Vlad", 45, 230000);
    b2.setDepartment(&hrDep);

    Employee e3("Maks", 30, 35000);
    e3.setDepartment(&mechDep);

    BigBoss b3("Georg", 60, 400000);
    b3.setDepartment(&mechDep);

    e1.Print();
    cout << "\n";

    b1.Print();
    cout << "\n";

    e2.Print();
    cout << "\n";

    b2.Print();
    cout << "\n";

    e3.Print();
    cout << "\n";

    b3.Print();
    cout << "\n";

    cout << "Сравнение зарплат двух боссов:\n";
    if (b2.getSalary() <= b1.getSalary()) {
        cout << "У босса " << b1.getName() << " зарплата " << "(" << b1.getSalary() << " руб) больше, чем у босса " << b2.getName() << " на " << b1.getSalary() - b2.getSalary() << " рублей.\n";
    }
    else
        cout << "У босса " << b2.getName() << " зарплата " << "(" << b2.getSalary() << " руб) больше, чем у босса " << b1.getName() << " на " << b2.getSalary() - b1.getSalary() << " рублей.\n";
}
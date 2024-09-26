#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <cstddef>  // 添加这个头文件

using namespace std;

class Student {
public:
    string id, name, className;
    int math, english, cpp;

    Student(string id, string name, string className, int math, int english, int cpp)
        : id(id), name(name), className(className), math(math), english(english), cpp(cpp) {}

    int totalScore() const {
        return math + english + cpp;
    }
};

// 比较函数，用于排序学生
bool compareStudents(const Student& a, const Student& b) {
    return a.totalScore() > b.totalScore();
}

class Course {
private:
    vector<Student> students;

    bool idExists(const string& id) {
        for (std::size_t i = 0; i < students.size(); ++i) {
            if (students[i].id == id) return true;
        }
        return false;
    }

public:
    void addStudent() {
        string id, name, className;
        int math, english, cpp;
        cout << "请输入学号(7位): ";
        cin >> id;
        if (idExists(id)) {
            cout << "学号已存在，不进行添加" << endl;
            return;
        }
        cout << "请输入姓名: ";
        cin >> name;
        cout << "请输入班级: ";
        cin >> className;
        cout << "请输入高数成绩: ";
        cin >> math;
        cout << "请输入英语成绩: ";
        cin >> english;
        cout << "请输入C++成绩: ";
        cin >> cpp;
        students.push_back(Student(id, name, className, math, english, cpp));
        cout << "学生信息添加成功！" << endl;
    }

    void displayStudents() {
        for (std::size_t i = 0; i < students.size(); ++i) {
            const Student& student = students[i];
            cout << "学号: " << student.id << ", 姓名: " << student.name << ", 班级: " << student.className
                 << ", 高数: " << student.math << ", 英语: " << student.english << ", C++: " << student.cpp << endl;
        }
    }

    void queryStudentById() {
        string id;
        cout << "请输入要查询的学号: ";
        cin >> id;
        for (std::size_t i = 0; i < students.size(); ++i) {
            const Student& student = students[i];
            if (student.id == id) {
                cout << "学号: " << student.id << ", 姓名: " << student.name << ", 班级: " << student.className
                     << ", 高数: " << student.math << ", 英语: " << student.english << ", C++: " << student.cpp << endl;
                return;
            }
        }
        cout << "没有这个学生！" << endl;
    }

    void modifyStudent() {
        string id;
        cout << "请输入要修改的学号: ";
        cin >> id;
        for (std::size_t i = 0; i < students.size(); ++i) {
            Student& student = students[i];
            if (student.id == id) {
                cout << "学号: " << student.id << ", 姓名: " << student.name << ", 班级: " << student.className
                     << ", 高数: " << student.math << ", 英语: " << student.english << ", C++: " << student.cpp << endl;
                cout << "确认修改该学生信息吗? (Y/N): ";
                char confirm;
                cin >> confirm;
                if (confirm == 'Y' || confirm == 'y') {
                    cout << "请输入新的姓名: ";
                    cin >> student.name;
                    cout << "请输入新的班级: ";
                    cin >> student.className;
                    cout << "请输入新的高数成绩: ";
                    cin >> student.math;
                    cout << "请输入新的英语成绩: ";
                    cin >> student.english;
                    cout << "请输入新的C++成绩: ";
                    cin >> student.cpp;
                    cout << "信息修改成功！" << endl;
                }
                return;
            }
        }
        cout << "没有这个学生！" << endl;
    }

    void deleteStudent() {
        string id;
        cout << "请输入要删除的学号: ";
        cin >> id;
        for (vector<Student>::iterator it = students.begin(); it != students.end(); ++it) {
            if (it->id == id) {
                cout << "确认删除该学生信息吗? (Y/N): ";
                char confirm;
                cin >> confirm;
                if (confirm == 'Y' || confirm == 'y') {
                    students.erase(it);
                    cout << "学生信息删除成功！" << endl;
                }
                return;
            }
        }
        cout << "没有这个学生！" << endl;
    }

    // 统计功能：显示学生人数和所有学生的总分
    void countStudents() {
        cout << "学生总人数: " << students.size() << endl;
        for (std::size_t i = 0; i < students.size(); ++i) {
            cout << "学号: " << students[i].id << "，总分: " << students[i].totalScore() << endl;
        }
    }

    // 排序功能：按总分降序排序
    void sortStudents() {
        sort(students.begin(), students.end(), compareStudents);
        cout << "学生信息按总分降序排序完成！" << endl;
    }

    void saveToFile() {
        ofstream outFile("students.txt");
        for (std::size_t i = 0; i < students.size(); ++i) {
            const Student& student = students[i];
            outFile << student.id << " " << student.name << " " << student.className << " "
                    << student.math << " " << student.english << " " << student.cpp << endl;
        }
        outFile.close();
        cout << "学生信息已保存到文件！" << endl;
    }

    void loadFromFile() {
        ifstream inFile("students.txt");
        string id, name, className;
        int math, english, cpp;
        while (inFile >> id >> name >> className >> math >> english >> cpp) {
            students.push_back(Student(id, name, className, math, english, cpp));
        }
        inFile.close();
        cout << "学生信息已从文件加载！" << endl;
    }
};

int main() {
    Course course;
    course.loadFromFile();
    int choice;
    while (true) {
        cout << "1. 录入学生信息" << endl;
        cout << "2. 显示学生信息" << endl;
        cout << "3. 查询学生信息" << endl;
        cout << "4. 修改学生信息" << endl;
        cout << "5. 删除学生信息" << endl;
        cout << "6. 保存学生信息到文件" << endl;
        cout << "7. 统计学生信息" << endl;
        cout << "8. 排序学生信息" << endl;
        cout << "0. 退出" << endl;
        cout << "请选择功能: ";
        cin >> choice;
        switch (choice) {
            case 1:
                course.addStudent();
                break;
            case 2:
                course.displayStudents();
                break;
            case 3:
                course.queryStudentById();
                break;
            case 4:
                course.modifyStudent();
                break;
            case 5:
                course.deleteStudent();
                break;
            case 6:
                course.saveToFile();
                break;
            case 7:
                course.countStudents();
                break;
            case 8:
                course.sortStudents();
                course.displayStudents();  // 排序后显示
                break;
            case 0:
                cout << "系统退出！" << endl;
                return 0;
            default:
                cout << "无效的选择，请重试！" << endl;
        }
    }
}


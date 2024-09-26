#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <cstddef>  // ������ͷ�ļ�

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

// �ȽϺ�������������ѧ��
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
        cout << "������ѧ��(7λ): ";
        cin >> id;
        if (idExists(id)) {
            cout << "ѧ���Ѵ��ڣ����������" << endl;
            return;
        }
        cout << "����������: ";
        cin >> name;
        cout << "������༶: ";
        cin >> className;
        cout << "����������ɼ�: ";
        cin >> math;
        cout << "������Ӣ��ɼ�: ";
        cin >> english;
        cout << "������C++�ɼ�: ";
        cin >> cpp;
        students.push_back(Student(id, name, className, math, english, cpp));
        cout << "ѧ����Ϣ��ӳɹ���" << endl;
    }

    void displayStudents() {
        for (std::size_t i = 0; i < students.size(); ++i) {
            const Student& student = students[i];
            cout << "ѧ��: " << student.id << ", ����: " << student.name << ", �༶: " << student.className
                 << ", ����: " << student.math << ", Ӣ��: " << student.english << ", C++: " << student.cpp << endl;
        }
    }

    void queryStudentById() {
        string id;
        cout << "������Ҫ��ѯ��ѧ��: ";
        cin >> id;
        for (std::size_t i = 0; i < students.size(); ++i) {
            const Student& student = students[i];
            if (student.id == id) {
                cout << "ѧ��: " << student.id << ", ����: " << student.name << ", �༶: " << student.className
                     << ", ����: " << student.math << ", Ӣ��: " << student.english << ", C++: " << student.cpp << endl;
                return;
            }
        }
        cout << "û�����ѧ����" << endl;
    }

    void modifyStudent() {
        string id;
        cout << "������Ҫ�޸ĵ�ѧ��: ";
        cin >> id;
        for (std::size_t i = 0; i < students.size(); ++i) {
            Student& student = students[i];
            if (student.id == id) {
                cout << "ѧ��: " << student.id << ", ����: " << student.name << ", �༶: " << student.className
                     << ", ����: " << student.math << ", Ӣ��: " << student.english << ", C++: " << student.cpp << endl;
                cout << "ȷ���޸ĸ�ѧ����Ϣ��? (Y/N): ";
                char confirm;
                cin >> confirm;
                if (confirm == 'Y' || confirm == 'y') {
                    cout << "�������µ�����: ";
                    cin >> student.name;
                    cout << "�������µİ༶: ";
                    cin >> student.className;
                    cout << "�������µĸ����ɼ�: ";
                    cin >> student.math;
                    cout << "�������µ�Ӣ��ɼ�: ";
                    cin >> student.english;
                    cout << "�������µ�C++�ɼ�: ";
                    cin >> student.cpp;
                    cout << "��Ϣ�޸ĳɹ���" << endl;
                }
                return;
            }
        }
        cout << "û�����ѧ����" << endl;
    }

    void deleteStudent() {
        string id;
        cout << "������Ҫɾ����ѧ��: ";
        cin >> id;
        for (vector<Student>::iterator it = students.begin(); it != students.end(); ++it) {
            if (it->id == id) {
                cout << "ȷ��ɾ����ѧ����Ϣ��? (Y/N): ";
                char confirm;
                cin >> confirm;
                if (confirm == 'Y' || confirm == 'y') {
                    students.erase(it);
                    cout << "ѧ����Ϣɾ���ɹ���" << endl;
                }
                return;
            }
        }
        cout << "û�����ѧ����" << endl;
    }

    // ͳ�ƹ��ܣ���ʾѧ������������ѧ�����ܷ�
    void countStudents() {
        cout << "ѧ��������: " << students.size() << endl;
        for (std::size_t i = 0; i < students.size(); ++i) {
            cout << "ѧ��: " << students[i].id << "���ܷ�: " << students[i].totalScore() << endl;
        }
    }

    // �����ܣ����ֽܷ�������
    void sortStudents() {
        sort(students.begin(), students.end(), compareStudents);
        cout << "ѧ����Ϣ���ֽܷ���������ɣ�" << endl;
    }

    void saveToFile() {
        ofstream outFile("students.txt");
        for (std::size_t i = 0; i < students.size(); ++i) {
            const Student& student = students[i];
            outFile << student.id << " " << student.name << " " << student.className << " "
                    << student.math << " " << student.english << " " << student.cpp << endl;
        }
        outFile.close();
        cout << "ѧ����Ϣ�ѱ��浽�ļ���" << endl;
    }

    void loadFromFile() {
        ifstream inFile("students.txt");
        string id, name, className;
        int math, english, cpp;
        while (inFile >> id >> name >> className >> math >> english >> cpp) {
            students.push_back(Student(id, name, className, math, english, cpp));
        }
        inFile.close();
        cout << "ѧ����Ϣ�Ѵ��ļ����أ�" << endl;
    }
};

int main() {
    Course course;
    course.loadFromFile();
    int choice;
    while (true) {
        cout << "1. ¼��ѧ����Ϣ" << endl;
        cout << "2. ��ʾѧ����Ϣ" << endl;
        cout << "3. ��ѯѧ����Ϣ" << endl;
        cout << "4. �޸�ѧ����Ϣ" << endl;
        cout << "5. ɾ��ѧ����Ϣ" << endl;
        cout << "6. ����ѧ����Ϣ���ļ�" << endl;
        cout << "7. ͳ��ѧ����Ϣ" << endl;
        cout << "8. ����ѧ����Ϣ" << endl;
        cout << "0. �˳�" << endl;
        cout << "��ѡ����: ";
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
                course.displayStudents();  // �������ʾ
                break;
            case 0:
                cout << "ϵͳ�˳���" << endl;
                return 0;
            default:
                cout << "��Ч��ѡ�������ԣ�" << endl;
        }
    }
}


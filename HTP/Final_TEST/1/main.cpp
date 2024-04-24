#include <iostream>
#include <map>
#include <string>
#include <memory>
#include <mutex>
#include <thread>
#include <stdexcept>

struct Student {
    int id;
    std::string name;
    int age;
};

class StudentDatabase {
public:
    void AddStudent(int id, const std::string& name, int age) {
        if (students.count(id) || id < 0 || age < 0 || name.empty()) {
            throw std::invalid_argument("Wrong id, name or age");
        }
        std::lock_guard<std::mutex> lock(mtx);
        students.emplace(std::pair{ id, std::make_shared<Student>(Student{id, name, age}) });
    }

    void RemoveStudent(int id) {
        if (id < 0) {
            throw std::invalid_argument("Wrong id");
        }
        if (auto pos = students.find(id); pos != students.end()) {
            std::lock_guard<std::mutex> lock(mtx);
            students.erase(pos);
        }
        
    }

    std::shared_ptr<Student> GetStudent(int id) {
        if (id < 0) {
            throw std::invalid_argument("Wrong id");
        }
        std::lock_guard<std::mutex> lock(mtx);
        if (auto pos = students.find(id); pos != students.end()) {
                return pos->second;
        }
        return nullptr;
    }
private:
    std::map<int, std::shared_ptr<Student>> students;
    std::mutex mtx;
};

void Writer(StudentDatabase& DB) {
    for (int i = 0; i < 30; ++i) {
        DB.AddStudent(i, "student_" + std::to_string(i), 25+i);
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }
}

void Reader(StudentDatabase& DB) {
    for (int i = 0; i < 30; ++i) {
        std::shared_ptr<Student> student = DB.GetStudent(i);
        if (student) {
            std::cout << "student id: " << student->id << ", name: " << student->name << ", age: " << student->age << std::endl;
        } else {
            std::cout << "student with id " << i << " not found." << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }
}

int main() {
    StudentDatabase DB;

    std::thread WriterThread(Writer, std::ref(DB));
    std::thread ReaderThread(Reader, std::ref(DB));

    WriterThread.join();
    ReaderThread.join();

    return 0;
}

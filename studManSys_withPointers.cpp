#include <iostream>
#include <vector>
#include <limits>
#include <ctime>
#include <iomanip>

using namespace std;

class Student {
  private:
  int studId;
  string name;
  string birthdate;
  int age;
  float grade;

  public:
  Student(int id, string n, string bd, float g): studId(id),
  name(n),
  birthdate(bd),
  grade(g) {
    // Calculate age based on birthdate
    age = calculateAge(bd);
  }

  int getStudentId() const {
    return studId;
  }
  string getName() const {
    return name;
  }
  string getBirthdate() const {
    return birthdate;
  }
  int getAge() const {
    return age;
  }
  float getGrade() const {
    return grade;
  }

  void setName(string n) {
    name = n;
  }
  void setBirthdate(string bd) {
    birthdate = bd;
    // Recalculate age when birthdate changes
    age = calculateAge(bd);
  }
  void setGrade(float g) {
    grade = g;
  }

  private:
  int calculateAge(const string& bd) const {
    // Calculate age based on birthdate
    time_t now = time(0);
    tm* ltm = localtime(&now);
    int currentYear = 1900 + ltm->tm_year;
    int birthYear = stoi(bd.substr(6, 4));
    int age = currentYear - birthYear;
    if (ltm->tm_mon + 1 < stoi(bd.substr(0, 2)) ||
      (ltm->tm_mon + 1 == stoi(bd.substr(0, 2)) && ltm->tm_mday < stoi(bd.substr(3, 2)))) {
      age--;
    }
    return age;
  }
};

void displayMenu() {
  cout << "\nMenu:\n";
  cout << "1. Add new student\n";
  cout << "2. Display all students\n";
  cout << "3. Search for a student\n";
  cout << "4. Update student information\n";
  cout << "5. Delete a student\n";
  cout << "6. Exit\n";
  cout << "Enter your choice: ";
}

void addStudent(vector < Student*>& students) {
  string name,
  birthdate;
  float grade;

  cout << "\nEnter student details:\n";
  cout << "Name: ";
  cin.ignore(numeric_limits < streamsize > ::max(), '\n');
  getline(cin, name);

  // Validate and handle birthdate input
  while (true) {
    cout << "Birthdate (MM/DD/YYYY): ";
    getline(cin, birthdate);
    // Check if birthdate has correct format
    if (birthdate.size() != 10 || birthdate[2] != '/' || birthdate[5] != '/') {
      cout << "Invalid birthdate format. Please enter in MM/DD/YYYY format.\n";
    } else {
      // Validate month, day, and year
      int month = stoi(birthdate.substr(0, 2));
      int day = stoi(birthdate.substr(3, 2));
      int year = stoi(birthdate.substr(6, 4));
      if (month < 1 || month > 12 || day < 1 || day > 31 || year < 1900) {
        cout << "Invalid birthdate. Please enter a valid date.\n";
      } else {
        break; // Valid birthdate input
      }
    }
  }

  cout << "Grade: ";
  while (!(cin >> grade)) {
    cout << "Invalid input. Please enter a valid grade: ";
    cin.clear();
    cin.ignore(numeric_limits < streamsize > ::max(), '\n');
  }

  int nextId = students.empty() ? 1: students.back()->getStudentId() + 1;
  students.push_back(new Student(nextId, name, birthdate, grade));
  cout << "Student added successfully!\n";
}

void displayStudents(const vector < Student*>& students) {
  cout << "\nList of all students:\n";
  cout << setw(5) << "ID" << setw(20) << "Name" << setw(15) << "Birthdate" << setw(5) << "Age" << setw(10) << "Grade" << endl;
  for (const auto& student: students) {
    cout << setw(5) << student->getStudentId() << setw(20) << student->getName() << setw(15) << student->getBirthdate() << setw(5) << student->getAge() << setw(10) << student->getGrade() << endl;
  }
}
// Function to search for a student by name
void searchStudent(const vector < Student*>& students) {
  string searchName;
  cout << "\nEnter the name of the student to search for: ";
  cin.ignore(numeric_limits < streamsize > ::max(), '\n');
  getline(cin, searchName);

  bool found = false;
  for (const auto& student: students) {
    if (student->getName() == searchName) {
      cout << "Student found:\n";
      cout << setw(5) << "ID" << setw(20) << "Name" << setw(15) << "Birthdate" << setw(5) << "Age" << setw(10) << "Grade" << endl;
      cout << setw(5) << student->getStudentId() << setw(20) << student->getName() << setw(15) << student->getBirthdate() << setw(5) << student->getAge() << setw(10) << student->getGrade() << endl;
      found = true;
      break;
    }
  }

  if (!found) {
    cout << "Student not found.\n";
  }
}

// Function to update student information
void updateStudent(vector < Student*>& students) {
  int searchId;
  cout << "\nEnter the ID of the student to update: ";
  while (!(cin >> searchId)) {
    cout << "Invalid input. Please enter a valid ID: ";
    cin.clear();
    cin.ignore(numeric_limits < streamsize > ::max(), '\n');
  }

  bool found = false;
  for (auto& student: students) {
    if (student->getStudentId() == searchId) {
      cout << "Enter new details:\n";
      cout << "Name: ";
      string newName;
      cin.ignore(numeric_limits < streamsize > ::max(), '\n');
      getline(cin, newName);

      if (newName.empty()) {
        cout << "Name cannot be empty. Please enter a valid name.\n";
        return;
      }

      student->setName(newName);

      // Validate and handle birthdate input
      string newBirthdate;
      while (true) {
        cout << "Birthdate (MM/DD/YYYY): ";
        getline(cin, newBirthdate);
        // Check if birthdate has correct format
        if (newBirthdate.size() != 10 || newBirthdate[2] != '/' || newBirthdate[5] != '/') {
          cout << "Invalid birthdate format. Please enter in MM/DD/YYYY format.\n";
        } else {
          // Validate month, day, and year
          int month = stoi(newBirthdate.substr(0, 2));
          int day = stoi(newBirthdate.substr(3, 2));
          int year = stoi(newBirthdate.substr(6, 4));
          if (month < 1 || month > 12 || day < 1 || day > 31 || year < 1900) {
            cout << "Invalid birthdate. Please enter a valid date.\n";
          } else {
            student->setBirthdate(newBirthdate);
            break; // Valid birthdate input
          }
        }
      }

      float newGrade;
      cout << "Grade: ";
      while (!(cin >> newGrade)) {
        cout << "Invalid input. Please enter a valid grade: ";
        cin.clear();
        cin.ignore(numeric_limits < streamsize > ::max(), '\n');
      }
      student->setGrade(newGrade);

      cout << "Student information updated successfully!\n";
      found = true;
      break;
    }
  }

  if (!found) {
    cout << "Student not found.\n";
  }
}

// Function to delete a student
void deleteStudent(vector < Student*>& students) {
  int searchId;
  cout << "\nEnter the ID of the student to delete: ";
  while (!(cin >> searchId)) {
    cout << "Invalid input. Please enter a valid ID: ";
    cin.clear();
    cin.ignore(numeric_limits < streamsize > ::max(), '\n');
  }

  for (auto it = students.begin(); it != students.end(); ++it) {
    if ((*it)->getStudentId() == searchId) {
      delete *it; // Free the memory allocated for the student object
      it = students.erase(it);
      cout << "Student deleted successfully!\n";
      return;
    }
  }
  cout << "Student not found.\n";
}

// Function to clean up dynamically allocated memory
void cleanupMemory(vector < Student*>& students) {
  for (auto& student: students) {
    delete student; // Free the memory allocated for each student object
  }
}


int main() {
  vector < Student*> students;
  int choice;
  system("clear");
  do {
    displayMenu();
    while (!(cin >> choice)) {
      cout << "Invalid input. Please enter a number: ";
      cin.clear();
      cin.ignore(numeric_limits < streamsize > ::max(), '\n');
    }

    switch (choice) {
      case 1:
      addStudent(students);
      break;
      case 2:
      displayStudents(students);
      break;
      case 3:
      searchStudent(students);
      break;
      case 4:
      updateStudent(students);
      break;
      case 5:
      deleteStudent(students);
      break;
      case 6:
      cout << "Exiting program. Goodbye!\n";
      break;
      default:
      cout << "Invalid choice. Please select a valid option.\n";
    }
  } while (choice != 6);

  // Clean up dynamically allocated memory before exiting
  for (auto& student: students) {
    delete student;
  }

  return 0;
}
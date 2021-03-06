#include <iostream>
using namespace std;

#include <fstream>//fstream is used to create files, write information to files , and read information from files.
#include <cstring>

const int NAME_SIZE = 20;
const int DEPT_NAME_SIZE = 5;

const int DYNAMIC_STUDENT_HEAP_SIZE = 5;

typedef unsigned char byte;

class student
{
    char *name;
    int age;
    char *department;
    int year_grad;

public:
    student();  // default condstructor
    ~student(); // destructor
    void readStudentData(ifstream &fin);
    void readStudentData();
    void printStudentData() const;
    void *operator new(size_t size);//size_t means max of int 
    void operator delete(void *p);
    static bool *data_occupied;
    static byte *data;//byte used for unsingned char
    static void initialize_dynamic_data();
};
byte *student ::data = NULL;
bool *student ::data_occupied = NULL;
void student ::initialize_dynamic_data()
{
    data = new byte[sizeof(student) * DYNAMIC_STUDENT_HEAP_SIZE];
    data_occupied = new bool[DYNAMIC_STUDENT_HEAP_SIZE];
}
student ::~student()
{
    free(name);
    free(department);
}
student::student() : age(-1), year_grad(-1)//initilisation list used here
{
    name = (char *)malloc(NAME_SIZE);//creating dynamic allocation 
    department = (char *)malloc(DEPT_NAME_SIZE);
}

void *student ::operator new(size_t size)
{
    void *s;
    for (int i = 0; i < DYNAMIC_STUDENT_HEAP_SIZE; i++)
    {
        if (data_occupied[i] == false)
        {
            data_occupied[i] = true;
            s = (void *)&data[i * sizeof(student)];
            return s;
        }
    }
    cout << "Error : No more dynamic data left !!,returning NULL " << endl;
    return NULL;
}
void student ::operator delete(void *p)
{
    for (int i = 0; i < DYNAMIC_STUDENT_HEAP_SIZE; i++)
    {

        if (&data[i] == (byte *)p)
        {
            data_occupied[i] = false;
        }
    }
}
void student ::readStudentData(ifstream &fin)
{
    fin.getline(name, NAME_SIZE);
    fin >> age >> department >> year_grad;
    fin.ignore();
}
void student ::readStudentData()
{
    cout << "Enter Student's Name: ";
    cin.getline(name, NAME_SIZE);
    cout << "Enter Age: ";
    cin >> age;
    cout << "Enter Department (Abbv.)" << endl;
    cin >> department;
    cout << "Enter Year of Graduation: ";
    cin >> year_grad;
    cin.ignore();//ignore newline
}

void student ::printStudentData() const
{
    cout << " Name : " << name << endl;
    cout << "Age :" << age << endl;
    cout << "Department : " << department << endl;
    cout << "Year of Gradution : " << year_grad << endl;
}
int main()
{
    cout << "Doing Pointer ...." << endl;
    student ::initialize_dynamic_data();

    student *dynamic1 = new student;
    dynamic1->readStudentData();

    student *dynamic2 = new student;
    dynamic2->readStudentData();

    student *dynamic3 = new student;
    dynamic3->readStudentData();

    dynamic1->printStudentData();
    dynamic2->printStudentData();
    dynamic3->printStudentData();

    delete dynamic1;
    delete dynamic2;
    delete dynamic3;
    return 0;
}
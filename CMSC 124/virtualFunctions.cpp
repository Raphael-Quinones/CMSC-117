#include <iostream>
using namespace std;

enum YEAR { FRESH, SOPH, JUNIOR, SENIOR };
enum SUPPORT {TA, RA, FELLOWSHIP, OTHER };
class Student
{
public:
    // Constructors
    Student()
    {
        student_id = 0;
        gpa = 0.0;
        college[0] = '\0';
        yr = FRESH;
        major [0] = '\0';
    }
    Student( int id, float g )
    {
        student_id = id;
        gpa = g;
        college[0] = '\0';
        yr = FRESH;
        major [0] = '\0';
    }
    // prompt for and read values
    virtual void read(int* addstudent_id, float* addgpa, char* addname[], char* addcollege[], YEAR* addyr, char* addmajor[]){
        *addstudent_id = student_id;
        *addgpa = gpa;
        *addname = name;
        *addcollege = college;
        *addyr = yr;
        *addmajor = major;
    };
    // print values held
    virtual void print(){
        cout << "Student ID: " << student_id << endl;
        cout << "GPA: " << gpa << endl;
        cout << "Name: " << name << endl;
        cout << "College: " << college << endl;
        cout << "Year: " << yr << endl;
        cout << "Major: " << major << endl;
    };
    protected:
        int student_id; // student number
        float gpa; // student grade point average
        char name[30]; // student name
        char college[20]; // college name
        YEAR yr; // year in college
        char major[10]; // area of study
    };

class GradStudent : public Student
{
public:
    // Constructors
    GradStudent() : Student()
    {
        supp = TA;
        dept[0] = '\0';
        thesis[0] = '\0';
    }
    GradStudent( SUPPORT x, int id, float g) 
        : Student(id, g)
    {
        supp = x;
        dept[0] = '\0';
        thesis[0] = '\0';
    }
    // implementation of base class virtual functions
    void print(){
        cout << "Support: " << supp << endl;
        cout << "Department: " << dept << endl;
        cout << "Thesis: " << thesis << endl;
    };
    void read(SUPPORT* addsupp, char* adddept[], char* addthesis[]){
        *addsupp = supp;
        *adddept = dept;
        *addthesis = thesis;
    };
private:
    SUPPORT supp;
    char dept[10];
    char thesis[80];
};

int main(){
    freopen("exercise.txt","w+",stdout);
    //Student sample data
    int id = 20942;
    float g = 3.3;
    char *name;
    char *college;
    YEAR yr;
    char *major;

    Student stud(id, g);
    Student *stud1 = &stud;


    cout << "Testing Student Class Print" << endl;
    stud1->print();
    cout << "-----------------------------" << endl;
    cout << "Testing Student Class Read" << endl;
    stud1->read(&id, &g, &name, &college, &yr, &major);
    cout << "Student ID: " << id << endl;
    cout << "GPA: " << g << endl;
    cout << "Name: " << name << endl;
    cout << "College: " << college << endl;
    cout << "Year: " << yr << endl;
    cout << "Major: " << major << endl;


    cout << "-----------------------------" << endl;

    //Grad Student variables
    SUPPORT supp;
    char *dept;
    char *thesis;

    GradStudent gradstud;
    GradStudent *stud2 = &gradstud;
    cout << "Testing Grad Student Class Print" << endl;
    stud2->print();
    cout << "-----------------------------" << endl;
    cout << "Testing Grad Student Class Read" << endl;
    stud2->read(&supp, &dept, &thesis);
    cout << "Support: " << supp << endl;
    cout << "Department: " << dept << endl;
    cout << "Thesis: " << thesis << endl;


     
    return 0;
}
#include "Task1.h"
#include "Task8.h"
#include "Task6.h"
#include "Task4.h"
#include "Task5.h"

int main(int argc, char** argv)
{
    // We have to use command line arguments (CLI) in the format ./a.out <space> filename.ext <space> task number.
    // argv[0] is ./a.out; argv[1] is filename.ext; argv[2] is the task number
    // Based on argv[2], we will have to make a switch case.

    Base* B;

    switch(stoi(argv[2]))
    {
        case 1 :
        {
            cout << "Task number " << stoi(argv[2]) << endl;
            B = new Task1(argv[1]);
            B->read();
            B->operate();
            B->write();
            break;
        }

        case 4:
        {
            cout << "Task 4" << endl;
            B = new Task4(argv[1]);
            B->read();
            B->operate();
            B->write();
            break;
        }

        case 5:
        {
            cout << "Task 5" << endl;
            B = new Task5(argv[1]);
            B->read();
            B->operate();
            B->write();
            break;
        }


        case 6:
        {
            cout << "Task number " << stoi(argv[2]) << endl;
            B = new Task6(argv[1]);
            B->read();
            B->operate();
            B->write();
            break;
        }
        case 8: // ./a.out diabetes.csv 8 A B
        {
            cout << "Task number " << stoi(argv[2]) << endl;
            string filename, c1, c2;
            filename = argv[1];
            c1 = argv[3];
            c2 = argv[4];
            cout << filename << " " << c1 << " " << c2 << '\n';

            Task8 task8(filename, c1, c2); // did not follow starter code
            task8.read();
            task8.operate();
            task8.write();
            break;
        }

        default :
            cout << "No task match";
    }





}
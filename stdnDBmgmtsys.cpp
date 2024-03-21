#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <conio.h>
#include <iomanip>

using namespace std;

int main() {
    FILE *fp, *ft;
    char choice, another;

    //structure for students
    struct student {
        char f_name[30], l_name[30];
        char course[50];
        int section;
    };

    struct student e;
    char xf_name[30], xl_name[30];
    long int recsize;

    fp = fopen("users.text", "rb+");

    if (fp == NULL) {
        fp = fopen("users.text", "wb+");
        if (fp == NULL) {
            puts("Cannot open the file");
            return 0;
        }
    }

    recsize = sizeof(e);
    
    while (1) {
        system("cls");

        cout << "\t\t====== STUDENT DATABASE MANAGEMENT SYSTEM ======";
        cout <<"\n\n                                          ";
        cout << "\n\n";
        cout << "\n \t\t\t 1. Add    Records";
        cout << "\n \t\t\t 2. List   Records";
        cout << "\n \t\t\t 3. Modify Records";
        cout << "\n \t\t\t 4. Delete Records";
        cout << "\n \t\t\t 5. Exit   Program";
        cout << "\n\n";
        cout << "\t\t\t Select Your Choice :=> ";

        fflush(stdin);
        choice = getche();
        

        switch (choice) {
            case '1' :
                fseek(fp, 0, SEEK_END);
                another = 'Y';
                while (another == 'Y' || another == 'y') {
                    system("cls");
                    cout << "Enter the first name: ";
                    cin >> e.f_name;
                    cout << "Enter the last name: ";
                    cin >> e.l_name;
                    cout << "Enter the course: ";
                    cin >> e.course;
                    cout << "Enter the section: ";
                    cin >> e.section;
                    fwrite(&e, recsize, 1, fp);
                    cout << "\n Add another record (Y/n) ";
                    fflush(stdin);
                    another = getchar();
                }
                break;
            case '2' :
                system("cls");
                rewind(fp);
                cout << "=== View the records in the database === ";
                cout << "\n";
                while (fread(&e, recsize, 1, fp) == 1) {
                    cout << "\n";
                    cout << "\n" << e.f_name << setw(10) << e.l_name;
                    cout << "\n";
                    cout << "\n" << e.course << setw(8) << e.section;
                }
                cout << "\n\n";
                system("pause");
                break;
            case '3' :
                system("cls");
                another = 'Y';
                while (another == 'Y' || another == 'y') {
                    cout << "\nEnter the last name of the student: ";
                    cin >> xl_name;

                    rewind(fp);
                    while(fread(&e, recsize, 1, fp) == 1) {
                        if (strcmp(e.l_name, xl_name) == 0) {
                            cout << "Enter a new first name: ";
                            cin >> e.f_name;
                            cout << "Enter a new last name: ";
                            cin >> e.l_name;
                            cout << "Enter a new course: ";
                            cin >> e.course;
                            cout << "Enter a new section: ";
                            cin >> e.section;
                            fseek(fp, - recsize, SEEK_CUR);
                            fwrite(&e, recsize, 1, fp);
                            break;
                        } else {
                            cout << "record not found";
                        }
                    }
                    cout << "\nModify another record (Y / n) ";
                    fflush(stdin);
                    another = getchar();
                }
                break;

            case '4' :
                system("cls");
                another = 'Y';
                while (another == 'Y' || another == 'y') {
                    cout << "\n Enter the last name of the student to delete: ";
                    cin >> xl_name;

                    ft = fopen("temp.dat", "wb");

                    rewind(fp);
                    while (fread(&e, recsize, 1, fp) == 1) {
                        if (strcmp(e.l_name, xl_name) != 0) {
                            fwrite(&e, recsize, 1, fp);
                        }
                    fclose(fp);
                    fclose(ft);
                    remove("users.txt");
                    rename("temp.dat", "users.txt");

                    fp = fopen("users.txt", "rb+");

                    cout << "\n Delete another record (y/n) ";
                    fflush(stdin);
                    another = getchar();
                    }
                break;
            }
            case '5' :
                fclose(fp);
                cout << "\n\n";
                cout << "\t\t";
                cout << "\n\n";
                exit(0);

        }   

    }
    system("pause");
    return 0;
}
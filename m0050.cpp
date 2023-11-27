#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

/* structure for employee data */
struct empData
{
    int id;
    string first;
    string last;
    double salary;
    double bonus;
};

/* function definitions */
bool compareId(empData first, empData second);
bool compareSalary(empData first, empData second);
bool compareNames(empData first, empData second);

int main (int argc, char** argv)
{
    ifstream fin;                   /* input file */
    ofstream fout;                  /* output file */
    string headers;                 /* string to represent headers*/
    string line;                    /* represents each line */
    string section;                 /* represents each column */
    stringstream csvLine;           /* represents line of csv file */
    empData emp;                    /* structure variable */
    vector<empData> employee;       /* vector to store data */
    vector<empData>::iterator it;   /* vector for iterator */
    int i = 0;                      /* loop variable */

    /* error checking */
    if (argc != 4)
    {
        cout << "Usage: m0050.exe inputCSVFile outputCSVFile sortMethod" << endl;
        return 0;
    }

    fin.open(argv[1], ifstream::in);    /* open input file */

    if (!fin.is_open())
    {
        cout << "Unable to open input file: " << argv[1] << endl;
        fin.close();
        return 0;
    }

    fout.open(argv[2], ifstream::out);  /* open output file */

    /* error checking */
    if (!fout.is_open())
    {
        cout << "Unable to open output file: " << argv[2] << endl;
        fin.close();
        return 0;
    }

    if ((strcmp(argv[3], "-i") != 0) && (strcmp(argv[3], "-s") != 0) && (strcmp(argv[3], "-n") != 0))
    {
        cout << "Invalid Sort Method:" << endl;
        cout << "-i - sort by id" << endl;
        cout << "-n - sort by name" << endl;
        cout << "-s - sort by salary" << endl;
    }

    /* read input file and assign data to variables */
    getline(fin, headers);
    while (getline(fin, line)) 
    {
        csvLine.str(line);
        csvLine.clear();

        while (getline(csvLine, section, ','))
        {
            if (i % 5 == 0)
            {
                emp.id = stoi(section);
            }
            if (i % 5 == 1)
            {
                emp.first = section;
            }
            if (i % 5 == 2)
            {
                emp.last = section;
            }
            if (i % 5 == 3)
            {
                emp.salary = stod(section);
            }
            if (i % 5 == 4)
            {
                emp.bonus = stod(section);
                employee.push_back(emp);
            }
            ++i;
        }
    }

    /* determine what sort needs to be used */
    if (strcmp(argv[3], "-i") == 0)
        sort(employee.begin(), employee.end(), compareId);
    if (strcmp(argv[3], "-s") == 0)
        sort(employee.begin(), employee.end(), compareSalary);
    if (strcmp(argv[3], "-n") == 0)
        sort(employee.begin(), employee.end(), compareNames);

    fin.close();    /* close input file */

    /* write output file */
    fout << headers << endl;
    for (it = employee.begin(); it != employee.end(); ++it)
    {
        fout << it->id << "," << it->first << "," << it->last << "," << 
            fixed << setprecision(2) << it->salary << "," << it->bonus << endl;
    }


    fout.close();   /* close output file */

    return 0;

}

bool compareId(empData first, empData second)
{
    return first.id < second.id;
}

bool compareSalary(empData first, empData second)
{
    return first.salary > second.salary;
}

bool compareNames(empData first, empData second)
{
    if (first.last == second.last)
        return first.first < second.first;
    
    return first.last < second.last;
}
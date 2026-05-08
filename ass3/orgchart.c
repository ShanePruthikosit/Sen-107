/* orgChart
 *
 * Build a corporate hierarchy structure and sorted binary tree
 *
 *  Created by Chavakorn Arunkunarax and Phasit Thanitkul, 2025-01-12
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/* Adds employee to the corporate hierarchy structure and sorted binary tree
 */
void addEmployee(char* name, char* employeeId, char* jobTitle, char* supervisorName, char* supervisorId)
{
    // ************** Please change the code below to your code **************
    printf("Please add your code to add employee.\n");
}

/* Prints the corporate hierarchy structure, pre-order
 */
void printCorporateHierarchy()
{
    // ************** Please change the code below to your code **************
    printf("Please add your code to print corporate hierarchy.\n");
}

/* Prints the sorted list of employees
 */
void printSortedList()
{
    // ************** Please change the code below to your code **************
    printf("Please add your code to print sorted list.\n");
}

/* Searches for an employee in the corporate hierarchy structure
 */
void searchEmployee(char* name, char* employeeId)
{
    // ************** Please change the code below to your code **************
    printf("Please add your code to search employee.\n");
}

/* Free the contents of the datastructures used */
void freeAll()
{
	// ************** Please change the code below to your code **************
	printf("Please add your code to free all datastructures.\n");
}


int main()
{
    char input[128];
    char name[32];
    char employeeId[8];
    char jobTitle[32];
    char supervisorName[32];
    char supervisorId[8];

    int numEmployees;
    int numQuestions;

    scanf("%d", &numEmployees);
    scanf("%d", &numQuestions);

    for (int i = 0; i < numEmployees; i++)
    {
        scanf("\n%s %s %s %s %s", name, employeeId, jobTitle, supervisorName, supervisorId);
        addEmployee(name, employeeId, jobTitle, supervisorName, supervisorId);
    }

    printCorporateHierarchy();


    for (int i = 0; i < numQuestions; i++)
    {
        scanf("\n%s %s", name, employeeId);
        searchEmployee(name, employeeId);
    }

    printSortedList();

    freeAll();

    return 0;
}

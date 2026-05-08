/* matrilineal
 * 
 * Build a simple, non-sorted tree of mother-daughter relationships
 *
 *  Template for Fundamental Data Structures Lab 2
 *  Created by Pasin Manurangsi, 2025-01-08
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Adds person with a given name at the root.
 */
void addRoot(char* name)
{
	// ************** Please change the code below to your code **************
	printf("Please add your code to handle root node addition.\n");
}

/* Adds person with a given name and mother's name to the tree.
 */
void addNonRoot(char* name, char* motherName)
{
	// ************** Please change the code below to your code **************
	printf("Please add your code to handle non-root node addition.\n");
}

/* Prints the person's daughters.
 */
void queryDescendant(char* name)
{
	// ************** Please change the code below to your code **************
	printf("Please add your code to descendants query.\n");
}

/* Prints the longest descendant chain.
 */
void queryLongestDescendantChain()
{
	// ************** Please change the code below to your code **************
	printf("Please add your code to max descendant chain query.\n");
}


int main()
{
	char input[64]; // Input operation name
	char name[25]; // The name of the woman
	char motherName[25]; // The number of woman's mother
	int numOperations; // The number of operations.
	scanf("%d", &numOperations);
	scanf("\n%s", name);
	addRoot(name);
	for (int i = 1 ; i < numOperations ; i ++)
	{
		scanf("\n%s", input);
		if (strcmp(input, "Add") == 0)
		{
			scanf(" %s %s", name, motherName);
			addNonRoot(name, motherName);
		}
		else if (strcmp(input, "Descendant") == 0)
		{
			scanf(" %s", name);
			queryDescendant(name);
		}
		else
		{
			queryLongestDescendantChain();
		}
	}
}
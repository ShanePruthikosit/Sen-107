/* cmkl_book
 * 
 * Build a social network with basic functionalities
 *
 *  Template for Fundamental Data Structures Lab 2
 *  Created by Pasin Manurangsi, 2025-01-13
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Creates a new account.
 */
void newAccount(char* emailAddress, char* firstName, char* lastName)
{
	// ************** Please change the code below to your code **************
	printf("Please add your code to create a new account.\n");
}

/* Deletes an account.
 */
void deleteAccount(char* emailAddress)
{
	// ************** Please change the code below to your code **************
	printf("Please add your code to delete an account.\n");
}

/* Makes two accounts friend of each other.
 */
void addFriend(char* firstEmailAddress, char* secondEmailAddress)
{
	// ************** Please change the code below to your code **************
	printf("Please add your code to add friend.\n");
}

/*  Unfriends two accounts.
 */
void unfriend(char* firstEmailAddress, char* secondEmailAddress)
{
	// ************** Please change the code below to your code **************
	printf("Please add your code to unfriend.\n");
}

/* Prints the account's friends.
 */
void listFriends(char* emailAddress)
{
	// ************** Please change the code below to your code **************
	printf("Please add your code to print a person's friends.\n");
}

/* Prints the account's friend suggestions.
 */
void listSuggestions(char* emailAddress)
{
	// ************** Please change the code below to your code **************
	printf("Please add your code to print a person's friend suggestions.\n");
}

/* Free the contents of the datastructures used */
void freeAll()
{
	// ************** Please change the code below to your code **************
	printf("Please add your code to free all datastructures.\n");
}

int main()
{
	char input[64]; // Input operation name
	char emailAddress[55]; // Email address of a person
	char secondEmailAddress[55]; // Email address of another person
	char firstName[25]; // First name of the person
	char lastName[25]; // First name of the person
	int numOperations; // The number of operations.
	scanf("%d", &numOperations);
	for (int i = 0 ; i < numOperations ; i ++)
	{
		scanf("\n%s", input);
		if (strcmp(input, "New") == 0)
		{
			scanf(" %s %s %s", emailAddress, firstName, lastName);
			newAccount(emailAddress, firstName, lastName);
		}
		else if (strcmp(input, "Delete") == 0)
		{
			scanf(" %s", emailAddress);
			deleteAccount(emailAddress);
		}
		else if (strcmp(input, "Add") == 0)
		{
			scanf(" %s %s", emailAddress, secondEmailAddress);
			addFriend(emailAddress, secondEmailAddress);
		}
		else if (strcmp(input, "Unfriend") == 0)
		{
			scanf(" %s %s", emailAddress, secondEmailAddress);
			unfriend(emailAddress, secondEmailAddress);
		}
		else if (strcmp(input, "Friend") == 0)
		{
			scanf(" %s", emailAddress);
			listFriends(emailAddress);
		}
		else
		{
			scanf(" %s", emailAddress);
			listSuggestions(emailAddress);
		}
	}
	freeAll();
}
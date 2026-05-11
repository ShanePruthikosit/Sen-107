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

#define HASH_SIZE 1009  /* prime number for hash table size */

/* Node in a friendship adjacency list */
typedef struct FriendNode
{
	struct Account *account;   /* pointer to the friend's account */
	struct FriendNode *next;   /* next friend in the list */
} FriendNode;

/* Represents a single user account */
typedef struct Account
{
	char email[55];       /* unique email address */
	char firstName[25];   /* first name */
	char lastName[25];    /* last name */
	FriendNode *friends;  /* head of the friends linked list */
	struct Account *next; /* next account in hash bucket chain */
} Account;

Account *hashTable[HASH_SIZE]; /* hash table for account lookup */

/* Compute a hash value for a given string.
 * Arguments:
 *   str - the string to hash
 * Returns an index into the hash table.
 */
unsigned int hashFunction(char *str)
{
	unsigned int hash = 5381; /* initial value for djb2 algorithm */
	int c = 0;                /* current character */

	while ((c = *str++) != 0)
	{
		hash = ((hash << 5) + hash) + c;
	}
	return hash % HASH_SIZE;
}

/* Look up an account by email address.
 * Arguments:
 *   emailAddress - the email to search for
 * Returns a pointer to the Account if found, or NULL.
 */
Account* findAccount(char *emailAddress)
{
	unsigned int index = hashFunction(emailAddress); /* bucket index */
	Account *current = hashTable[index];             /* walk the chain */

	while (current != NULL)
	{
		if (strcmp(current->email, emailAddress) == 0)
		{
			return current;
		}
		current = current->next;
	}
	return NULL;
}

/* Check whether two accounts are already friends.
 * Arguments:
 *   acc   - the first account
 *   other - the second account
 * Returns 1 if they are friends, 0 otherwise.
 */
int areFriends(Account *acc, Account *other)
{
	FriendNode *current = acc->friends; /* walk the friend list */

	while (current != NULL)
	{
		if (current->account == other)
		{
			return 1;
		}
		current = current->next;
	}
	return 0;
}

/* Add a FriendNode linking owner to friendAcc.
 * Arguments:
 *   owner     - the account gaining a friend
 *   friendAcc - the account being added as a friend
 */
void addFriendNode(Account *owner, Account *friendAcc)
{
	FriendNode *node = (FriendNode *)malloc(sizeof(FriendNode));

	node->account = friendAcc;
	node->next = NULL;

	if (owner->friends == NULL)
	{
		owner->friends = node;
	}
	else
	{
		FriendNode *tail = owner->friends; /* find end of list */

		while (tail->next != NULL)
		{
			tail = tail->next;
		}
		tail->next = node;
	}
}

/* Remove the FriendNode linking owner to friendAcc.
 * Arguments:
 *   owner     - the account losing a friend
 *   friendAcc - the account being removed
 */
void removeFriendNode(Account *owner, Account *friendAcc)
{
	FriendNode *current = owner->friends; /* current node */
	FriendNode *previous = NULL;          /* trailing pointer */

	while (current != NULL)
	{
		if (current->account == friendAcc)
		{
			if (previous == NULL)
			{
				owner->friends = current->next;
			}
			else
			{
				previous->next = current->next;
			}
			free(current);
			return;
		}
		previous = current;
		current = current->next;
	}
}

/* Check if an account is already in a visited array.
 * Arguments:
 *   visited - array of Account pointers already seen
 *   count   - number of entries in visited
 *   acc     - the account to check
 * Returns 1 if found, 0 otherwise.
 */
int isVisited(Account **visited, int count, Account *acc)
{
	int i = 0; /* loop variable */

	for (i = 0; i < count; i++)
	{
		if (visited[i] == acc)
		{
			return 1;
		}
	}
	return 0;
}

/* Creates a new account.
 */
void newAccount(char* emailAddress, char* firstName, char* lastName)
{
	if (findAccount(emailAddress) != NULL)
	{
		printf("Error: Duplicate\n");
		return;
	}

	Account *acc = (Account *)malloc(sizeof(Account));

	strcpy(acc->email, emailAddress);
	strcpy(acc->firstName, firstName);
	strcpy(acc->lastName, lastName);
	acc->friends = NULL;

	unsigned int index = hashFunction(emailAddress); /* bucket index */

	acc->next = hashTable[index];
	hashTable[index] = acc;

	printf("Success\n");
}

/* Deletes an account.
 */
void deleteAccount(char* emailAddress)
{
	unsigned int index = hashFunction(emailAddress); /* bucket index */
	Account *current = hashTable[index];             /* walk the chain */
	Account *previous = NULL;                        /* trailing pointer */

	while (current != NULL)
	{
		if (strcmp(current->email, emailAddress) == 0)
		{
			break;
		}
		previous = current;
		current = current->next;
	}

	if (current == NULL)
	{
		printf("Error: Not Found\n");
		return;
	}

	/* Remove this account from all friends' lists */
	FriendNode *friendNode = current->friends; /* walk friend list */

	while (friendNode != NULL)
	{
		removeFriendNode(friendNode->account, current);
		friendNode = friendNode->next;
	}

	/* Free the account's own friend list */
	FriendNode *temp = NULL; /* temporary for freeing */

	friendNode = current->friends;
	while (friendNode != NULL)
	{
		temp = friendNode;
		friendNode = friendNode->next;
		free(temp);
	}

	/* Remove account from hash chain */
	if (previous == NULL)
	{
		hashTable[index] = current->next;
	}
	else
	{
		previous->next = current->next;
	}

	free(current);
	printf("Success\n");
}

/* Makes two accounts friend of each other.
 */
void addFriend(char* firstEmailAddress, char* secondEmailAddress)
{
	Account *first = findAccount(firstEmailAddress);   /* first account */
	Account *second = findAccount(secondEmailAddress); /* second account */

	if ((first == NULL) || (second == NULL))
	{
		printf("Error: Account Not Found\n");
		return;
	}

	if (strcmp(firstEmailAddress, secondEmailAddress) == 0)
	{
		printf("Error: Can't add friend to self\n");
		return;
	}

	if (areFriends(first, second))
	{
		printf("Error: Accounts are already friends\n");
		return;
	}

	addFriendNode(first, second);
	addFriendNode(second, first);

	printf("Success\n");
}

/*  Unfriends two accounts.
 */
void unfriend(char* firstEmailAddress, char* secondEmailAddress)
{
	Account *first = findAccount(firstEmailAddress);   /* first account */
	Account *second = findAccount(secondEmailAddress); /* second account */

	if ((first == NULL) || (second == NULL))
	{
		printf("Error: Account Not Found\n");
		return;
	}

	if (strcmp(firstEmailAddress, secondEmailAddress) == 0)
	{
		printf("Error: Can't add unfriend self\n");
		return;
	}

	if (!areFriends(first, second))
	{
		printf(
			"Error: Can't unfriend accounts that are not friends\n");
		return;
	}

	removeFriendNode(first, second);
	removeFriendNode(second, first);

	printf("Success\n");
}

/* Prints the account's friends.
 */
void listFriends(char* emailAddress)
{
	Account *acc = findAccount(emailAddress); /* the account */

	if (acc == NULL)
	{
		printf("Error: Account Not Found\n");
		return;
	}

	if (acc->friends == NULL)
	{
		printf("No Friend\n");
		return;
	}

	FriendNode *current = acc->friends; /* walk the friend list */
	int first = 1;                      /* flag for comma formatting */

	while (current != NULL)
	{
		if (!first)
		{
			printf(", ");
		}
		printf("%s %s",
			current->account->firstName,
			current->account->lastName);
		first = 0;
		current = current->next;
	}
	printf("\n");
}

/* Prints the account's friend suggestions.
 */
void listSuggestions(char* emailAddress)
{
	Account *acc = findAccount(emailAddress); /* the account */

	if (acc == NULL)
	{
		printf("Error: Account Not Found\n");
		return;
	}

	int capacity = 16;    /* initial capacity for suggestions array */
	int count = 0;        /* number of suggestions found */
	Account **suggestions = (Account **)malloc(
		sizeof(Account *) * capacity); /* dynamic array */

	FriendNode *friendNode = acc->friends; /* iterate over friends */

	while (friendNode != NULL)
	{
		/* friends of this friend */
		FriendNode *fof = friendNode->account->friends;

		while (fof != NULL)
		{
			Account *candidate = fof->account; /* potential suggestion */

			/* Skip self and existing friends */
			if ((candidate != acc)
				&& (!areFriends(acc, candidate))
				&& (!isVisited(suggestions, count, candidate)))
			{
				/* Grow array if needed */
				if (count >= capacity)
				{
					capacity = capacity * 2;
					suggestions = (Account **)realloc(
						suggestions,
						sizeof(Account *) * capacity);
				}
				suggestions[count] = candidate;
				count++;
			}
			fof = fof->next;
		}
		friendNode = friendNode->next;
	}

	if (count == 0)
	{
		printf("No Friend Suggestion\n");
	}
	else
	{
		int i = 0; /* loop variable */

		for (i = 0; i < count; i++)
		{
			if (i > 0)
			{
				printf(", ");
			}
			printf("%s %s",
				suggestions[i]->firstName,
				suggestions[i]->lastName);
		}
		printf("\n");
	}

	free(suggestions);
}

/* Free the contents of the datastructures used */
void freeAll()
{
	int i = 0; /* loop variable */

	for (i = 0; i < HASH_SIZE; i++)
	{
		Account *current = hashTable[i]; /* current account */

		while (current != NULL)
		{
			Account *nextAcc = current->next; /* save next */
			FriendNode *fn = current->friends; /* friend list */

			while (fn != NULL)
			{
				FriendNode *nextFn = fn->next; /* save next */

				free(fn);
				fn = nextFn;
			}
			free(current);
			current = nextAcc;
		}
		hashTable[i] = NULL;
	}
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
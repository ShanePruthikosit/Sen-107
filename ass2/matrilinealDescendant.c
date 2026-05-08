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

typedef struct Node
{
	char name[25];
	struct Node* children[10];
	int numChildren;
} Node;

Node* root = NULL;

Node* createNode(char* name)
{
	Node* n = (Node*)malloc(sizeof(Node));
	strcpy(n->name, name);
	n->numChildren = 0;
	return n;
}

Node* findNode(Node* cur, char* name)
{
	if (cur == NULL) return NULL;
	if (strcmp(cur->name, name) == 0) return cur;
	for (int i = 0; i < cur->numChildren; i++)
	{
		Node* r = findNode(cur->children[i], name);
		if (r != NULL) return r;
	}
	return NULL;
}

void printAll(Node* n, int* first)
{
	for (int i = 0; i < n->numChildren; i++)
	{
		if (!(*first)) printf(" ");
		*first = 0;
		printf("%s", n->children[i]->name);
		printAll(n->children[i], first);
	}
}

int height(Node* n)
{
	int max = 0;
	for (int i = 0; i < n->numChildren; i++)
	{
		int h = height(n->children[i]);
		if (h > max) max = h;
	}
	return max + 1;
}

void printChains(Node* n, char path[][25], int len, int target)
{
	strcpy(path[len], n->name);
	len++;
	if (len == target)
	{
		for (int i = 0; i < len; i++)
		{
			if (i > 0) printf(" ");
			printf("%s", path[i]);
		}
		printf("\n");
		return;
	}
	for (int i = 0; i < n->numChildren; i++)
	{
		if (height(n->children[i]) + len == target)
			printChains(n->children[i], path, len, target);
	}
}

/* Adds person with a given name at the root.
 */
void addRoot(char* name)
{
	root = createNode(name);
	printf("Added \n");
}

/* Adds person with a given name and mother's name to the tree.
 */
void addNonRoot(char* name, char* motherName)
{
	Node* mom = findNode(root, motherName);
	if (mom == NULL || mom->numChildren >= 10)
	{
		printf("Unsuccessful\n");
		return;
	}
	mom->children[mom->numChildren++] = createNode(name);
	printf("Added\n");
}

/* Prints the person's daughters.
 */
void queryDescendant(char* name)
{
	Node* p = findNode(root, name);
	if (p == NULL || p->numChildren == 0)
	{
		printf("Not Found\n");
		return;
	}
	int first = 1;
	printAll(p, &first);
	printf("\n");
}

/* Prints the longest descendant chain.
 */
void queryLongestDescendantChain()
{
	char path[500][25];
	printChains(root, path, 0, height(root));
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
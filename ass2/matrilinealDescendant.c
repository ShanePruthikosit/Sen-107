/* 
 * matrilinealDescendant.c
 * 
 * Build a simple, non-sorted tree of mother-daughter relationships.
 * Supports adding nodes, querying all descendants of a person,
 * and finding the longest chain of descendants.
 *
 * Created by [Your Name], [Date]
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Node
{
	char name[25];           /* name of the person */
	struct Node* children[10]; /* pointers to daughter nodes */
	int numChildren;         /* number of daughters */
} Node;

Node* root = NULL; /* root of the tree */

/* 
 * Create a new node with the given name.
 * Arguments:
 *   name - the name of the person to create
 * Returns a pointer to the newly created node.
 */
Node* createNode(char* name)
{
	Node* n = (Node*)malloc(sizeof(Node)); /* new node */
	strcpy(n->name, name);
	n->numChildren = 0;
	return n;
}

/* 
 * Search the subtree rooted at cur for a node matching name.
 * Arguments:
 *   cur  - the current node being searched
 *   name - the name to search for
 * Returns a pointer to the matching node, or NULL if not found.
 */
Node* findNode(Node* cur, char* name)
{
	if (cur == NULL)
	{
		return NULL;
	}
	if (strcmp(cur->name, name) == 0)
	{
		return cur;
	}
	for (int i = 0; i < cur->numChildren; i++)
	{
		Node* r = findNode(cur->children[i], name); /* result */
		if (r != NULL)
		{
			return r;
		}
	}
	return NULL;
}

/* 
 * Recursively print all descendants of a node.
 * Arguments:
 *   n     - the current node
 *   first - pointer to flag tracking if first name printed
 */
void printAll(Node* n, int* first)
{
	for (int i = 0; i < n->numChildren; i++)
	{
		if (!(*first))
		{
			printf(" ");
		}
		*first = 0;
		printf("%s", n->children[i]->name);
		printAll(n->children[i], first);
	}
}

/* 
 * Compute the height of the subtree rooted at n.
 * Arguments:
 *   n - the root of the subtree
 * Returns the height (number of nodes on longest path).
 */
int height(Node* n)
{
	int max = 0; /* maximum child height */
	int h = 0;   /* current child height */
	for (int i = 0; i < n->numChildren; i++)
	{
		h = height(n->children[i]);
		if (h > max)
		{
			max = h;
		}
	}
	return max + 1;
}

/* 
 * Recursively print all root-to-leaf chains of a given length.
 * Arguments:
 *   n      - the current node
 *   path   - array storing the current chain of names
 *   len    - current length of the chain
 *   target - the target chain length
 */
void printChains(Node* n, char path[][25], int len, int target)
{
	strcpy(path[len], n->name);
	len++;
	if (len == target)
	{
		for (int i = 0; i < len; i++)
		{
			if (i > 0)
			{
				printf(" ");
			}
			printf("%s", path[i]);
		}
		printf("\n");
		return;
	}
	for (int i = 0; i < n->numChildren; i++)
	{
		if ((height(n->children[i]) + len) == target)
		{
			printChains(n->children[i], path, len, target);
		}
	}
}

/* Adds person with a given name at the root.
 */
void addRoot(char* name)
{
	root = createNode(name);
	printf("Added\n");
}

/* Adds person with a given name and mother's name to the tree.
 */
void addNonRoot(char* name, char* motherName)
{
	Node* mom = findNode(root, motherName); /* mother node */
	if ((mom == NULL) || (mom->numChildren >= 10))
	{
		printf("Unsuccessful\n");
		return;
	}
	mom->children[mom->numChildren++] = createNode(name);
	printf("Added\n");
}

/* Prints the person's descendants.
 */
void queryDescendant(char* name)
{
	Node* p = findNode(root, name); /* person node */
	int first = 1;                  /* flag for spacing */
	if ((p == NULL) || (p->numChildren == 0))
	{
		printf("Not Found\n");
		return;
	}
	printAll(p, &first);
	printf("\n");
}

/* Prints the longest descendant chain.
 */
void queryLongestDescendantChain()
{
	char path[500][25]; /* array to store current chain */
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
/* orgChart
 *
 * Build a corporate hierarchy structure and sorted binary tree
 *
 *  Created by Chavakorn Arunkunarax and Phasit Thanitkul, 2025-01-12
 *  Altered by Sunidhi Pruthikosit, 2026-02-05
 */

 #include <stdio.h>
 #include <string.h>
 #include <stdlib.h>
 #include <ctype.h>
 
 /* Node in the organization chart (general tree).
  * Uses first-child / next-sibling representation.
  */
 typedef struct _OrgNode
 {
     char name[32];        //employee name
     char employeeId[8];   //employee ID 
     char jobTitle[32];    //job title
     struct _OrgNode* parent;      //pointer to supervisor
     struct _OrgNode* firstChild;  //pointer to first child
     struct _OrgNode* nextSibling; //pointer to next sibling
 } OrgNode;
 
 /* Node in the binary search tree.
  * Sorted by concatenation of name + employeeId.
  * Points to the corresponding OrgNode (no duplicated data).
  */
 typedef struct _BSTNode
 {
     char key[40];             //sorting key (name + employeeId)
     OrgNode* orgRef;          //pointer to an org chart node
     struct _BSTNode* left;    //left child
     struct _BSTNode* right;   //right child
 } BSTNode;
 
 OrgNode* orgRoot = NULL; //root of the organization chart
 BSTNode* bstRoot = NULL;   //root of the binary search tree
 
 /* Create a new organization chart node.
  * Arguments:
  *   name       - employee name
  *   employeeId - employee ID string
  *   jobTitle   - job title string
  * Returns a pointer to the newly allocated OrgNode.
  */
 OrgNode* createOrgNode(char* name, char* employeeId, char* jobTitle)
 {
     OrgNode* node = (OrgNode*)malloc(sizeof(OrgNode));
     if (node == NULL)
     {
         return NULL;
     }
     strcpy(node->name, name);
     strcpy(node->employeeId, employeeId);
     strcpy(node->jobTitle, jobTitle);
     node->parent = NULL;
     node->firstChild = NULL;
     node->nextSibling = NULL;
     return node;
 }
 
 /* Insert a node into the binary search tree.
  * Arguments:
  *   root   - pointer to the current BST root
  *   key    - the sorting key (name + employeeId)
  *   orgRef - pointer to the corresponding OrgNode
  * Returns the (possibly updated) root of the BST.
  */
 BSTNode* insertBST(BSTNode* root, char* key, OrgNode* orgRef)
 {
     if (root == NULL)
     {
         BSTNode* node = (BSTNode*)malloc(sizeof(BSTNode));
         if (node == NULL)
         {
             return NULL;
         }
         strcpy(node->key, key);
         node->orgRef = orgRef;
         node->left = NULL;
         node->right = NULL;
         return node;
     }
     if (strcmp(key, root->key) < 0)
     {
         root->left = insertBST(root->left, key, orgRef);
     }
     else 
     {
         root->right = insertBST(root->right, key, orgRef);
     }
     return root;
 }
 
 /* Search the BST for a node matching the given key.
  * Arguments:
  *   root - pointer to the current BST root
  *   key  - the sorting key to search for
  * Returns pointer to the matching BSTNode, or NULL if not found.
  */
 BSTNode* searchBST(BSTNode* root, char* key)
 {
     int cmp = 0; //comparison result
     if (root == NULL)
     {
         return NULL;
     }
     cmp = strcmp(key, root->key);
     if (cmp == 0)
     {
         return root;
     }
     else if (cmp < 0)
     {
         return searchBST(root->left, key);
     }
     else
     {
         return searchBST(root->right, key);
     }
 }
 
 /* Find the minimum node in a BST subtree.
  * Arguments:
  *   node - root of subtree to search
  * Returns pointer to the node with the smallest key.
  */
 BSTNode* findMinBST(BSTNode* node)
 {
     if (node == NULL)
     {
         return NULL;
     }
     while (node->left != NULL)
     {
         node = node->left;
     }
     return node;
 }
 
 /* Remove a node with the given key from the BST.
  * Arguments:
  *   root - pointer to the current BST root
  *   key  - the sorting key to remove
  * Returns the (possibly updated) root of the BST.
  */
 BSTNode* removeBST(BSTNode* root, char* key)
 {
     int cmp = 0;           //comparison result
     BSTNode* temp = NULL;  //temporary node for swapping
 
     if (root == NULL)
     {
         return NULL;
     }
     cmp = strcmp(key, root->key);
     if (cmp < 0)
     {
         root->left = removeBST(root->left, key);
     }
     else if (cmp > 0)
     {
         root->right = removeBST(root->right, key);
     }
     else
     {
         if (root->left == NULL)
         {
             temp = root->right;
             free(root);
             return temp;
         }
         else if (root->right == NULL)
         {
             temp = root->left;
             free(root);
             return temp;
         }
         temp = findMinBST(root->right);
         strcpy(root->key, temp->key);
         root->orgRef = temp->orgRef;
         root->right = removeBST(root->right, temp->key);
     }
     return root;
 }
 
 /* Find an OrgNode by name and employeeId using the BST.
  * Arguments:
  *   name       - employee name
  *   employeeId - employee ID
  * Returns pointer to the OrgNode, or NULL if not found.
  */
 OrgNode* findOrgNode(char* name, char* employeeId)
 {
     char key[40];          //combined key for BST search
     BSTNode* result = NULL;//search result from BST
     snprintf(key, sizeof(key), "%s_%s", name, employeeId);
     result = searchBST(bstRoot, key);
     if (result != NULL)
     {
         return result->orgRef;
     }
     return NULL;
 }
 
 
 /* Free all nodes in the BST.
  * Arguments:
  *   node - current BST node to free
  */
 void freeBST(BSTNode* node)
 {
     if (node == NULL)
     {
         return;
     }
     freeBST(node->left);
     freeBST(node->right);
     free(node);
 }
 
 /* Free all nodes in the org chart tree.
  * Arguments:
  *   node - current org node to free
  */
 void freeOrg(OrgNode* node)
 {
     if (node == NULL)
     {
         return;
     }
     freeOrg(node->firstChild);
     freeOrg(node->nextSibling);
     free(node);
 }
 
 /* Adds employee to the corporate hierarchy structure and sorted binary tree
  */
 void addEmployee(char* name, char* employeeId, char* jobTitle, char* supervisorName, char* supervisorId)
 {
     OrgNode* newNode = NULL;      //new employee node
     OrgNode* supervisor = NULL;   //supervisor node
     OrgNode* child = NULL;        //for traversing supervisor's children
     char key[40];                 //combined key for BST
 
     if ((strcmp(supervisorName, "--") == 0) &&
         (strcmp(supervisorId, "--") == 0))
     {
         newNode = createOrgNode(name, employeeId, jobTitle);
         if (newNode == NULL)
         {
             return;
         }
         if (orgRoot != NULL)
         {
             newNode->firstChild = orgRoot->firstChild;
             child = newNode->firstChild;
             while (child != NULL)
             {
                 child->parent = newNode;
                 child = child->nextSibling;
             }
             snprintf(key, sizeof(key), "%s_%s",
                      orgRoot->name, orgRoot->employeeId);
             bstRoot = removeBST(bstRoot, key);
             free(orgRoot);
         }
         orgRoot = newNode;
     }
     else
     {
         supervisor = findOrgNode(supervisorName, supervisorId);
         if (supervisor == NULL)
         {
             printf("cannot_add %s %s\n", name, employeeId);
             return;
         }
         newNode = createOrgNode(name, employeeId, jobTitle);
         if (newNode == NULL)
         {
             return;
         }
         newNode->parent = supervisor;
 
         if (supervisor->firstChild == NULL)
         {
             supervisor->firstChild = newNode;
         }
         else
         {
             child = supervisor->firstChild;
             while (child->nextSibling != NULL)
             {
                 child = child->nextSibling;
             }
             child->nextSibling = newNode;
         }
     }
 
     snprintf(key, sizeof(key), "%s_%s", name, employeeId);
     bstRoot = insertBST(bstRoot, key, newNode);
 }
 
 /* Prints the corporate hierarchy structure, pre-order
  * Arguments:
  *   node  - current node to print
  *   level - depth level for indentation (3 dots per level)
  */
 void printCorporateHierarchy(OrgNode* node, int level)
 {
     if (node == NULL)
     {
         return;
     }
     for (int i = 0; i < level; i++)
     {
         printf("...");
     }
     printf("%s %s %s\n", node->name, node->employeeId,
            node->jobTitle);
     printCorporateHierarchy(node->firstChild, level + 1);
     printCorporateHierarchy(node->nextSibling, level);
 }
 
 /* Prints the sorted list of employees by in-order traversal
  * Arguments:
  *   node - current BST node
  */
 void printSortedList(BSTNode* node)
 {
     if (node == NULL)
     {
         return;
     }
     printSortedList(node->left);
     printf("%s %s %s\n", node->orgRef->name,
            node->orgRef->employeeId,
            node->orgRef->jobTitle);
     printSortedList(node->right);
 }
 
 /* Searches for an employee in the corporate hierarchy structure
  */
 void searchEmployee(char* name, char* employeeId)
 {
     OrgNode* found = findOrgNode(name, employeeId);
     if (found == NULL)
     {
         printf("not_found\n");
         return;
     }
     if (found->parent == NULL)
     {
         printf("%s\n", found->jobTitle);
     }
     else
     {
         printf("%s %s %s\n", found->jobTitle,
                found->parent->name,
                found->parent->employeeId);
     }
 }
 
 /* Free the contents of the datastructures used */
 void freeAll()
 {
     freeBST(bstRoot);
     bstRoot = NULL;
     freeOrg(orgRoot);
     orgRoot = NULL;
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
         scanf("\n%31s %7s %31s %31s %7s", name, employeeId, jobTitle, supervisorName, supervisorId);
         addEmployee(name, employeeId, jobTitle, supervisorName, supervisorId);
     }
 
     printCorporateHierarchy(orgRoot, 0);
 
 
     for (int i = 0; i < numQuestions; i++)
     {
         scanf("\n%31s %7s", name, employeeId);
         searchEmployee(name, employeeId);
     }
 
     printSortedList(bstRoot);
 
     freeAll();
 
     return 0;
 }
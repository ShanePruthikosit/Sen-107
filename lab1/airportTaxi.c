/* Airport Taxi Queue
 * Template for Lab 1.
 *
 * Created by Pasin Manurangsi, 2025-01-08
 * Edited by Sunidhi Pruthikosit, 2026-01-26
 */
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>

//node structure
 typedef struct Node{
    char* name;
	int count;
	struct Node* next;
} Node;

//Queue structure
typedef struct {
	Node* front;
	Node* rear;
} QueueStruct;

QueueStruct* Queue;

/* Create the Enqueue function: add a taxi party to the queue.
  * Arguments:
  *			count		- the number of people in the party
  *			name 		- the name of the party
 */
 void Enqueue(int count, char name[])
 {
	 Node* newNode = (Node*)malloc(sizeof(Node));
	 newNode -> count = count;
	 newNode -> name = (char*)malloc(sizeof(strlen(name) + 1));
	 strcpy(newNode -> name, name);
	 newNode -> next = NULL;
	 if(Queue -> rear == NULL)
	 {
		 Queue -> front = newNode;
		 Queue -> rear = newNode;
	 }
	 else
	 {
		 Queue -> rear -> next = newNode;
		 Queue -> rear = newNode;
	 }
 }	

/* Create the Dequeue function: remove the first taxi party from the queue.
 */
 void Dequeue()
 {
	 Node* temp = Queue -> front;
	 printf("Taxi departs with %s and their party of %i\n", temp -> name, temp -> count);
	 Queue -> front = Queue -> front -> next;
	 if(Queue -> front == NULL)
	 {
		 Queue -> rear = NULL;
	 }
    free(temp->name);  
	 free(temp);
 }

 /* Handle an arrival of a taxi. 
  */
void taxiArrival()
{
	if(Queue -> front != NULL)
	{
		Dequeue();
	}
	else
	{
		printf("Empty Queue\n");
	}
}
 
 /* Handles an arrival of a new party.
  * Arguments:
  *			count		- the number of people in the party
  *			name 		- the name of the party
  */
void partyArrival(int count, char name[])
{
	Enqueue(count, name);
}	

/* Free the contents of the queue */
void freeAll()
{
    while(Queue->front != NULL)
    {
        Node* temp = Queue->front;
        Queue->front = Queue->front->next;
        free(temp->name);  
        free(temp);      
	}
	free(Queue);
}

/* Main function loops for however many timesteps is specified, 
 * reading from the standard input and handling taxi / party arrivals
 */
int main(int argc, char* argv[])
{
	Queue = (QueueStruct*)malloc(sizeof(QueueStruct));
	Queue -> front = NULL;
	Queue -> rear = NULL;

 	int timesteps; // The total number of timesteps
 	char input[10]; // For the input prefix "Taxi" or "Party"
 	char name[25]; // The party name
 	int rank; // The party's status
 	int count; // The number of people in the party
 	scanf("%d", &timesteps);
	printf("Total timesteps: %d\n", timesteps);
 	for (int i = 0 ; i < timesteps ; i ++)
 	{
 		scanf("\n%s", input);
 		if (strcmp(input, "Taxi") == 0)
 		{
 			taxiArrival();
 		}
 		else
 		{
 			scanf(" %d %s", &count, name);
 			partyArrival(count, name);
 		}
 	}
 	freeAll();
}

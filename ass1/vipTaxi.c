/* VIP Taxi Queue
 * Template for Fundamental Data Structures, skill 00010.
 *
 * Created by Pasin Manurangsi, 2025-01-08
 * Modified by Sunidhi Pruthikosit, 2025-01-09
 */
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>

 //Queue Node structure
 typedef struct QNode{
    char* name;
	int rank;
	int count;
	struct QNode* next;
} QNode;

//Queue structure
typedef struct QueueStruct{
	QNode* front;
	QNode* rear;
	int rank;
	struct QueueStruct* next;
} QueueStruct;

//Stack structure
typedef struct {
	QueueStruct* top;
} StackStruct;

StackStruct* Stack;


// Adds a new party to the queue on top of the stack
void Enqueue(int count, char name[])
{
	QueueStruct* Queue = Stack -> top;
	QNode* newNode = (QNode*)malloc(sizeof(QNode));
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
	printf("Accepted\n");
}	

//Pops the queue off from the stack
void Pop()
{
	QueueStruct* temp = Stack -> top;
	Stack -> top = Stack -> top -> next;

	free(temp);
}

// Removes a party from the front of the queue on top of the stack
void Dequeue()
{
	QueueStruct* Queue = Stack -> top;
	QNode* temp = Queue -> front;
	printf("Taxi departs with %s and their party of %i\n", temp -> name, temp -> count);
	Queue -> front = Queue -> front -> next;
	if(Queue -> front == NULL)
	{
		Pop();
	}
   free(temp->name);  
   free(temp);
}

// Adds a new queue to the stack
void Push(StackStruct* Stack,int rank, int count, char name[])
{
	QueueStruct* newQueue = (QueueStruct*)malloc(sizeof(QueueStruct));
	newQueue -> front = NULL;
	newQueue -> rear = NULL;
	newQueue -> next = Stack -> top;
	newQueue -> rank = rank;
	Stack -> top = newQueue;
	Enqueue(count, name);
}

 // Handle an arrival of a taxi. 
void taxiArrival()
{
	QueueStruct* Queue = Stack -> top;
	if (Queue == NULL)
	{
		printf("Empty Queue\n");
	}
	else
	{
		Dequeue();
	}
}

//handle an arrival of a party.
void partyArrival(int rank, int count, char name[])
{
	QueueStruct* Queue = Stack -> top;
	if (Queue == NULL || Queue -> rank < rank)
	{
		Push(Stack, rank, count, name);
	}
	else if (Queue -> rank == rank)
	{
		Enqueue(count, name);
	}
	else
	{
		printf("Rejected\n");
	}
	
}	

/* Free the contents of the datastructures used */
void freeAll()
{
    while (Stack->top != NULL)
    {
        QueueStruct* currentQueue = Stack->top;
        
        // Free all nodes in the current queue
        while (currentQueue->front != NULL)
        {
            QNode* temp = currentQueue->front;
            currentQueue->front = currentQueue->front->next;
            free(temp->name);
            free(temp);
        }
        
        // Remove the queue from the stack
        Stack->top = Stack->top->next;
        free(currentQueue);
    }
    
    // Free the stack itself
    free(Stack);
}

/* Main function loops for however many timesteps is specified, 
 * reading from the standard input and handling taxi / party arrivals
 */
int main(int argc, char* argv[])
{
	Stack = (StackStruct*)malloc(sizeof(StackStruct));
	Stack->top = NULL;

 	int timesteps; // The total number of timesteps
 	char input[25]; // For the input prefix "Taxi" or "Party"
 	char name[25]; // The party name
 	int rank; // The party's status
 	int count; // The number of people in the party
 	scanf("%d", &timesteps);
 	for (int i = 0 ; i < timesteps ; i ++)
 	{
 		scanf("\n%s", input);
 		if (strcmp(input, "Taxi") == 0)
 		{
 			taxiArrival();
 		}
 		else
 		{
 			scanf(" %d %d %s", &rank, &count, name);
 			partyArrival(rank, count, name);
 		}
 	}
 	freeAll();
}

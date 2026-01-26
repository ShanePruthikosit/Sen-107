/* VIP Taxi Queue
 * Template for Fundamental Data Structures, skill 00010.
 *
 * Created by Pasin Manurangsi, 2025-01-08
 */
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>

 /* Handle an arrival of a taxi. 
  */
void taxiArrival()
{
	// ************** Please change the code below to your code **************
 	printf("Please add your code to handle taxi arrival.\n");
}
 
 /* Handles an arrival of a new party.
  * Arguments:
  * 		rank 		- the status of the party assumed to be one of 1, 2, 3, 4, 5
  *			count		- the number of people in the party
  *			name 		- the name of the party
  */
void partyArrival(int rank, int count, char name[])
{
	// ************** Please change the code below to your code **************
 	printf("Please add your code to handle party arrival.\n");
}	

/* Free the contents of the datastructures used */
void freeAll()
{
	// ************** Please change the code below to your code **************
	printf("Please add your code to free all datastructures.\n");
}

/* Main function loops for however many timesteps is specified, 
 * reading from the standard input and handling taxi / party arrivals
 */
int main(int argc, char* argv[])
{
 	int timesteps; // The total number of timesteps
 	char input[10]; // For the input prefix "Taxi" or "Party"
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

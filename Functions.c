#include "Headers.h"

/* ---------------------------------------------------------------------------------- */
/*                                   REQUIRED FUNCTIONS                               */
/* ---------------------------------------------------------------------------------- */

/*---------------------------------------------!ATTENTION!-------------------------------------------------*/
/*I HAVE USED ONLY VOID INPUTS. YOU DO NOT HAVE TO DO THAT YOU CAN USE WHATEVER INPUTS YOU DEEM NECESSARY!!*/
/*---------------------------------------------!ATTENTION!-------------------------------------------------*/

struct Video_Game_Ratings
{
	char name[50];					 // This is the name of the video game
	float rating;					 // This is the rating out of 10
	int year;						 // This is the year the game was released
	struct Video_Game_Ratings *next; // This is a pointer pointing to the next entry in the linked list
	struct Video_Game_Ratings *prev; // This is a pointer pointing to the previous entry in the linked list
									 // This is the definition of your lined list, you must be able to add entries for this and have it be traversable
};

/* ---------- core linked list helpers ---------- */

/*You can make these on your own, or not use them at all. I would recommend using them so your coe becomes less confusing*/

struct Video_Game_Ratings *find_repeated_name(struct Video_Game_Ratings *head, char *newname)
{
	if (head == NULL)
		return NULL;

	if (strcmp(head->name, newname) == 0)
	{
		return head;
	}

	return find_repeated_name(head->next, newname);
}

// This function implements selection sort.
// Head is the start of the whole link list.
// Everything before curr is sorted and after(including) curr is unsorted
// The last input node is picked base on different sorting funcitons (e.g. highest rating in unsorted list for sorting rating)
struct Video_Game_Ratings *swapNodes(struct Video_Game_Ratings *head, struct Video_Game_Ratings *curr, struct Video_Game_Ratings *node)
{
	// curr == node and head == node is filtered in each individual function already
	// list with length of one is handled already
	// remove the "node" from it's original spot

	if (node->next == NULL)
	{
		node->prev->next = node->next;
	}
	else
	{
		node->next->prev = node->prev;
		node->prev->next = node->next;
	}
	if (curr == head)
	{
		head = node;
		curr->prev = node;
		node->next = curr;
		node->prev = NULL;
	}
	else
	{
		node->prev = curr->prev;
		node->next = curr;
		curr->prev->next = node;
		curr->prev = node;
	}

	// add node to the end of sorted list(the spot before curr)

	return head;
}

struct Video_Game_Ratings *intialize_LL(void)
{
	/*
		Initialize the linked list to empty.
		Returns: head pointer (NULL if empty).
	*/
	struct Video_Game_Ratings *head = NULL;

	return head;
}

struct Video_Game_Ratings *remove_entry(struct Video_Game_Ratings *head)
{
	/*
		Remove entries.
		Option 1: remove FIRST entry matching a given name (case-sensitive).
		Option 2: remove ALL invalid entries (bad name/rating/year). 

		Returns: head pointer (unchanged on error).
	*/

	// Invalid entry should be detected when inputing information

	// Remove matching given name
	char name[50];
	printf("Name of the game: ");
	fgets(name, sizeof(name), stdin);
	name[strlen(name) - 1] = '\0';
	struct Video_Game_Ratings *removeNode = find_repeated_name(head, name); // Check if game exist
	if (removeNode == NULL)
	{
		printf("ERROR: Game doesn't exist in list. Please try again.\n");
		return head;
	}
	if(removeNode ==head && removeNode->next == NULL) // If removing the only node in list
	{
		free(removeNode);
		return NULL;
	}
	if(removeNode ==head){ // If the removing node is head
		removeNode->next->prev =NULL;
		head = head->next;
		
	}
	else if(removeNode->next == NULL){ // If the removing node is last
		removeNode->prev->next = NULL;
		
	}
	else{
		removeNode->prev->next = removeNode->next;
		removeNode->next->prev = removeNode->prev;
	}

	free(removeNode);

	return head;
}

struct Video_Game_Ratings *add_entry(struct Video_Game_Ratings *head)
{
	/*
		Add one entry to the linked list (interactive).
		On validation error, list is unchanged and hw2_last_error is set.

		Returns: head pointer (unchanged on error).
	*/
	char name[25];
	printf("Name of the game(20 characters max including space): ");
	fgets(name, sizeof(name), stdin);
	name[strlen(name) - 1] = '\0';
	while(strlen(name)>20){ // deal with incorrect input
		printf("ERROR: Invalid input. Please follow the name length limit.\n");
		printf("Name of the game(20 characters max including space): ");
		fgets(name, sizeof(name), stdin);
		name[strlen(name) - 1] = '\0'; // change \n to \0 to represent a string
	}
	// Check if the game exist already
	if (find_repeated_name(head, name) != NULL)
	{
		printf("ERROR: Game already added"); // print error message
		return head;						 // return unchanged head pointer
	}

	struct Video_Game_Ratings *new = (struct Video_Game_Ratings*)malloc(sizeof(struct Video_Game_Ratings));
	strcpy(new->name, name);
	new->next = head; // Add new node to the front of the list

	if (head != NULL)
	{
		head->prev = new;
	}
	new->prev = NULL;

	// Get year and rating from user input
	int newyear = -1;
	char tmpString[25], tmp[10];

	printf("Year of the game: ");
	fgets(tmpString, sizeof(tmpString), stdin); // Consumes the whole line including 'Enter'
	while (sscanf(tmpString, "%d %s", &newyear, tmp) != 1 || newyear == -1 ) // deal with incorrect input
	{
		printf("ERROR: Invalid year input. Please enter again.\n");
		printf("Year of the game: ");
		fgets(tmpString, sizeof(tmpString), stdin); // Consumes the whole line including 'Enter'
	}

	new->year = newyear;
	float newratings = -1;
	printf("Ratings of the game(will be rounded to one decimal place): ");
	fgets(tmpString, sizeof(tmpString), stdin); // Consumes the whole line including 'Enter'
	while (sscanf(tmpString, "%f %s", &newratings, tmp) != 1 || newratings == -1) // deal with incorrect input
	{
		printf("ERROR: Invalid ratings input. Please enter again\n");
		printf("Ratings of the game(will be rounded to one decimal place): ");
		fgets(tmpString, sizeof(tmpString), stdin); // Consumes the whole line including 'Enter'
	}
	new->rating = newratings;
	printf("\nGame successfully added to the first entry of list.\n");
	return new;
}

struct Video_Game_Ratings *sort_by_rating(struct Video_Game_Ratings *head)
{
	/*
		Sort linked list by rating using SELECTION SORT.
		Default: descending (highest rating first).

		Returns: head pointer (unchanged on error).
	*/
	struct Video_Game_Ratings *curr = head;

	while (curr->next != NULL)
	{
		struct Video_Game_Ratings *tmp = curr;
		struct Video_Game_Ratings *highest = curr;
		// find highest rating node in the unsorted list
		while (tmp != NULL)
		{
			if (tmp->rating > highest->rating)
			{
				highest = tmp;
			}
			tmp = tmp->next;
		}

		// check edge cases which doesn't require "swapNodes" function
		// doesn't need to consider these cases again in the "swapNodes" function
		if (highest == head || curr == highest)
		{
			curr = curr->next;
		}
		else
		{
			head = swapNodes(head, curr, highest);
		}
	}
	printf("\nGame successfully sorted by rating from high to low.\n");
	return head;
}

struct Video_Game_Ratings *sort_by_year(struct Video_Game_Ratings *head)
{
	/*
		Sort linked list by year using SELECTION SORT.
		Default: ascending (oldest -> newest).

		Returns: head pointer (unchanged on error).
	*/
	struct Video_Game_Ratings *curr = head;

	while (curr->next != NULL)
	{
		struct Video_Game_Ratings *tmp = curr; 
		struct Video_Game_Ratings *oldest = curr;
		// find oldest year node in the unsorted list
		while (tmp != NULL)
		{
			if (tmp->year < oldest->year)
			{
				oldest = tmp;
			}
			tmp = tmp->next;
		}
		// check edge cases which doesn't require "swapNodes" function
		// doesn't need to consider these cases again in the "swapNodes" function
		if (curr == oldest || oldest == head)
		{
			curr = curr->next;
		}

		else
		{
			head = swapNodes(head, curr, oldest);
		}
	}
	printf("\nGame successfully sorted by year from oldest to newest.\n");

	return head;
}

struct Video_Game_Ratings *sort_by_name(struct Video_Game_Ratings *head)
{
	/*
		Sort linked list by name (A-Z) using SELECTION SORT.

		Returns: head pointer (unchanged on error).
	*/
	struct Video_Game_Ratings *curr = head;

	while (curr->next != NULL)
	{
		struct Video_Game_Ratings *tmp = curr;
		struct Video_Game_Ratings *lowest = curr;
		// find lowest ACII for name in the unsorted list
		while (tmp != NULL)
		{
			if (strcmp(tmp->name, lowest->name) < 0)
			{
				lowest = tmp;
			}
			tmp = tmp->next;
		}

		// check edge cases which doesn't require "swapNodes" function
		// doesn't need to consider these cases again in the "swapNodes" function
		if (curr == lowest || lowest == head)
		{
			curr = curr->next;
		}
		else
		{
			head = swapNodes(head, curr, lowest);
		}
	}

	printf("\nGame successfully sorted by name(A-Z).\n");

	return head;
}

struct Video_Game_Ratings *display_linked_list(struct Video_Game_Ratings *head)
{
	/*
		Display the linked list in a readable table and show memory locations.
		Shows:
		- Head pointer address
		- Each node's address and next pointer
		- Name, rating, year
	*/
	if(head == NULL)
	{
		printf("ERROR: No game in list. Please add game first.\n");
		
		return head;
	}
	struct Video_Game_Ratings *curr = head;
	printf("-------------------------------------------------------------------------------------\n");

	printf("%-20s %-20s %-23s %-8s %-8s \n",  "Address", "Next Address", "Game Title", "Rating", "year");
	printf("-------------------------------------------------------------------------------------\n");
	while (curr != NULL)
	{

		printf("%-20p %-20p %-23s %-8.1f %-8d \n",  curr, curr->next, curr->name, curr->rating, curr->year);

		curr = curr->next;
	}
	return head;
}

void freememory(struct Video_Game_Ratings *head)
{
	if (head->next == NULL)
	{
		free(head);
		return;
	}

	struct Video_Game_Ratings *tmp = head->next;
	free(head);
	freememory(tmp);
	return;
}

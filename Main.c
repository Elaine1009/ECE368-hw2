#include "Functions.c"

/* ------------------------------- main ------------------------------- */
int main()
{

	/* Start with a known empty list */
	struct Video_Game_Ratings *head = intialize_LL();

	// 1. Add game
	// 2. Remove game
	// 3. Sort by rating
	// 4. Sort by year
	// 5. Sort by name
	// 6. Display current list
	// 7. Exit program
	int running = 1;

	while (running)
	{
		int choice = -1;
		char tmp[10];
		printf("-----------------------------------------------------------\n");

		printf("Menu:\n");

		printf("1. Add game\n2. Remove game\n3. Sort by rating\n4. Sort by year\n5. Sort by name\n6. Display current list\n7. Exit program\n");
		char tmpString[10];
		printf("Enter your choice: ");
		fgets(tmpString, sizeof(tmpString), stdin); // Consumes the whole line including 'Enter'
		while (sscanf(tmpString, "%d %s", &choice, tmp) != 1 || (choice < 1 || choice > 7))
		{
			printf("ERROR: Invalid choice. Please try enter again.\n");
			printf("-------------------------------------------------------------------------------------\n");

			printf("Menu:\n");

			printf("1. Add game\n2. Remove game\n3. Sort by rating\n4. Sort by year\n5. Sort by name\n6. Display current list\n7. Exit program\n");
			printf("-------------------------------------------------------------------------------------\n");

			printf("Enter your choice: ");
			fgets(tmpString, sizeof(tmpString), stdin); // Consumes the whole line including 'Enter'
			printf("-------------------------------------------------------------------------------------\n");
		}
		switch (choice)
		{
		case 1:
			head = add_entry(head);
			break;
		case 2:
			head = remove_entry(head);
			break;
		case 3:
			if (head == NULL)
			{
				printf("ERROR: No game to sort. Please add game to list first.\n");
			}
			if (head->next == NULL)
			{
				printf("Only one game in list.\n");
			}
			head = sort_by_rating(head);
			break;
		case 4:
			head = sort_by_year(head);
			break;
		case 5:
			head = sort_by_name(head);
			break;
		case 6:
			head = display_linked_list(head);
			break;
		case 7:
			running = 0;
			freememory(head);
			break;
		}
	}

	return 0;
}
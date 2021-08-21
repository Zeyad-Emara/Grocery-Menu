#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//structure for item
struct item {
	int id;
	char name [20];
	double cost;
	char category;
	struct item *next;
};



typedef struct item LIST;//making synonym for struct item to be LIST to abbreviate struct item
//function prototypes
void display_list_unsort(LIST *head);//function to display the linked list unsorted
add_item(LIST *head);//function to add an item to the linked list
int search_item_id(LIST *head, int id_search);//function to search for item id used when adding a new item if the new item's id is already in use
int search_item_name(LIST *head, char name_search[], int recv_type);//function to search for item name used when adding a new item if the new item's name is already in use and used also for searching for an item in the list
delete_item(LIST *head, int item_id);//function to search for an item id and delete the whole node if found
change_cost(LIST *head, int item_id);//function to search for an item id and change the cost of that item according to user input
void display_list_sorted(LIST *head);//function to display the linked list sorted by id ascending
read_file(LIST *head, char *filename);//function to append list from file of the users input
save_file(LIST *head, char *filename);//function to save all current nodes in the list to a file of the users input

int main()
{
    LIST *head = NULL;//pointer to the first node in the linked list initialized to NULL
    int save_flag;//variable to store a 1 or 0 depending on weather any changes have been made to the list
    int save_choice;//variable to store user choice on weather to save list to file or no
	char filename[30];//variable to store the name of the file to access to append to list
	char save_filename[30];//variable to store the name of the file which the list will be saved to
	int loop1_counter = 0;//loop counter to be set to 1 once the user enters a valid file name
	int choice;//variable to store users input for choosing from the menu
	FILE *fp;//pointer to file
	char preview_file;//variable to store character by character to display the contents of the file
    char name_search[20];//variable to hold the name of item user wants to search for
    int send_type = 0;//variable to hold the send type of the search request so it can determine weather to search for an item with the same name in the list or to check if the added item has the same name as an existing item
    int id_del;//variable to hold id of the users input that is to be deleted
    int id_cost;//variable to hold cost of the users input to be changed
    int sort_choice;//variable to determine weather to sort the list or not based on user input

    printf("Welcome to the grocery store!\n");

loop1:
//prompting user to enter a file name
	printf("\nPlease input the name of file and extension you would like to load into stock\n\n");

	do
	{
        //checking for users filename if not found repeat until a valid filename is entered
		scanf("%s",&filename);

		fp=fopen(filename, "r");

		if(fp==NULL)
		{
			printf("%s" " file NOT FOUND!\nPlease make sure file exists or file extension is correct\n\n",filename);
			goto loop1;
		}

		else
		{
			printf("\n" "%s" " has been properly loaded into the database!\n\n",filename);
			printf("File Contents:\n\n");
			loop1_counter++;
			save_flag = 0;
			head = read_file(head, filename);//if file opened pass the head and file name to read_file function to append list from file
		}

		do
		{
            //display file contents to user
			preview_file=getc(fp);
			printf("%c",preview_file);
		}
		while(preview_file!=EOF);
		fclose(fp);
	}
	while(loop1_counter = 0);


loop2:

	while(1)
	{
	    printf("\n---------------------------------------------------\n");
		printf("\n\nPlease make one of the following selections: \n");
		printf("1. Add new item\n");
		printf("2. Delete item\n");
		printf("3. Change the cost of an item\n");
		printf("4. Search for item\n");
		printf("5. Display inventory details\n");
		printf("6. Quit\n\n");

		scanf("%d",&choice);
        //preform the tasks in the menu corresponding to user input if any invalid input is given display warning and show the menu again
		switch(choice)
		{
			case 1:
			    if (save_flag == 0)
                {
                    save_flag = save_flag + 1;//if any change occurs change the save flag to 1
                }
                head = add_item(head);//pass the head to add_item function to be able to append a new item to the list and return head
				goto loop2;

			case 2:
			    if (save_flag == 0)
                {
                    save_flag = save_flag + 1;
                }
			    printf("\nPlease enter the ID of the item you want to delete\n");
			    scanf("%d", &id_del);
			    head = delete_item(head, id_del);//pass head and id of the item that is to be searched for and deleted once found to the delete_item function and return head
                goto loop2;

			case 3:
			    if (save_flag == 0)
                {
                    save_flag = save_flag + 1;
                }
			    printf("\nPlease enter the ID of item you want to change the cost of\n");
			    scanf("%d", &id_cost);
			    change_cost(head, id_cost);//pass head and id of the item that is to be searched for and change the cost once found to the change_cost function
				goto loop2;

			case 4:
			    printf("\nPlease enter the name of the item you are searching for(case sensitive)\n");
			    scanf("%s",&name_search);
			    send_type = 1;
			    if(search_item_name(head,name_search,send_type) == 2)//pass head and name to searched for and the send type to the name search function and check the function return
                {
                    printf("\nItem Found!\n");
                }
				goto loop2;

			case 5:
			    while(1)
                    {
                        printf("\nWould you like to display the list sorted (sorted in ascending order by ID)?Input 1 to display sorted or input 2 to display unsorted\n");
                        scanf("%d",&sort_choice);
                        switch(sort_choice)
                        {
                            case 1:
                                display_list_sorted(head);//display the sorted list
                                goto loop2;
                            case 2:
                                display_list_unsort(head);//display the unsorted list
                                goto loop2;
                            default:
                                printf("\nError! please choose a valid option\n");

                        }
                    }

			case 6://check if any changes made(save_flag is not 0) and ask the user weather he wants to save and is he is to save which file should be saved to
			    if (save_flag != 0)
                {
                    while(1)
                    {
                        printf("\nSome changes have been made to the list would you like to save to a file?\nInput 1 to save or input 2 to exit without saving\n");
                        scanf("%d",&save_choice);
                        switch(save_choice)
                        {
                            case 1:
                                printf("\nPlease enter file name and extension\n");
                                scanf("%s", save_filename);
                                save_file(head, save_filename);//passing head and file name to save_file function
                                exit(1);//terminating the program once saved
                                printf("\nSaved successfully to file ""s"" Goodbye!\n", save_filename);
                            case 2:
                                printf("\nGoodbye!\n");
                                exit(1);
                            default:
                                printf("\nError! please choose a valid option\n");

                        }
                    }
                }
                printf("\nGoodbye!\n");
                exit(1);
				goto loop2;

			default:

				printf("\nError! please choose a valid option\n");

				goto loop2;
		}
	}



}

add_item(LIST *head)
{
    //declaring variables to be added to the list once checked for any similarity with an existing item
    int new_id = 0;
	char new_name[20] = "";
	double new_cost = 0;
	char new_catg;
	int send_type = 0;
    printf("\nPlease enter the id of the item you want to add\n");
    scanf("%d",&new_id);
    printf("\nPlease enter the name of the item you want to add\n");
    scanf("%s",&new_name);
    printf("\nPlease enter the cost of the item you want to add\n");
    scanf("%lf",&new_cost);
    printf("\nPlease enter the category of the item you want to add\n");
    scanf("%s",&new_catg);
    //searching for the new id and name if they already exist in the list
    search_item_id(head, new_id);
    search_item_name(head, new_name, send_type);

    if (search_item_id(head, new_id) == 0 && search_item_name(head, new_name, send_type) == 0)//if the return of both the id and name searches 0 then add the new item to the list(item is new and no other item share the same id or name)
    {
        new_catg = toupper(new_catg);
        LIST *current_item, *new_item;
        new_item = (LIST *)malloc(sizeof(LIST));//allocating memory for the new item
        new_item->id = new_id;
        strcpy(new_item->name, new_name);//using strcpy as we are dealing with array of chars
        new_item->cost = new_cost;
        new_item->category = new_catg;
        new_item->next = NULL;//setting the next pointer to null as we are adding to the end
        if(head == NULL)//checking if head is null means no items in list yet therefore set the new item as the head
        {
            head = new_item;
            return head;
        }
        else//if the head is not null loop until end of list then add item
        {
            current_item = head;
            while(current_item->next != NULL)
            {
                current_item = current_item->next;
            }
            current_item->next = new_item;
        }
        return head;


    }//if the id or name exist notify user depending on return values of the search functions
    if (search_item_id(head, new_id) == 1 && search_item_name(head, new_name, send_type) == 0)
    {
        printf("\nItem with the same ID is already in Stock!\n");
    }
    if (search_item_name(head, new_name, send_type) == 1 && search_item_id(head, new_id) == 0)
    {
        printf("\nItem with the same Name is already in Stock!\n");
    }
    if (search_item_id(head, new_id) == 1 && search_item_name(head, new_name, send_type) == 1)
    {
        printf("\nItem with the same ID and Name is already in Stock!\n");
    }
    return head;
}

void display_list_unsort(LIST *head)
{
    if(head == NULL)//if the head is null means the list is empty so notify user
    {
        printf("\nEmpty list!\n");
        return;
    }
    printf("\n\n ID | Product | Price | Category | -Not Sorted\n");
    LIST *current_item = NULL;
    current_item = head;
    while(current_item != NULL)//iterate through the list and print each item until the next pointer of the current item is null
    {
        printf("%d ""|"" %s ""|"" %.3f ""|"" %c ""|"" \n",current_item->id,current_item->name,current_item->cost,current_item->category);
        current_item = current_item->next;
    }
}

int search_item_id(LIST *head, int id_search)
{

    if (head == NULL)
    {
        return 0;
    }
    LIST *current_item;
    current_item = head;
     while(current_item != NULL)//iterate through the list and compare each items id with the id that is being searched for until next pointer of the current item is null
     {
         if(current_item->id == id_search)
         {
            return 1; //if the item is found return 1
         }
         current_item = current_item->next;
     }
}

int search_item_name(LIST *head, char name_search[], int recv_type)
{
    if (head == NULL && recv_type != 0)
    {
        printf("\nThe list is empty!\n");
        return 0;
    }
    LIST *current_item;
    current_item = head;
    while(current_item != NULL)//iterate through the list and compare each items name with the name that is being searched for until next pointer of the current item is null
    {
        //using strcmp to compare the strings of the name being searched and the current item name strcmp returns 0 when the strings are identical
        if(strcmp(current_item->name, name_search) == 0 && recv_type == 0)
        {
            return 1;//if the name is found but the receive type is 0 return 1
        }
        else if(strcmp(current_item->name, name_search) == 0 && recv_type == 1)
        {
            printf("\n\n ID | Product | Price | Category |\n");
            printf("%d ""|"" %s ""|"" %.3f ""|"" %c ""|"" \n",current_item->id,current_item->name,current_item->cost,current_item->category);
            return 2;//if the name is found but the receive type is 1 return 2
        }

        current_item = current_item->next;
    }
    if (recv_type == 1)
    {
        printf("\nAn item with that name was not found\n");
        return 3;//if the name is not found but the receive type is 1 return 3

    }

}

delete_item(LIST *head, int item_id)
{
    LIST *previous_item, *current_item;//need 2 pointer to point to the item and the item before it so once the item which user wants to delete is found we link the item before it with the one after it
    if (head == NULL)//if head is null means list is empty (head pointer not pointing to anything no entries in the list)
    {
        printf("\nThe item id is not available as the list is empty\n");
        return;
    }
    current_item = head;
    previous_item = head;
    if (current_item->id == item_id)//if the head holds the item that is to be deleted move the head pointer to the next item
    {//delete the item by freeing the memory and removing the pointer from it to the next item
        head = head->next;
        free(current_item);
        current_item = NULL;
        printf("\nItem deleted\n");
        return head;

    }
    while (current_item != NULL && current_item->id != item_id)//iterate through the list and compare each items id with the id that is being searched for until next pointer of the current item is null or item id is not equal to id being searched
    {
        previous_item = current_item;
        current_item = current_item->next;
    }
    if (current_item == NULL)
    {
        printf("\nItem not found in list\n");//if reached the end of list and not found the id of the item to be deleted notify the user
        return;
    }
    else
    {//delete the item by freeing the memory and removing the pointer from it to the next item
        previous_item->next = current_item->next;
        free(current_item);
        current_item = NULL;
        printf("\nItem deleted\n");
        return head;//return the head
    }
    return;
}

change_cost(LIST *head, int item_id)
{
    double new_cost;//variable to hold user input of new cost
    LIST *current_item;
    if (head == NULL)//if head is null means list is empty (head pointer not pointing to anything no entries in the list)
    {
        printf("\nThe item id is not available as the list is empty\n");
        return;
    }
    current_item = head;
    while(current_item != NULL)//iterate through the list and compare each items id with the id that is being searched for until next pointer of the current item is null
    {
        if(current_item->id == item_id)//if the current item id and the id of user input are equal change the cost to the cost of the user input
        {
            printf("\nPlease enter the new cost for item\n");
            scanf("%lf", &new_cost);
            current_item->cost = new_cost;
            return;
        }
        current_item = current_item->next;
    }
    printf("\nAn item with that ID was not found in the list\n");//if reach current item = null and did not find the item with the id user gave print item not found
    return;
}

read_file(LIST *head, char *filename)
{
    LIST *current_item, *new_item;//pointer to the current item(starts and head and moves along the list using ->next) in the linked list and a pointer to the new item(append the data from file to the node pointed to by the new item then link the current to the new item)
    FILE *fp;
    head = current_item = NULL;//initialize the list set head to null and current to head
    fp = fopen(filename, "r");
    char line[80];

    while(!feof(fp))//loop as long as the end of file indicator is not return true for the file
    {
        //declaring variables to be added to the list
        //for each line in the file will populate the variable with the appropriate data using fscanf
        int new_id = 0;
        char new_name[20] = "";
        double new_cost = 0;
        char new_catg = "";

        fscanf(fp, "%d %s %lf %s", &new_id, &new_name, &new_cost, &new_catg);

        if (new_id == 0)//this is used to remove a blank entry into the list with all the values as zero so if the new_id is a 0 stop adding new items and return the head pointer of the list
        {
            return head;
        }

        new_item = (LIST *)malloc(sizeof(LIST));//allocate memory for each new item
        new_item->id = new_id;
        strcpy(new_item->name, new_name);//using strcpy as we are dealing with array of chars
        new_item->cost = new_cost;
        new_item->category = new_catg;
        new_item->next = NULL;

        if(head == NULL)//if the head is null (list is still empty) set the new item as the head and current item as head to move it from there relative to the head
        {
            current_item = head = new_item;
        }
        else
        {
            current_item = current_item->next = new_item;
        }

    }
    fclose(fp);

    return head;
}

save_file(LIST *head, char *filename)
{
    FILE *fp;
	fp = fopen(filename, "w+");

	if(fp == NULL)
    {
        printf("\nError\n");
    }
    else
    {
		LIST *current_item = NULL;
		current_item = head;
		while(current_item != NULL)//iterate through the list and using fprintf write into the specified file the data in each item
		{
			fprintf(fp, "%d %s %lf %c\n", current_item->id, current_item->name, current_item->cost, current_item->category);
			current_item = current_item->next;

		}
		fclose(fp);
		fp = NULL;
	}
}

void display_list_sorted(LIST *head)
{
    //to be able to display the sorted list whilst not changing the original list we must make a copy parallel to the list and then sort using bubble sort then display it
    LIST *old_LIST;//pointer to the original linked list will start at head and move until the end (null)
    LIST *new_LIST_head = (LIST *)malloc(sizeof(LIST));//allocate memory to the head of new list
    LIST *new_current_item;//pointer to iterate through the new list
    int id_temp = 0;//these variables are used as temporary to swap data between nodes/items
	char name_temp[20] = "";
	double cost_temp = 0;
	char catg_temp;


    new_current_item = new_LIST_head;
    old_LIST = head;

    while(old_LIST != NULL)//until we iterate through the old list(last node points to null) we use memcpy to copy data from the node in the old list to the corresponding node in the new list
    {
        memcpy(new_current_item, old_LIST, sizeof(LIST));
        old_LIST = old_LIST->next;
        if (old_LIST != NULL)
        {
            new_current_item->next = (LIST *)malloc(sizeof(LIST));
            new_current_item = new_current_item->next;
        }
    }
    //to be able to use bubble sort we must be able to access each item and the item before it to be able to compare them
    LIST *previous_item;
    LIST *current_item;
    current_item = new_LIST_head;
    previous_item = new_LIST_head;
    for (previous_item = new_LIST_head ; previous_item->next != NULL ; previous_item = previous_item->next)//loop from the beginning of the new list moving the previous pointer along by one item each time until reach end of list
    {

        for (current_item = previous_item->next ; current_item != NULL ; current_item = current_item->next)//loop from the beginning of the new list moving the current pointer along by one item each time until reach end of list
        {
            if(previous_item->id > current_item->id)//if the id of the previous item is larger than the id of the current item swap data
            {
                id_temp = previous_item->id;
                previous_item->id = current_item->id;
                current_item->id = id_temp;

                strcpy(name_temp,previous_item->name);
                strcpy(previous_item->name,current_item->name);
                strcpy(current_item->name,name_temp);

                cost_temp = previous_item->cost;
                previous_item->cost = current_item->cost;
                current_item->cost = cost_temp;

                catg_temp = previous_item->category;
                previous_item->category = current_item->category;
                current_item->category = catg_temp;

            }
        }
    }//display the new list (sorted)
    printf("\n\n ID | Product | Price | Category | -Sorted by ID in ascending order \n");
    new_current_item = NULL;
    new_current_item = new_LIST_head;
    while(new_current_item != NULL)
    {
        printf("%d ""|"" %s ""|"" %.3f ""|"" %c ""|"" \n",new_current_item->id,new_current_item->name,new_current_item->cost,new_current_item->category);
        new_current_item = new_current_item->next;
    }

}

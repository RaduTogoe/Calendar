#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

/*void	update(void)
{
	file *f1 = fopen("dates.csv", "w");
	struct note *temp = root->note;

	while (temp)
	{
			fprintf(f1, "%s,", temp->data);
			temp = temp->link;
	}
}

void	get_date(void)
{
		file *f1 = fopen("dates.csv", "r");
		char date[15];

		while (fscanf(f1, "%s,", date))
		note_insert(date);
}*/

void	menu()
{
		get_date();
		int option;
		//printf("\e[1;1H\e[2J");
		printf("		        _________   _________			Welcome\n");
		printf("		   ____/      452\\ /     453 \\____\n");
		printf("		 /| ------------- |  ------------ |\\\n");
		printf("		||| ------------- | ------------- |||		To\n");
		printf("		||| ------------- | ------------- |||\n");
		printf("		||| ------------- | ------------- |||\n");
		printf("		||| ------------- | ------------- |||		Your\n");
		printf("		||| ------------- | ------------- |||\n");
		printf("		||| ------------- | ------------- |||\n");
		printf("		||| ------------- | ------------- |||		Personal\n");
		printf("		||| ------------- | ------------- |||\n");
		printf("		||| ------------- | ------------- |||\n");
		printf("		||| ------------- | ------------- |||		Calendar\n");
		printf("		|||_____________  |  _____________|||\n");
		printf("		L/_____/--------\\\\_//W-------\\_____\\J		Have Fun!\n");
		printf("		Please select an option:\n");
		printf("		1.Display the calendar\n");
		printf("		2.Create a note for a certain date\n");
		printf("		3.Delete a note\n");
		printf("		4.Exit\n		");
		scanf("%d", &option);
		switch (option)
		{
				case 1: 
						display();
						break;
				case 2:
						create_note();
						break;
				case 3:
						delete_note();
						break;
				case 4:
						exit(WEXITED);
						break;
		}
}

int		main(void)
{
		menu();
}

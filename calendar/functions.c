#include "functions.h"
#include "var.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#ifndef FUNC
#define FUNC
#define RED     "\033[31m"      /* Red */
#define RESET   "\033[0m"
#define GREEN   "\033[32m"      /* Green */
#define BLUE    "\033[34m"  /* Blue */
struct note *root_note = NULL;
char datito[15];

int		is_bisect(int year)
{
		if (year % 4)
				return (0);
		if (year % 100)
				return (1);
		if (year % 400)
				return (0);
		return (1);
}

int		get_month(char *p)
{
		if (strcmp(p, "Jan") == 0)
				return (1);
		if (strcmp(p, "Feb") == 0)
				return (2);
		if (strcmp(p, "Mar") == 0)
				return (3);
		if (strcmp(p, "Apr") == 0)
				return (4);
		if (strcmp(p, "May") == 0)
				return (5);
		if (strcmp(p, "Jun") == 0)
				return (6);
		if (strcmp(p, "Jul") == 0)
				return (7);
		if (strcmp(p, "Aug") == 0)
				return (8);
		if (strcmp(p, "Sep") == 0)
				return (9);
		if (strcmp(p, "Oct") == 0)
				return (10);
		if (strcmp(p, "Nov") == 0)
				return (11);
		if (strcmp(p, "Dec") == 0)
				return (12);
		return (1);
}

int		get_day(int d, int m, int y)
{
		static int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 }; 
		y -= m < 3; 
		printf("%d", ( y + y/4 - y/100 + y/400 + t[m-1] + d) % 7);
		return ( y + y/4 - y/100 + y/400 + t[m-1] + d) % 7; 
}

void	print_title(int month, int year)
{
		printf("		");
		if (month == 1)
				printf("January");
		if (month == 2)
				printf("February");
		if (month == 3)
				printf("March");
		if (month == 4)
				printf("April");
		if (month == 5)
				printf("May");
		if (month == 6)
				printf("June");
		if (month == 7)
				printf("July");
		if (month == 8)
				printf("August");
		if (month == 9)
				printf("September");
		if (month == 10)
				printf("October");
		if (month == 11)
				printf("November");
		if (month == 12)
				printf("December");
		printf(" %d\n", year);
}

int		color_verif(int date, int month, int year)
{
		struct note *temp = root_note;
		int k = 0;
		while (temp)
		{
				k = (k +  (int)(temp->data[0] - 48)) * 10 + (int)(temp->data[1] - 48);
				printf("***%d&%d ", k, date);
				if (k == date)
				{
						k = 0;
						k = 10 * (int)(temp->data[3] - 48) + (int)(temp->data[4] - 48);
				printf("***%d ", k);

						if (k == month)
						{
								k = 1000 * (int)(temp->data[6] - 48) + 100 * (int)(temp->data[7] - 48) + 10 * (int)(temp->data[8] - 48) + (int)(temp->data[9] - 48);
										printf("***%d ", k);

						}
						if (k == year)
								return (1);
				}
				k = 0;
				temp = temp->link;
		}
		return (0);
}

void	final(int date, int month, int year)
{
		int i;
		int nr;
		int first_day = get_day(1, month, year);
		int op;
		int k = 0;
		int day = first_day;
		if (day == 0)
				day = 7;
		if (month == 13)
		{
				year++;
				month = 1;
		}
		if (month == 0)
		{
				year--;
				month = 12;
		}

		printf("\e[1;1H\e[2J");
		//printf("***%d***\n\n", date);
		print_title(month, year);
		printf("		M	T	W	T	F	S	S\n");
		if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
				nr = 31;
		else
		{
				if (month == 2)
				{
						if (is_bisect(year))
								nr = 29;
						else
								nr = 28;
				}
				else
						nr = 30;
		}
		printf("		");
		//printf("*** %d ***", day);
		for (i = 1; i < day; i++)
		{
				printf("	");
		}
		for (i = 1; i <= nr; i++)
		{
				k = color_verif(date, month, year);
				if (day == 7)
				{
						if (k == 0)
						{
								if (i == date)
										printf("%s%d%s	", GREEN, i, RESET);
								else
										printf("%s%d%s	", RED, i, RESET);
								printf("\n		");
								day = 1;
						}
						else
								printf("%s%d%s	", BLUE, i, RESET);
				}
				else
				{
						if (k == 0)
						{
								if (i == date)
										printf("%s%d%s	", GREEN, i, RESET);
								else
										printf("%d	", i);
								day++;
						}
						else
								printf("%s%d%s	", BLUE, i, RESET);
				}
		}
		printf("\n		Introduce the number of the option (1-5)\n");
		printf("		1. Prev Month\n");
		printf("		2. Next Month\n");
		printf("		3. Prev Year\n");
		printf("		4. Next Year\n");
		printf("		5.Exit\n");
		scanf("%d", &op);
		switch (op)
		{
				case 1: final(date, month - 1, year);
						break;
				case 2: final(date, month + 1, year);
						break;
				case 3: final(date, month, year - 1);
						break;
				case 4: final(date, month, year + 1);
						break;
				case 5: menu();
						break;
		}
}

void	display(void)
{
		char data[50];
		char *p;
		int date = 0;
		int year = 0;
		int month;
		int k = 0;

		strcpy(data, __DATE__);
		p = strtok(data, " ");
		while (p)
		{
				if (k == 1)
				{
						//printf("\n\n*%s*\n\n", p); 
						if (p[1] == '\0')
								date = (p[0] - 48);
						else
								date = (p[0] - 48) * 10 + (p[1] - 48);
				}
				if (k == 0)
						month = get_month(p);
				if (k == 2)
						year = (p[0] - 48) * 1000 + (p[1] - 48) * 100 + (p[2] - 48) * 10 + (p[3] - 48);
				p = strtok(NULL, " ");
				k++;
		}
		//printf("\n\n***%d***\n\n", date);
		final(date, month, year);
}
void	update(void)
{
		FILE *f1 = fopen("dates.csv", "w");
		struct note *temp = root_note;
printf("\n\n***%s***\n\n", temp->data);

		while (temp)
		{
				fprintf(f1, "%s,", temp->data);
				temp = temp->link;
		}
}

void	get_date(void)
{
		FILE *f1 = fopen("dates.csv", "r");

		while (fscanf(f1, "%s,", datito) == 1)
		{
				note_insert();
				printf("///");
		}
}

int		verif(char c, int k)
{
		int ok = 0;
		if ((c == 'F' && (k == 0)) || (c == 'I' && (k == 1)) || (c == 'N' && (k == 2)))
		{
				k++;
				if (c == 'N')
					printf("$");
				ok = 1;
	}
		if ((c == 'I' && (k == 3)) || (c == 'S' && (k == 4)) || (c == 'H' && (k == 5)))
		{
				k++;
				ok = 1;
		}
		if (ok)
		printf("*");
		return (ok);
}

void	note_insert(void)
{
		struct note *temp = root_note;
		struct note *temp1 = malloc(sizeof(struct note));
		strcpy(temp1->data, datito);
		temp1->data[11] = '\0';
		//printf("****%s*****", temp1->data);
		//printf("%s", temp1->data);
		temp1->link = NULL;
		if (root_note == NULL)
		{
				root_note = NULL;
				temp1->link = root_note;
				root_note = temp1;
		}
		else
		{
				while (temp->link != NULL)
				{
						temp = temp->link;
				}
						temp->link = temp1;
		}
}


void	create_note(void)
{
		FILE *f;
		int k = 0;
		char c;

		printf("\e[1;1H\e[2J");
		printf("		Please introduce the date you want to create the note\n");
		printf("		Format: 	DD.MM.YYYY (if the day or the month are lower than 9, write 0 before\n		 it, make sure to enter the dots too)\n");
		printf("		If you have another note on that date, it will be replaced automatically\n");
		printf("		If you want to check if you have another note here, go to the calendar, the day will be marked\n 		with blue\n");
		printf("		To go back to the menu, write MENU instead of the date\n		");
		scanf("%s", datito);
		if (strcmp(datito, "MENU") == 0)
		{
				menu();
				return;
		}
		f = fopen(datito, "w");
		note_insert();
		//printf("\e[1;1H\e[2J");
		printf("\n\n\n");
		printf("		Now you can write your note, when you are done, go to a new line, then write FINISH\n");
		while (1)
		{
				scanf("%c", &c);
				fprintf(f, "%c",  c); 
				if (verif(c, k) == 1)
					k++;
				if (k == 6)
				{
						menu();
						break;
				}
		}
		update();
}

void	delete_note(void)
{
}
#endif

//This system is Built By Kanha Bindal 

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

//Different functions prototype
int sign_up(void);
int login(void);
int from_to(void);
int route(int, int);
int tickets_(int, int, int);
int view_seats(int, int);
int bus_1(int, int, int);
int bus_2(int, int, int);
int bus_3(int, int, int);
void cancel(void);

char extra[12][15];

int main(void)
{
	int fair, data, tell;
	int start;
	printf("\n\n\t\t\t\tWELCOME TO NEON TRAVELS\n\n\n");
	//Bus centers
	printf("\tIndore\t\tBhopal\t\tGuna\t\tGwalior\t\tMuzaffarpur\n\n\n\n\n");
	printf("\tPress '1' to Create a new account\n\n\tPress '2' to login through an existing account\n\nEnter number: ");
	scanf("%d", &start);

	//enter correct details to proceed
	while (start != 1 && start != 2)
	{
		printf("\nEnter correct details\n\n");
		scanf("%d", &start);
	}

	//sign up if u are a new user
	if (start == 1)
	{
		tell = sign_up();
		if (tell == 0)
		{
			tell = sign_up();
		}

	}

	//otherwise login
	else
	{
		tell = login();
		if (tell == 0)
		{
			tell = sign_up();
		}
	}
	//book tickets
	printf("\n\tPress '1' to Book tickets and '2' to cancel tickets\n\n");
	printf("Enter number: ");
	scanf("%d", &start);
	while (start != 1 && start != 2)
	{
		printf("\nEnter correct details\n");
		printf("\n\t\tPress '1' to Book tickets and '2' to cancel tickets\n\n");
		printf("Enter number: ");
		scanf("%d", &start);
	}
	//prompt user about source and destination
	if (start == 1)
	{
		data = from_to();
		// selecting route according to details given by user
		fair = route(data, 1);

		//displaying fare
		printf("\n\t\tYou Have to pay %dRs. for the ticket(s)\n", fair);
	}
	// if user has to cancel ticket
	else
	{
		cancel();
	}
	start = 0;
	//ask user if continue or exit
	while (start != 1 && start != 2)
	{
		printf("\nPress '1' to go to main menu and Press '2' to exit\n");
		scanf("%d", &start);
	}
	if (start == 1)
	{
		main();
		exit(0);
	}

	printf("\n\t\tThank You For Using Neon Travels\n\n");
}

//funtion to get details while signing up
int sign_up(void)
{
	char name[30];
	char password[30];
	//char *pass;
	//pass = (char *)(malloc(15 * sizeof(char)));
	char check[30];

	FILE *id;
	//open file in append mode
	id = fopen("id.txt", "a+");

	printf("\nEnter Username: ");
	scanf("%s", name);
	while (fscanf(id, "%s", check) != EOF)
	{
		if (strcmp(name, check) == 0)
		{
			printf("\nUsername is already taken\n");
			fclose(id);
			return 0;
		}
	}

	//in buit funtion to get passwork in masked form
	//pass = getpass("Enter Password (it will be hidden): ");
	printf("Enter Password: ");
	scanf("%s", password);
	//enter name and password in the file created
	fprintf(id, "%s\n%s\n\n", name, password);
	//free(pass);

	fclose(id);
	return 1;
}

//Funtion to log in into an existing account
int login(void)
{
	char name[30];
	char password[30];
	//char *pass;
	char check[30];
	char check_2[30];
	int count = 0;

	//pass = (char *)(malloc(15 * sizeof(char)));
	FILE *id;
	if ((id = fopen("id.txt", "r")) == NULL)
	{
		printf("\nNo account found! \nYou must sign up first\n");
		printf("\nYou have been redirected to the create new account window\n");
		return 0;
	}

	printf("\nEnter Username: ");
	scanf("%s", name);
	//pass = getpass("Enter Password (it will be hidden): ");
	printf("Enter Password: ");
	scanf("%s", password);

	while (fscanf(id, "%s%s", check, check_2) != EOF)
	{
		if (strcmp(name, check) == 0 && strcmp(check_2, password) == 0)
		{
			count++;
		}
	}
	if (count == 0)
	{
		printf("\nEnter correct username or password\n");
		fclose(id);
		login();
		return 1;
	}
	//free(pass);
	fclose(id);
	return 1;
}

//ask user about there initial point and desitination
int from_to(void)
{
	int from;
	int to;
	printf("\n1.)Gwalior\n2.)Guna\n3.)Indore\n4.)Bhopal\n5.)Muzaffarpur\n\n");
	printf("Enter bus number\n\n");
	printf("\tFrom: ");
	scanf("%d", &from);

	//if incorrect details are given
	while (from > 5 || from < 1)
	{
		printf("\nEnter correct details\n\nFrom: ");
		scanf("%d", &from);
	}
	printf("\n\tTo: ");
	scanf("%d", &to);
	while (to > 5 || to < 1 || to == from)
	{
		printf("\nEnter correct details\n\nTo: ");
		scanf("%d", &to);
	}
	printf("\n");

	//return data
	return from * 10 + to;
}

//function to select a route (not for user)
int route(int data, int x)
{
	int distance, bus_type;
	printf("\nSelect Bus: \n\n\t1.) Sleeper Non Ac\n\n\t2.) Sleeper Ac\n\nEnter no: ");
	scanf("%d", &bus_type);
	if (x == 0)
	{
		return bus_type;
	}

	// gwalior-guna-indore
	if (data == 12 || data == 21)
	{
		distance = 220;
		return tickets_(distance, data, bus_type);
	}
	else if (data == 23 || data == 32)
	{
		distance = 290;
		return tickets_(distance, data, bus_type);

	}
	else if (data == 31 || data == 13)
	{
		distance = 510;
		return tickets_(distance, data, bus_type);
	}

	// bhopal-guna-gwalior-muz.
	else if (data == 42 || data == 24)
	{
		distance = 210;
		return tickets_(distance, data, bus_type);
	}
	else if (data == 41 || data == 14)
	{
		distance = 430;
		return tickets_(distance, data, bus_type);
	}
	else if (data == 15 || data == 51)
	{
		distance = 870;
		return tickets_(distance, data, bus_type);
	}
	else if (data == 25 || data == 52)
	{
		distance = 1040;
		return tickets_(distance, data, bus_type);
	}

	// indore-bhopal-muzaffarpur
	else if (data == 35 || data == 53)
	{
		distance = 1320;
		return tickets_(distance, data, bus_type);
	}
	else if (data == 34 || data == 43)
	{
		distance = 190;
		return tickets_(distance, data, bus_type);
	}
	else
	{
		distance = 1030;
		return tickets_(distance, data, bus_type);
	}
}

//function to prompt user for tickets and to calculate fare
int tickets_(int distance, int data, int bus_type)
{
	int seat_no, tickets, counter;
	//check how many tickets are already booked
	counter = view_seats(data, bus_type);
	printf("\nHow many tickets do you want to book: ");
	scanf("%d", &tickets);

	//if user enters more tickets than total available
	while (counter + tickets > 12)
	{
		printf("\nEnter correct details!\n");
		printf("\nHow many tickets do you want to book: ");
		scanf("%d", &tickets);
	}
	int tic = tickets;
	while (tickets--)
	{

		printf("\nEnter Seat Number: ");
		scanf("%d", &seat_no);
		printf("Enter your name: ");
		scanf("%s", extra[seat_no - 1]);

		//saving tickets
		if (data == 32 || data == 21 || data == 31 || data == 23 || data == 12 || data == 13)
		{
			bus_1(data, bus_type, seat_no);
		}
		else if (data == 42 || data == 24 || data == 41 || data == 14 || data == 15 || data == 51 || data == 25 || data == 52)
		{
			bus_2(data, bus_type, seat_no);
		}
		else
		{
			bus_3(data, bus_type, seat_no);
		}
	}

	counter = view_seats(data, bus_type);

	//returning fare
	return distance * bus_type * tic;

}

//selecting data for route 1
int bus_1(int data, int bus_type, int seat_no)
{
	if (data == 32 || data == 21 || data == 31)
	{
		if (bus_type == 1 || bus_type == 3)
		{
			if (bus_type == 1)
			{
				//adding data to a file
				FILE *book;
				book = fopen("voyage.txt", "a+");
				fprintf(book, "%d\n%s\n\n", seat_no, extra[seat_no - 1]);
				fclose(book);
				return 0;
			}
			else
			{
				//reading data from a file
				int counter = 0;
				FILE *id;
				id = fopen("voyage.txt", "r");
				if (id == NULL)
					return 0;

				int *num;
				num = (int *)(malloc(sizeof(int)));
				char check[20];
				while (fscanf(id, "%d %s", num, check) != EOF)
				{
					strcpy(extra[*num - 1], check);
					counter++;
				}
				fclose(id);
				free(num);
				return counter;
			}

		}
		else
		{
			if (bus_type == 2)
			{
				FILE *book;
				book = fopen("voyage_A.txt", "a+");
				fprintf(book, "%d\n%s\n\n", seat_no, extra[seat_no - 1]);
				fclose(book);
				return 0;

			}
			else
			{
				int counter = 0;
				FILE *id;
				id = fopen("voyage_A.txt", "r");
				if (id == NULL)
					return 0;

				int *num;
				num = (int *)(malloc(sizeof(int)));
				char check[20];
				while (fscanf(id, "%d %s", num, check) != EOF)
				{
					strcpy(extra[*num - 1], check);
					counter++;
				}
				fclose(id);
				free(num);
				return counter;
			}

		}
	}
	else
	{
		if (bus_type == 1 || bus_type == 3)
		{
			if (bus_type == 1)
			{
				FILE *book;
				book = fopen("voyage_N.txt", "a+");
				fprintf(book, "%d\n%s\n\n", seat_no, extra[seat_no - 1]);
				fclose(book);
				return 0;
			}
			else
			{
				int counter = 0;
				FILE *id;
				id = fopen("voyage_N.txt", "r");
				if (id == NULL)
					return 0;

				int *num;
				num = (int *)(malloc(sizeof(int)));
				char check[20];
				while (fscanf(id, "%d %s", num, check) != EOF)
				{
					strcpy(extra[*num - 1], check);
					counter++;
				}
				fclose(id);
				free(num);
				return counter;
			}
		}
		else
		{
			if (bus_type == 2)
			{
				FILE *book;
				book = fopen("voyage_NA.txt", "a+");
				fprintf(book, "%d\n%s\n\n", seat_no, extra[seat_no - 1]);
				fclose(book);
				return 0;
			}
			else
			{
				int counter = 0;
				FILE *id;
				id = fopen("voyage_NA.txt", "r");
				if (id == NULL)
					return 0;

				int *num;
				num = (int *)(malloc(sizeof(int)));
				char check[20];
				while (fscanf(id, "%d %s", num, check) != EOF)
				{
					strcpy(extra[*num - 1], check);
					counter++;
				}
				fclose(id);
				free(num);
				return counter;
			}
		}
	}
}

//selecting data for route 2
int bus_2(int data, int bus_type, int seat_no)
{
	if (data == 42 || data == 45 || data == 41 || data == 25)
	{
		if (bus_type == 1 || bus_type == 3)
		{
			if (bus_type == 1)
			{
				FILE *book;
				book = fopen("Titanic.txt", "a+");
				fprintf(book, "%d\n%s\n\n", seat_no, extra[seat_no - 1]);
				fclose(book);
				return 0;
			}
			else
			{
				int counter = 0;
				FILE *id;
				id = fopen("Titanic.txt", "r");
				if (id == NULL)
					return 0;

				int *num;
				num = (int *)(malloc(sizeof(int)));
				char check[20];
				while (fscanf(id, "%d %s", num, check) != EOF)
				{
					strcpy(extra[*num - 1], check);
					counter++;
				}
				fclose(id);
				free(num);
				return counter;
			}
		}
		else
		{
			if (bus_type == 2)
			{
				FILE *book;
				book = fopen("Titanic_A.txt", "a+");
				fprintf(book, "%d\n%s\n\n", seat_no, extra[seat_no - 1]);
				fclose(book);
				return 0;
			}
			else
			{
				int counter = 0;
				FILE *id;
				id = fopen("Titanic_A.txt", "r");
				if (id == NULL)
					return 0;

				int *num;
				num = (int *)(malloc(sizeof(int)));
				char check[20];
				while (fscanf(id, "%d %s", num, check) != EOF)
				{
					strcpy(extra[*num - 1], check);
					counter++;
				}
				fclose(id);
				free(num);
				return counter;
			}
		}
	}
	else
	{
		if (bus_type == 1 || bus_type == 3)
		{
			if (bus_type == 1)
			{
				FILE *book;
				book = fopen("Titanic_N.txt", "a+");
				fprintf(book, "%d\n%s\n\n", seat_no, extra[seat_no - 1]);
				fclose(book);
				return 0;
			}
			else
			{
				int counter = 0;
				FILE *id;
				id = fopen("Titanic_N.txt", "r");
				if (id == NULL)
					return 0;

				int *num;
				num = (int *)(malloc(sizeof(int)));
				char check[20];
				while (fscanf(id, "%d %s", num, check) != EOF)
				{
					strcpy(extra[*num - 1], check);
					counter++;
				}
				fclose(id);
				free(num);
				return counter;
			}
		}
		else
		{
			if (bus_type == 2)
			{
				FILE *book;
				book = fopen("Titanic_NA.txt", "a+");
				fprintf(book, "%d\n%s\n\n", seat_no, extra[seat_no - 1]);
				fclose(book);
				return 0;
			}
			else
			{
				int counter = 0;
				FILE *id;
				id = fopen("Titanic_NA.txt", "r");
				if (id == NULL)
					return 0;

				int *num;
				num = (int *)(malloc(sizeof(int)));
				char check[20];
				while (fscanf(id, "%d %s", num, check) != EOF)
				{
					strcpy(extra[*num - 1], check);
					counter++;
				}
				fclose(id);
				free(num);
				return counter;
			}
		}
	}
}

//selecting data for root 3
int bus_3(int data, int bus_type, int seat_no)
{
	if (data == 34 || data == 35 || data == 45)
	{
		if (bus_type == 1 || bus_type == 3)
		{
			if (bus_type == 1)
			{
				FILE *book;
				book = fopen("Force.txt", "a+");
				fprintf(book, "%d\n%s\n\n", seat_no, extra[seat_no - 1]);
				fclose(book);
				return 0;
			}
			else
			{
				int counter = 0;
				FILE *id;
				id = fopen("Force.txt", "r");
				if (id == NULL)
					return 0;

				int *num;
				num = (int *)(malloc(sizeof(int)));
				char check[20];
				while (fscanf(id, "%d %s", num, check) != EOF)
				{
					strcpy(extra[*num - 1], check);
					counter++;
				}
				fclose(id);
				free(num);
				return counter;
			}
		}
		else
		{
			if (bus_type == 2)
			{
				FILE *book;
				book = fopen("Force_A.txt", "a+");
				fprintf(book, "%d\n%s\n\n", seat_no, extra[seat_no - 1]);
				fclose(book);
				return 0;
			}
			else
			{
				int counter = 0;
				FILE *id;
				id = fopen("Force_A.txt", "r+");
				if (id == NULL)
					return 0;

				int *num;
				num = (int *)(malloc(sizeof(int)));
				char check[20];
				while (fscanf(id, "%d %s", num, check) != EOF)
				{
					strcpy(extra[*num - 1], check);
					counter++;
				}
				fclose(id);
				free(num);
				return counter;
			}
		}
	}
	else
	{
		if (bus_type == 1 || bus_type == 3)
		{
			if (bus_type == 1)
			{
				FILE *book;
				book = fopen("Force_N.txt", "a+");
				fprintf(book, "%d\n%s\n\n", seat_no, extra[seat_no - 1]);
				fclose(book);
				return 0;
			}
			else
			{
				int counter = 0;
				FILE *id;
				id = fopen("Force_N.txt", "r");
				if (id == NULL)
					return 0;

				int *num;
				num = (int *)(malloc(sizeof(int)));
				char check[20];
				while (fscanf(id, "%d %s", num, check) != EOF)
				{
					strcpy(extra[*num - 1], check);
					counter++;
				}
				fclose(id);
				free(num);
				return counter;
			}
		}
		else
		{
			if (bus_type == 2)
			{
				FILE *book;
				book = fopen("Force_NA.txt", "a+");
				fprintf(book, "%d\n%s\n\n", seat_no, extra[seat_no - 1]);
				fclose(book);
				return 0;
			}
			else
			{
				int counter = 0;
				FILE *id;
				id = fopen("Force_NA.txt", "r");
				if (id == NULL)
					return 0;

				int *num;
				num = (int *)(malloc(sizeof(int)));
				char check[20];
				while (fscanf(id, "%d %s", num, check) != EOF)
				{
					strcpy(extra[*num - 1], check);
					counter++;
				}
				fclose(id);
				free(num);
				return counter;
			}
		}
	}
}

//function to view how many seats are available
int view_seats(int data, int bus_type)
{
	int counter, seat_no = 0;

	for (int i = 0; i < 12; i++)
	{
		strcpy(extra[i], "Empty");
	}

	bus_type += 2;

	if (data == 32 || data == 21 || data == 31 || data == 23 || data == 12 || data == 13)
	{
		counter = bus_1(data, bus_type, seat_no);
	}
	else if (data == 42 || data == 24 || data == 41 || data == 14 || data == 15 || data == 51 || data == 25 || data == 52)
	{
		counter = bus_2(data, bus_type, seat_no);
	}
	else
	{
		counter = bus_3(data, bus_type, seat_no);
	}

	for (int i = 0; i < 10; i += 2)
	{
		printf("\t\t%d %s    %d %s\n", i + 1, extra[i], i + 2, extra[i + 1]);
	}

	printf("\t\t11 %s   12 %s", extra[10], extra[11]);
	printf("\n\n");
	return counter;
}

//function to cancel tickets
void cancel(void)
{
	int data = from_to();
	int bus_type = route(data, 0);
	int counter, seat_no = 0;

	for (int i = 0; i < 12; i++)
	{
		strcpy(extra[i], "Empty");
	}
	bus_type += 2;
	//checking initial seats if booked or empty

	if (data == 32 || data == 21 || data == 31 || data == 23 || data == 12 || data == 13)
	{
		counter = bus_1(data, bus_type, seat_no);
	}
	else if (data == 42 || data == 24 || data == 41 || data == 14 || data == 15 || data == 51 || data == 25 || data == 52)
	{
		counter = bus_2(data, bus_type, seat_no);
	}
	else
	{
		counter = bus_3(data, bus_type, seat_no);
	}

	for (int i = 0; i < 10; i += 2)
	{
		printf("\t\t%d %s    %d %s\n", i + 1, extra[i], i + 2, extra[i + 1]);
	}

	printf("\t\t11 %s   12 %s", extra[10], extra[11]);
	printf("\n\n");

	//asking user how many tickets to cancel
	printf("\n\tHow many tickets you want to cancel: ");
	scanf("%d", &counter);
	while (counter--)
	{
		printf("\nSelect Seat Number: ");
		scanf("%d", &seat_no);
		strcpy(extra[seat_no - 1], "Empty");
	}
	bus_type -= 2;

	if (data == 32 || data == 21 || data == 31 || data == 23 || data == 12 || data == 13)
	{
		counter = bus_1(data, bus_type, seat_no);
	}
	else if (data == 42 || data == 24 || data == 41 || data == 14 || data == 15 || data == 51 || data == 25 || data == 52)
	{
		counter = bus_2(data, bus_type, seat_no);
	}
	else
	{
		counter = bus_3(data, bus_type, seat_no);
	}

	for (int i = 0; i < 10; i += 2)
	{
		printf("\t\t%d %s    %d %s\n", i + 1, extra[i], i + 2, extra[i + 1]);
	}

	//showing last seats
	printf("\t\t11 %s   12 %s", extra[10], extra[11]);
	printf("\n\n");

}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#include "Patients.h"
#include "program.h"

#define proj

P_Node *Patients_record = NULL;

int main()
{

	// load data first
	Patrec_load(&Patients_record);
	load_slots();

	//PatRec_print(Patients_record);
	//getch();

	char choice;

	while (1)
	{
		system("cls"); // clear screen in case return from other window
		entry(); // the first entry
		choice = getch(); // take input

		if ( choice == 3 )
			break; // if Ctrl C is pressed or returned during run time end program
		else if ( choice == 27 ) continue; // Esc has no effect here

		if ( choice == 'U' ) // user mode
		{
			choice = user_mode();
		}

		else if ( choice == 'A' ) //admin mode
		{
			system("cls"); // clear screen
			admin_entry();
			int state = get_password(); // get password function
			if ( state == 0 )
			{
				printf("**************************************************\n");
				printf("three failures, system log out");
				break;
			}

			else if ( state == 27 )
				continue;
			else if ( state == 3 )
				break;

			else // case password is entered right
			{
				choice = admin_mode();
			}

		}
		else // a key otherwise U,A, Esc or Ctrl+C
		{
			printf("no such choice\n");
		}

		if ( choice == 3 ) break;
	} //while 1

	// save data before closing
	PatRec_save(Patients_record);
	save_slots();

}

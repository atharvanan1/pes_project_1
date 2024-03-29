/************************************************
 * File - program_2.c				*
 * Name - Atharva Nandanwar			*
 * Email - atharva.nandanwar@colorado.edu	*
 * Date - 09-17-2019				*
 * Compiler - gcc std=c99                       *
 ************************************************/

/* Header files */
#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<ctype.h>

/****************************************************************
 * Main function - used for taking inputs, check them, and call *
 * print function.                                              *
 * Name - main                                                  *
 * Parameters - void                                            *
 * Return - int                                                 *
 ****************************************************************/
int main(void)
{
	/* Array of input numbers that shall be processed */
	const int8_t input[20]={66, 114, 117, 99, 101, 32, 83,\
		                97, 121, 115, 32, 72, 105, 33,\
				7, 9, 50, 48, 49, 57};

	/* A pointer to char, to hold string which will be      *
	 * printed with the output                              */
	char *type = NULL;

	/* Looping through all the elements of the array */
	for (int i = 0; i < 20; i++)
	{
		/* islower() function will return 1, if the     *
		 * character is lowercase character.            */
		if(islower((char) input[i]))
		{
			type = "Lower Case";	
		}

		/* isupper() function will return 1, if the     *
		 * character is uppercase character.            */
		else if(isupper((char) input[i]))
		{
			type = "Upper Case";
		}

		/* Checking condition for white space characters */
		else if((input[i] >= 0 && input[i] <= 32) || input[i] == 127)
		{
			type = "White Space";
		}

		/* Checking for special characters */
		else if((input[i] >= 33 && input[i] <= 47) \
		     || (input[i] >= 58 && input[i] <= 64) \
		     || (input[i] >= 91 && input[i] <= 96) \
		     || (input[i] >= 123 && input[i] <= 126))
		{
			type = "Special Character";
		}
		/* isdigit() function will return 1, if the     *
		 * character is digit character.            */
		else if(isdigit((char) input[i]))
		{
			type = "Digit";
		}

		/* Printing the output in required format */
		printf("Code: %-6d\tType: %-20s\tASCII Char: %-5c\n", input[i], \
				type, (char)input[i]);
	}
	return 0;
}

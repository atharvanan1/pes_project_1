/************************************************
 * File - program_1.c                           *
 * Name - Atharva Nandanwar                     *
 * Email - atharva.nandanwar@colorado.edu       *
 * Date - 09-14-2019                            *
 ************************************************/

/* Header files */
#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>

/* Function declarations */
// Scroll down for function descriptions to understand 
// more about them.
void binary_print(uint16_t num);
void test(uint16_t num);

/****************************************************************
 * Main function - calling functions which perform testing, and *
 * print binary representation                                  *
 * Name - main                                                  *
 * Parameters - void                                            *
 * Return - int                                                 *
 ****************************************************************/
int main(void)
{
	/* Assigning hexadecimal number to a variable */
	uint16_t number = 0xCAFE;
	// Temporary variable to store results of bit masks
	uint16_t temp;

	// Print hexadecimal
	printf("%#X\n", number);
	// Check for last four bits
	test(number);
	// Print binary representation
	binary_print(number);
	
	// Change the byte order, mask the lower byte, and shift
	// right by 8 bits. Storing in temp variable.
	temp = (number & 0xFF00) >> 8;
	// Shifting the original variable by 8 bits to left.
	number = number << 8;
	// Add temporary and original (shifted version).
	number = number + temp;
	printf("%#X\n", number);
	test(number);
	binary_print(number);

	// Rotate the number by shifting most significant nibble
	// to least significant position, and storing it in temp.
	// Effectively resulting as being rotated left.
	temp = (number & 0xF000) >> 12;
	// Shift original number by 4 bits to left. Adding
	// temporary and original would result in rotating left
	// by 4 bits.
	number = number << 4;
	number = number + temp;
	printf("%#X\n", number);
	test(number);
	binary_print(number);

	// Masking most significant byte, and shifting towards
	// left, effectively most significant byte being rotated 
	// towards right.
	temp = (number & 0x00FF) << 8;
	// Shift the original number to right by 8 bits, adding
	// temporary and orignal would result in rotating 8 bits
	// to the right.
	number = number >> 8;
	number = number + temp;
	printf("%#X\n", number);
	test(number);
	binary_print(number);
	return 0;
}

/****************************************************************
 * Binary Print function - Prints binary representation of      *
 * argument passed                                              *
 * Name - binary_print                                          *
 * Parameters -                                                 *
 * uint16_t (number_to_print) - decimal number to print binary  *
 * Return - void                                                *
 ****************************************************************/
void binary_print(uint16_t num)
{
	/* Integer to index through the character array that    *
	 * will house binary representation                     */     
	int i;
	char c[19] = "0b0000000000000000";
	// Loop backwards by selecting each character representing
	// bits at respective positions, replacing it with 
	// 1s or 0s depending on AND operation on LSB.
	for(i = 17; i >= 2; i--)
	{
		if(num & 0x0001)
		{
			c[i] = '1';
		}
		else
		{
			c[i] = '0';
		}
		num = num >> 1;
	}
	// Print the character array
	printf("%s\n", c);
}

/****************************************************************
 * Test function - This function takes an integer and checks    *
 * if last three bits are 1 or not. It prints the result as     *
 * TRUE or FALSE on standard output.                            *
 * Name - test                                                  *
 * Parameters -                                                 *
 * uint16_t num - number to run the tests on                    *
 * Return - void                                                *
 ****************************************************************/
void test(uint16_t num)
{
	/* Masking bits of num, except last 4 bits */
	num = num & 0x000F;
	/* Test case for checking if 3 out of 4 bits are 1 */
	if(num == 0x7 || num == 0xB || num == 0xD || num == 0xE || num == 0xF)
	{
		printf("TRUE!\n");
	}
	else
	{
		printf("FALSE!\n");
	}
}	

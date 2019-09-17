/************************************************
 * File - program_1.c				*
 * Name - Atharva Nandanwar			*
 * Email - atharva.nandanwar@colorado.edu	*
 * Date - 09-14-2019				*
 ************************************************/

/* Header files */
#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>


/* Global Variables */
// Structure Input will have value, radix, and operand size
// Making it global for easier access
struct input
{
    int32_t num;
    uint8_t radix;
    uint8_t op_size;
} line[11];
// MAX and MIN values - to be used in program in place of 
// macros
const uint16_t MAX = 0xFFFF;
const uint16_t MIN = 0x0000;

/* Function Declarations */
// Scroll down for function descriptions to understand 
// more about them
uint8_t error_check(struct input);
void binary_print(uint16_t, uint8_t);
void print_output(struct input);
uint16_t onescomplement(uint16_t, uint8_t);
uint16_t twoscomplement(uint16_t, uint8_t);
uint16_t signmagnitude(uint16_t, uint8_t);

/****************************************************************
 * Main function - used for making an array of input sets,      *
 * check them for errors, and call print function.              *
 * Name - main                                                  *
 * Parameters - void                                            *
 * Return - int                                                 *
 ****************************************************************/
int main (void)
{
    /* Making a const array to hold all the values that require *
     * checking.                                                */
    const int32_t array[11][3] = {{-6, 10, 4}, {-6, 9, 4},\
            {-6, 10, 5}, {-9, 10, 4}, {237, 10, 8}, {0354, 8, 8},\
            {0xEB, 16, 8}, {-125, 10, 8}, {65400, 10, 8},\
            {65400, 10, 16}, {-32701, 10, 16}};

    // Putting all values in a structure that enables modularity
    for (int i = 0; i < 11; i++)
    {
	    line[i].num = array[i][0];
	    line[i].radix = array[i][1];
	    line[i].op_size = array[i][2];
    }

    /* Print the input set, check if there are errors. If       *
     * errors, then skip to next iteration of loop. If not,     *
     * then print the output that's desired.			*/
    for (int i = 0; i < 11; i++)
    {
        printf("{%d, %hhu, %hhu}\n", line[i].num, line[i].radix, line[i].op_size);
        if (error_check(line[i]))
	{
	    continue;
	}
	else
	{
	    print_output(line[i]);
            // Indicator to tell that program run has ended
            printf("--------------END-OF-SEQUENCE---------------\n");
        }
    }

    return 0;
}

/****************************************************************
 * Error Check function - Checks for erros in values of input   *
 * set                                                          *
 * Name - error_check                                           *
 * Parameters -                                                 *
 * struct input line - passing structure consisting of input    *
 * set values                                                   *
 * Return - uint8_t                                             *
 ****************************************************************/
uint8_t error_check(struct input line)
{
    /* Radix check to get proper representation as input	*
     * in line.num element of structure input. Pops up 	        *
     * error at invalid radix, and returns 1.                   */
    if (line.radix != 8 \
        && line.radix != 10 \
	&& line.radix != 16)
    {
        printf("Error: Invalid radix\n");
        printf("--------------END-OF-SEQUENCE---------------\n");
        return 1;
    }

    /* Check for valid operand size. Pops up error at invalid   *
     * operand size, and returns 1.                             */
    if (line.op_size != 4 \
        && line.op_size != 8 \
        && line.op_size != 16)
    {
        printf("Error: Invalid operand size\n");
        printf("--------------END-OF-SEQUENCE---------------\n");
        return 1;
    }

    /* Check for too-big numbers                               *
     * 0xFFFF is the maximum 16 bit number, and then using     *
     * bit shifts, I am trying to make maximum for different   *
     * operand sizes. Similar with the negative part.          *
     * So, for 8 bit operand, check will happen from 255 to    *
     * -255 (to just print absolute values).                   */
    if ((line.num > (0xFFFF >> (16 - line.op_size))) \
        || (line.num < (((0xFFFF >> (16 - line.op_size))) * -1)))
    {
        printf("Error: Value too large for operand size.\n");
        printf("--------------END-OF-SEQUENCE---------------\n");
        return 1;
    }
	
    return 0;
}

/****************************************************************
 * Binary Print function - Prints binary representation of      *
 * argument passed                                              *
 * print function.                                              *
 * Name - binary_print                                          *
 * Parameters -                                                 *
 * uint16_t (number_to_print) - decimal number to print binary  *
 * uint8_t (number_of_digits) - bit length                      *
 * Return - void                                                *
 ****************************************************************/
void binary_print(uint16_t binary, uint8_t digits)
{
    /* A buffer to store characters */
    char c[20];
    // Initial characters of binary representation
    c[0] = '0';
    c[1] = 'b';

    /* Go to the end of the c array and start           *
     * filling 1s and 0s based on bits of number.       *
     * len = 2 + digits is for starting the index       *
     * from end, but i = len - 1 is to have space       *
     * for null terminator                              */
    uint8_t len = 2 + digits;
    for (uint8_t i = len - 1; i > 1; i--)
    {
        /* If the last bit is 1, then 1.        *
         * Otherwise 0.                         *
         * Then shift bits to left one at a time*/
        if (binary & 0x01)
        {
            c[i] = '1';
        }
        else
        {
            c[i] = '0';
        }
        binary = binary >> 1;
    }
    // Terminator character
    c[len] = '\0';
    // Left aligned and with set width for neat output
    printf("%-18s\t", c);
}

/****************************************************************
 * Print Output function - This function takes the structure    *
 * with input data, and prints out the table with different     *
 * representations of the number.                               *
 * Name - print_output                                          *
 * Parameters - struct input                                    *
 * Return - void                                                *
 ****************************************************************/
void print_output(struct input line)
{
    /* Variables that will be used                              *
     * x = absolute value of number                             *
     * size = operand size                                      *
     * max = maximum value that operand size can accomodate     *
     * minone, mintwo, minsign = minimum values in one's        *
     * complement, two's complement, and sign magnitude         */
    const int32_t num = line.num;
    const uint16_t x = abs(num);
    const uint8_t size = line.op_size;
    uint16_t max, minone, mintwo, minsign;

    /* Printing title line, used printf width specifiers       */
    printf("%-23s\t%-18s\t%-18s\t%-18s\n", " ", "Value", \
           "Maximum", "Minimum");

    /*---------------------------------------------------------*/
    /* Printing line with binary representation                */
    /* %-23s prints out a string with width 23 and aligned     *
     * towards left.                                           *
     * binary_print() prints binary representaion              */

    printf("%-23s\t", "Binary(abs)");
    binary_print(x, size);
    binary_print(MAX, size);
    binary_print(MIN, size);
    printf("\n");

    /*---------------------------------------------------------*/
    /* Printing line with octal representation                 */
    /* MAX & (0xFFFF >> (16 - size)) gives a value of          *
     * that's maximum for particular operand size.             *
     * Ex. 0xFF is maximum for 8 bits. Hence, 0xFFFF will      *
     * shift by 8 bits, and this will be used as bit mask      *
     * for MAX                                                 */

    printf("%-23s\t%#-18o\t%#-18o\t%#-18o\n", "Octal(abs)", x, \
           (MAX & (0xFFFF >> (16 - size))), \
           (MIN & (0x0 >> (16 - size))));

    /*---------------------------------------------------------*/
    /* Printing line with decimal representation               */

    printf("%-23s\t%-18d\t%-18d\t%-18d\n", "Decimal(abs)", x, \
           (MAX & (0xFFFF >> (16 - size))), \
           (MIN & (0x0 >> (16 - size))));
	
    /*---------------------------------------------------------*/
    /* Printing line with hexadecimal representation           */

    printf("%-23s\t%#-18x\t%#-18x\t%#-18x\n", "Hexadecimal(abs)", 
           x, (MAX & (0xFFFF >> (16 - size))), \
           (MIN & (0x0 >> (16 - size))));

    /*----------------------------------------------------------*/
    /* Calculating maximum and minimum value represented        *
     * in different representations                             *
     * Masking MAX and shifting it left by 1 - why? To          *
     * create a space for sign bit.                             */

    max = (MAX & (0xFFFF >> (16 - size))) >> 1;
    minone = ~max | 0x01 << size;
    minone = onescomplement(max, size); 
    mintwo = twoscomplement(max, size);
    minsign = signmagnitude(max, size);

    /* Printing one's complement representation                 *
     * if condition is there to thrrow error when signed        *
     * representations can't be computed due to lack of         *
     * space. Usually, 2^(n-1) is the maximum for signed        *
     * bits. 2^(n-1) is achieved by bit shifts.                 */
	
    printf("Signed One's Complement\t");
    if (x < (0x01 << (size - 1)))
    {
        if (num > 0)
        {
            binary_print(num, size);
        }
        else
        {
            binary_print(onescomplement(x, size), size);
        }
    }
    else
    {
        printf("%-23s\t", "Error");
    }
    binary_print(max, size);
    binary_print(minone, size);
    printf("\n");

    /*----------------------------------------------------------*/
    /* Printing two's complement representation */

    printf("Signed Two's Complement\t");
    if (x < (0x01 << (size - 1)))
    {
        if (num > 0)
        {
            binary_print(num, size);
        }
        else
        {
            binary_print(twoscomplement(x, size), size);
        }
    }
    else
    {
        printf("%-23s\t", "Error");
    }
    binary_print(max, size);
    binary_print(mintwo, size);
    printf("\n");

    /*----------------------------------------------------------*/
    /* Printing sign-magnitude representation */

    printf("%-23s\t", "Sign-Magnitude");
    if (x < (0x01 << (size - 1)))
    {
        if (num > 0)
        {
            binary_print(num, size);
        }
        else
        {
            binary_print(signmagnitude(x, size), size);
        }
    }  
    else
    {
        printf("%-23s\t", "Error");
    }
    binary_print(max, size);
    binary_print(minsign, size);
    printf("\n");
}

/*****************************************************************
 * One's complement function - calculates and returns one's      *
 * complement of a number                                        *
 * Name - onescomplement                                         *
 * Parameters -                                                  *
 * uint16_t number - decimal number to be converted to one's     *
 * complement form                                               *
 * uint8_t size - operand size                                   *
 * Return - uint16_t - one's complement value                    *
 *****************************************************************/
uint16_t onescomplement(uint16_t number, uint8_t size)
{
    /* Variable mask is to be used as bit mask */
    uint16_t mask = 0;

    // Bitwise not operation will complement every bit
    number = ~number;

    // Configure mask for different operand sizes
    if (size == 4)
    {
        mask = 0x0F;
    }
    else if (size == 8)
    {
        mask = 0xFF;
    }
    else if (size == 16)
    {
        mask = 0xFFFF;
    }
    number = number & mask;
    return number;
}


/*****************************************************************
 * Two's Complement function - calculates and returns two's      *
 * complement representation of a number                         *
 * Name - twoscomplement                                         *
 * Parameters -                                                  *
 * uint16_t number - number to be converted to two's complement  *
 * uint8_t size - operand size                                   *
 * Return - uint16_t - two's complement value                    *
 *****************************************************************/
uint16_t twoscomplement(uint16_t number, uint8_t size)
{
    // Adding one to one's complement leads to required 
    // two's complement
    return onescomplement(number, size) + 1;
}

/*****************************************************************
 * Sign Magnitude function - calculates and returns sign         *
 * magnitude representation of a number                          *
 * Name - signmagnitude                                          *
 * Parameters -                                                  *
 * uint16_t number - number to be converted to sign magnitude    *
 * uint8_t size - operand size                                   *
 * Return - uint16_t - signed magnitude value                    *
 *****************************************************************/
uint16_t signmagnitude(uint16_t number, uint8_t size)
{
    // Just change the MSB to 1
    return number | 0x0001 << (size - 1);
}

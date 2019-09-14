/* Includes */
#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>


/* Global Variables */
struct input
{
	uint32_t num;
	uint8_t radix;
	uint8_t op_size;
}line;
const uint16_t MAX = 0xFFFF;
const uint16_t MIN = 0x0000;

/* Function Declarations */
void binary_print(uint16_t, uint8_t);
void print_output(struct input);
uint16_t onescomplement(uint16_t, uint8_t);
uint16_t twoscomplement(uint16_t, uint8_t);
uint16_t signmagnitude(uint16_t, uint8_t);

int main (void)
{
	char line_input[20];
	int c, i = 0, scan_check;
	printf("Enter the input set {number, radix, operand size}:\n");
	while((c = getchar()) != '\n')
	{
		line_input[i] = c;
		i++;
	}
	line_input[i] = '\0';

	sscanf(line_input, "{%*[^ ]%hhu, %hhu}", &line.radix, \
			&line.op_size);
	if(line.radix == 8)
	{
		scan_check = sscanf(line_input, "{%o, *}", &line.num);
	}
	else if(line.radix == 10)
	{
		scan_check = sscanf(line_input, "{%d, *}", &line.num);
	}
	else if(line.radix == 16)
	{
		scan_check = sscanf(line_input, "{%x, *}", &line.num);
	}
	else
	{
		printf("Error: Invalid radix\n");
		return 1;
	}
	if (scan_check == 0)
	{
		printf("Error: Radix and number format mismatch\n");
		return 1;
	}
	if (line.op_size != 4 \
	    && line.op_size != 8 \
	    && line.op_size != 16)
	{
		printf("Error: Invalid operand size\n");
		return 1;
	}
	printf("%d, %hhu, %hhu\n", line.num, line.radix, \
				   line.op_size);

	print_output(line);

	return 0;
}


void binary_print(uint16_t binary, uint8_t digits)
{
	char c[20];
	c[0] = '0';
	c[1] = 'b';
	int len = 2 + digits;
	for(int i = len - 1; i > 1; i--)
	{
		if(binary & 0x01)
		{
			c[i] = '1';
		}
		else
		{
			c[i] = '0';
		}
		binary = binary >> 1;
	}
	c[len] = '\0';
	printf("%-18s\t", c);
}

void print_output(struct input line)
{
	const uint16_t x = abs(line.num);
	const uint8_t size = line.op_size;
	uint16_t max, minone, mintwo, minsign;

	printf("%-23s\t%-18s\t%-18s\t%-18s\n", " ", "Value", \
			"Maximum", "Minimum");

	printf("%-23s\t", "Binary(abs)");
	binary_print(x, size);
	binary_print(MAX, size);
	binary_print(MIN, size);
	printf("\n");

	printf("%-23s\t%#-18o\t%#-18o\t%#-18o\n", "Octal(abs)", x, \
			(MAX & (0xFFFF >> (16 - size))), \
			(MIN & (0xFF >> (16 - size))));

	printf("%-23s\t%-18d\t%-18d\t%-18d\n", "Decimal(abs)", x, \
			(0xFFFF & (0xFFFF >> (16 - size))), \
			(0x0 & (0x0 >> (16 - size))));
	
	printf("%-23s\t%#-18x\t%#-18x\t%#-18x\n", "Hexadecimal(abs)"\
			, x, (0xFFFF & (0xFFFF >> (16 - size))), \
			(0x0 & (0x0 >> (16 - size))));

	max = (MAX & (0xFFFF >> (16 - size))) >> 1;
	minone = ~max | 0x01 << size;
	minone = onescomplement(max, size); 
	mintwo = twoscomplement(max, size);
	minsign = signmagnitude(max, size);

	printf("Signed One's Complement\t");
	binary_print(onescomplement(x, size), size);
	binary_print(max, size);
	binary_print(minone, size);
	printf("\n");
	
	printf("Signed Two's Complement\t");
	binary_print(twoscomplement(x, size), size);
	binary_print(max, size);
	binary_print(mintwo, size);
	printf("\n");
	
	printf("%-23s\t", "Sign-Magnitude");
	binary_print(signmagnitude(x, size), size);
	binary_print(max, size);
	binary_print(minsign, size);
	printf("\n");
}

uint16_t onescomplement(uint16_t number, uint8_t size)
{
	uint16_t mask = 0;
	number = ~number;
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

uint16_t twoscomplement(uint16_t number, uint8_t size)
{
	return onescomplement(number, size) + 1;
}

uint16_t signmagnitude(uint16_t number, uint8_t size)
{
	return number | 0x0001 << (size - 1);
}

#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>

void binary_print(uint16_t num);
void test(uint16_t num);

int main(void)
{
	uint16_t number = 0xCAFE;
	uint16_t temp;
	printf("%#x\n", number);
	test(number);
	binary_print(number);
	
	temp = (number & 0xFF00) >> 8;
	number = number << 8;
	number = number + temp;
	printf("%#x\n", number);
	test(number);
	binary_print(number);

	temp = (number & 0xF000) >> 12;
	number = number << 4;
	number = number + temp;
	printf("%#x\n", number);
	test(number);
	binary_print(number);

	temp = (number & 0x00FF) << 8;
	number = number >> 8;
	number = number + temp;
	printf("%#x\n", number);
	test(number);
	binary_print(number);
	return 0;
}

void binary_print(uint16_t num)
{
	int i;
	char c[19] = "0b0000000000000000";
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
	printf("%s\n", c);
}

void test(uint16_t num)
{
	num = num & 0x000F;
	if(num == 0x7 || num == 0xB || num == 0xD || num == 0xE || num == 0xF)
	{
		printf("TRUE!\n");
	}
	else
	{
		printf("FALSE!\n");
	}
}	

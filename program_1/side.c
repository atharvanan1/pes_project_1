#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>

void binary_print(uint16_t, uint8_t);

int main (void)
{
	uint16_t num = 0xCAFE;
	binary_print(num, 16);
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
	printf("%s\n", c);
}

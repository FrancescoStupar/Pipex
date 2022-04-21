//
/**********************************************************************
** 1.2 : Reversing bits on an octet (octet means 8 bits or 1 byte)
**********************************************************************/

/*
** This a vanilla question for interviews :
** Write a function that takes a byte, reverses it, bit by bit (like the
** example) and returns the result.
** 
** Your function must be declared as follows:
** 
** unsigned char	reverse_bits(unsigned char octet);
** 
** Example:
** 
**   1 byte
** _____________
**  0100  0001
**      ||
**      \/
**  1000  0010
*/



#include "pipex.h"

void	print_bits(unsigned char n)
{
	int x;

	x = 256;
	while(x>>=1)
	{
		if (n & x)
			write(1, "1", 1);
		else
			write(1, "0", 1);
	}
	write(1, "\n", 1);
}

unsigned char	reverse_bits(unsigned char n)
{
	int x;
	int y;

	y = 8;
	x = 0;
	while(y--)
	{
		x = (x << 1) | (n & 1);
		n = n >> 1;
	}
	return(x);
}

int main()
{
	int n = 7;
	print_bits(n);
	n = reverse_bits(n);
	print_bits(n);
	return(0);
}
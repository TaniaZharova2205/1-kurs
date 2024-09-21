#include <stdio.h>
_Bool R(int a)
{
	return ((a=='\n')||(a=='\t')||(a==' '));
}
int main()
{
	int a[1000],str=0,words=0,i=0,j;
	while ((a[i] = getchar()) != EOF)
	{
		if (a[i]=='\n')
			str++;
		if ((i!=0)&&(R(a[i]))&&(!R(a[i-1])))
			words++;
		i++;
	}
	printf("%d символов,%d строк,%d слов\n",i,str,words);
	for (j=0;j<i;j++)
		putchar(a[j]);
	return 0;
}

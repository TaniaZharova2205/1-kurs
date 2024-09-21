#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int inputtoint(int number, int i)//переводим в код 16 системы
{
  int buf[8];
  switch(number)
  {
    case 1:{ 
      int buf[8] = {0x1,0x3,0x5,0x9,0x1,0x1,0x1,0x1};
      return(buf[i]);};
    case 2:{
       int buf[8] = {0x6,0x9,0x9,0x1,0x1,0x2,0x4,0xf};
       return(buf[i]);};
    case 3:{
      int buf[8] = {0x6,0x9,0x1,0x2,0x1,0x1,0x9,0x6};
      return(buf[i]);};
    case 4:{
      int buf[8] = {0x9,0x9,0x9,0xf,0x1,0x1,0x1,0x1};
      return(buf[i]);};
    case 5:{
      int buf[8] = {0xf,0x8,0x8,0x8,0xf,0x1,0x1,0xf}; 
      return(buf[i]);};
    case 6:{
      int buf[8] = {0x6,0x9,0x8,0x8,0xf,0x9,0x9,0xf}; 
      return(buf[i]);};
    case 7:{
      int buf[8] = {0xf,0x9,0x1,0x1,0x1,0x1,0x1,0x1}; 
      return(buf[i]);};
    case 8:{
      int buf[8] = {0xf,0x9,0x9,0x6,0x9,0x9,0x9,0xf};
      return(buf[i]);};
    case 9:{
      int buf[8] = {0x6,0x9,0x9,0x7,0x1,0x1,0x9,0x6};
      return(buf[i]);};
    case 0:{
      int buf[8] = {0x6,0x9,0x9,0x9,0x9,0x9,0x9,0x6};
      return(buf[i]);};
    default:{
      int buf[8] = {0x6,0x9,0x9,0x9,0x9,0x9,0x9,0x6};
      return(buf[i]);};
  }
}

int countdigits(int n)
{
	if(n==0)	return(1);
  int i=0;
  while(n>0)
  {
    n /= 10;
    i++;
  }
  return(i);
}

void hextobin(int hex)
{
  int dec, i, del;
  switch(hex)
  {
    case 'a': dec = 10; break;
    case 'b': dec = 11; break;
    case 'c': dec = 12; break;
    case 'd': dec = 13; break;
    case 'e': dec = 14; break;
    case 'f': dec = 15; break;
    default: dec = hex; break;
  }
  for(i=3; i>=0; i--)
  {
    del = pow(2,i);
    if((dec/del)==0)
      printf(" ");
    else
      printf("#");
    dec = dec % del;
  }
	putchar(' ');
}

void output(int buf[], int i)
{
  int hex;
  hex = buf[i];
  hextobin(hex);
}

int main()
{
  int number, c, p, i, del, buf[8], j, num;
  printf("Введите число\n");
  while(scanf("%d", &number) != 1)
  {
    while(getchar()!='\n'){}
      printf("Повторите ввод\n");}
  c = countdigits(number);
  for(i=0; i<8; i++)
	{
		p = c;
		num = number;
  	for(j=0; j<c; j++)
		{
    	p--;
    	del = pow(10, p);
    	buf[i] = inputtoint(num/del, i);
    	output(buf, i);
    	num %= del;
  	}
		putchar('\n');
	}
  return 0;
}

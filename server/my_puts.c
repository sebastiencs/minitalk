/*
** my_puts.c for minitalk in /home/chapui_s/travaux/minitalk/server
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Sun Mar 16 13:49:45 2014 chapui_s
** Last update Sun Mar 16 13:54:15 2014 chapui_s
*/

#include <unistd.h>

void		my_putchar(char c)
{
  write(1, &c, 1);
}

void		my_putstr(char *s)
{
  while (s && *s)
    write(1, s++, 1);
}

void		my_putnbr(int n)
{
  if (n < 0)
  {
    my_putchar('-');
    n = -n;
  }
  if (n >= 10)
    my_putnbr(n / 10);
  my_putchar((n % 10) + '0');
}

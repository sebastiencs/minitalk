/*
** utils.c for minitalk in /home/chapui_s/travaux/minitalk/client
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Sun Mar 16 17:39:23 2014 chapui_s
** Last update Thu Mar 20 12:44:00 2014 chapui_s
*/

#include <unistd.h>

int		my_strlen(char *str)
{
  int		size;

  size = 0;
  while (str[size])
    size += 1;
  return (size);
}

int		my_puterror(char *s)
{
  while (s && *s)
    write(2, s++, 1);
  return (-1);
}

/*
** utils.c for minitalk in /home/chapui_s/travaux/minitalk/client
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Sun Mar 16 17:39:23 2014 chapui_s
** Last update Sun Mar 16 17:40:21 2014 chapui_s
*/

int		my_strlen(char *str)
{
  int		size;

  size = 0;
  while (str[size])
    size += 1;
  return (size);
}

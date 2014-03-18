/*
** my_atoi.c for minitalk in /home/chapui_s/travaux/minitalk/client
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Sun Mar 16 14:10:48 2014 chapui_s
** Last update Sun Mar 16 14:10:56 2014 chapui_s
*/

int		my_atoi(char *str)
{
  int		i;
  int		negativ;
  int		number;

  i = 0;
  negativ = 0;
  number = 0;
  while ((str[i] == ' ') || (str[i] == '\t') || (str[i] == '\n')
	 || (str[i] == '\v') || (str[i] == '\f') || (str[i] == '\r'))
    i++;
  if (str[i] == 45)
    negativ = 1;
  if ((str[i] == 45) || (str[i] == 43))
    i++;
  while (str[i] >= 48 && str[i] <= 57)
  {
    number *= 10;
    number += ((int)str[i] - 48);
    i++;
  }
  if (negativ == 1)
    return (-number);
  else
    return (number);
}

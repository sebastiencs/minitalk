/*
** main.c for minitalk in /home/chapui_s/travaux/minitalk/server
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Sun Mar 16 13:49:45 2014 chapui_s
** Last update Tue Mar 18 14:04:43 2014 chapui_s
*/

#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include "server.h"

#include <stdio.h>

char		*str[2];

void		my_putnbr_bin(int nb)
{
  if (nb >= 2)
    my_putnbr_bin(nb / 2);
  my_putchar((nb % 2) + '0');
}

static void	disp_pid(pid_t pid)
{
  my_putstr("pid: ");
  my_putnbr(pid);
  my_putchar('\n');
}

void		str_to_zero(char *str)
{
  int		i;

  i = 0;
  while (i < 9)
    str[i++] = 0;
}

int		save_pid_client(int nb)
{
  static int	current;

  str[1][0] = 0;
  if (nb != 0b1111111)
    str[1][current] = nb;
  current += 1;
  if (nb == 0b1111111 && current > 1)
  {
    str[1][current - 1] = '\0';
    str[1][0] = 1;
    printf("  // new talk from %s \\\\\n", str[1] + 1);
    kill(SIGUSR1, my_atoi(str[1] + 1));
    current = 0;
    return (0);
  }
  return (1);
}

void		my_print_binary(char *str)
{
  static int	is_pid;
  int		i;
  int		nb;

  i = 0;
  nb = 0;
  while (str[i])
  {
    /* my_putchar(str[i]); */
    nb |= (str[i] - '0') << (6 - i);
    i += 1;
  }
  /* my_putnbr_bin(nb); */
  /* my_putchar('\n'); */
  if (nb != 0b1111111 && is_pid == 0)
  {
    my_putchar(nb);
    is_pid = 0;
  }
  else if (nb == 0b1111111 || is_pid == 1)
  {
    is_pid = 1;
    is_pid = save_pid_client(nb);
  }
}

static void	add_bit(char bit)
{
  static int	current = 0;

  str[0][current] = bit + '0';
  str[0][current + 1] = 0;
  current += 1;
//  my_print_binary(str);
  if (current == 7)
 {
    /* my_putstr(str); */
    /* str[7] = 0; */
    my_print_binary(str[0]);
    /* my_putchar('\n'); */
    current = 0;
  }
}

void		get_usr1(int sig)
{
  (void)sig;
  /* my_putchar('0'); */
  add_bit(0);
  /* printf("my_atoi(str[1] + 1) = %d\n", my_atoi(str[1] + 1)); */
  if (str[1][0] == 1)
  {
    kill(my_atoi(str[1] + 1), SIGUSR1);
  }
}

void		get_usr2(int sig)
{
  (void)sig;
  /* my_putchar('1'); */
  add_bit(1);
  /* if (str[1][0] == 1) */
  /* printf("my_atoi(str[1] + 1) = %d\n", my_atoi(str[1] + 1)); */
  if (str[1][0] == 1)
  {
    kill(my_atoi(str[1] + 1), SIGUSR2);
  }
}

static int	get_msg(void)
{
  signal(SIGUSR2, get_usr2);
  signal(SIGUSR1, get_usr1);
  while (42)
  {
  }
  return (0);
}


int		main(int argc, char **argv)
{
  pid_t		pid;

  if ((str[0] = (char*)malloc(9)) == NULL)
    return (0);
  if ((str[1] = (char*)malloc(9)) == NULL)
    return (0);
  str_to_zero(str[0]);
  str[8] = '\0';
  disp_pid(pid = getpid());
  get_msg();
  return (0);
}

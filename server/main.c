/*
** main.c for minitalk in /home/chapui_s/travaux/minitalk/server
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Sun Mar 16 13:49:45 2014 chapui_s
** Last update Tue Mar 18 22:44:11 2014 chapui_s
*/

#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include "server.h"

int		pid_client;

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

int		save_pid_client(int nb)
{
  static int	current;
  static int	pid_cur;

  pid_client = -1;
  if (current == 0)
    current = 10;
  if (nb != 0b1111111)
    pid_cur = (pid_cur * current) + (nb - '0');
  if (nb == 0b1111111 && pid_cur != 0)
  {
    pid_client = pid_cur;
    my_putstr("  // talk from ");
    my_putnbr(pid_client);
    my_putstr(" \\\\\n");
    pid_cur = 0;
    return (0);
  }
  return (1);
}

void		my_print_binary(int nb)
{
  static int	is_pid;

  if (nb == 0)
    my_putchar('\n');
  if (((nb >= 32 && nb <= 126) || (nb >= 7 && nb <= 13)) && is_pid == 0)
    my_putchar(nb);
  else if (nb == 0b1111111 || is_pid == 1)
    is_pid = save_pid_client(nb);
}

static void	add_bit(char bit)
{
  static int	i;
  static int	nb;

  nb |= bit << (6 - i);
  i += 1;
  if (i == 7)
  {
    my_print_binary(nb);
    i = 0;
    nb = 0;
  }
}

void		get_usr1(int sig)
{
  (void)sig;
  add_bit(0);
  if (pid_client != -1)
    kill(pid_client, SIGUSR1);
}

void		get_usr2(int sig)
{
  (void)sig;
  add_bit(1);
  if (pid_client != -1)
    kill(pid_client, SIGUSR1);
}

int		main(int argc, char **argv)
{
  pid_t		pid;

  (void)argc;
  (void)argv;
  disp_pid(pid = getpid());
  pid_client = -1;
  signal(SIGUSR2, get_usr2);
  signal(SIGUSR1, get_usr1);
  while (42)
    ;
  return (0);
}

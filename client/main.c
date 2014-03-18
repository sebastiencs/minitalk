/*
** main.c for minitalk in /home/chapui_s/travaux/minitalk/client
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Sun Mar 16 14:02:32 2014 chapui_s
** Last update Tue Mar 18 15:19:54 2014 chapui_s
*/

#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

#include <stdio.h>

int	wait;

void	my_putchar(char c)
{
  write(1, &c, 1);
}

int	get_size_bin(int nb)
{
  int	size;

  size = 1;
  while (nb / 2)
  {
    size += 1;
    nb /= 2;
  }
  return (size);
}

void	get_usr1(int pid)
{
  /* (void)pid; */
  wait += 1;
  write(1, "A", 1);
  /* usleep(1000); */
  /* printf("RECU\n"); */
}

void	get_usr2(int pid)
{
  /* (void)pid; */
  wait += 1;
  write(1, "B", 1);
  /* write(1, "A", 1); */
  /* usleep(1000); */
}

int	get_size_decimal(int nb)
{
  int	size;

  size = 1;
  while (nb / 10)
  {
    size += 1;
    nb /= 10;
  }
  return (size);
}

char		*reverse_str(char *str)
{
  char		*new_str;
  int		i;
  int		j;

  if ((new_str = (char*)malloc(my_strlen(str) + 3)) == NULL)
    return (NULL);
  i = 1;
  j = my_strlen(str) - 1;
  while (j >= 0)
  {
    new_str[i] = str[j];
    i += 1;
    j -= 1;
  }
  new_str[0] = 0b1111111;
  new_str[i] = 0b1111111;
  new_str[i + 1] = '\0';
  return (new_str);
}

void		my_put_binary(int nb, int pid)
{
  char		base[2];
  int		i;

  base[0] = '0';
  base[1] = '1';
//  wait = ;
//  complete_size_bin(nb, pid);
  wait = 1;
  signal(SIGUSR1, get_usr1);
  signal(SIGUSR2, get_usr2);
  if (nb >= 2)
    my_put_binary(nb / 2, pid);
  i = 0;
  while (wait == 0 && ++i < 5)
  {
    usleep(500);
  }
  if ((nb % 2))
  {
    my_putchar('1');
    kill(pid, SIGUSR2);
    /* usleep(10000); */
  }
  else
  {
    my_putchar('0');
    kill(pid, SIGUSR1);
    /* usleep(10000); */
  }
  wait = 0;
}

void	complete_size_bin(int nb, int pid)
{
  int	size;
  int	i;

  size = get_size_bin(nb);
  wait = 0;
  /* signal(SIGUSR1, get_usr1); */
  /* signal(SIGUSR2, get_usr2); */
  printf("size = %d\n", size);
  while (size < 7)
  {
    usleep(10000);
    kill(pid, SIGUSR1);
    my_putchar('0');
    usleep(10000);
    size += 1;
  }
  my_put_binary(nb, pid);
  /* wait = 1; */
}

void		my_put_binary_pid(int nb, int pid)
{
  char		base[2];

  base[0] = '0';
  base[1] = '1';
  /* wait = 0; */
  signal(SIGUSR1, get_usr1);
  signal(SIGUSR2, get_usr2);
//  complete_size_bin(nb, pid);
  if (nb >= 2)
    my_put_binary_pid(nb / 2, pid);
    /* usleep(10000); */
  /* if (wait == 1 || str[1] == 0) */
  if ((nb % 2))
  {
    my_putchar('1');
    kill(pid, SIGUSR2);
    usleep(10000);
  }
  else
  {
    my_putchar('0');
    kill(pid, SIGUSR1);
    usleep(10000);
  }
  /* wait = 1; */
  //my_putchar(base[nb % 2]);
}

void	complete_size_bin_pid(int nb, int pid)
{
  int	size;
  int	i;

  size = get_size_bin(nb);
  printf("size = %d\n", size);
  while (size < 7)
  {
    kill(pid, SIGUSR1);
    my_putchar('0');
    usleep(10000);
    size += 1;
  }
  my_put_binary_pid(nb, pid);
}

int		give_pid_to_server(int pid_client, int pid_server)
{
  char		*str;
  int		tmp;
  int		size;
  int		i;

  i = 0;
  tmp = pid_client;
  size = get_size_decimal(pid_client);
  if ((str = (char*)malloc(size + 1)) == NULL)
    return (-1);
  while (tmp > 0)
  {
    str[i] = (tmp % 10) + '0';
    tmp = tmp / 10;
    i += 1;
  }
  str[i] = '\0';
  if ((str = reverse_str(str)) == NULL)
    return (-1);
  i = 0;
  printf("str = %s\n", str);
  wait = 0;
  while (str[i])
    complete_size_bin_pid(str[i++], pid_server);
  return (0);
}

int		main(int argc, char **argv)
{
  char		*str;
  int		pid_server;
  int		pid_client;

  if (argc < 2)
    return (0);
  pid_server = my_atoi(argv[1]);
  pid_client = getpid();
  printf("pid_client = %d\n", pid_client);
  give_pid_to_server(pid_client, pid_server);
  str = "coucou\n\n~#//1234\\#~\n";

  int	i;

  i = 0;

  wait = 0;
  while (str[i])
  {
    complete_size_bin(str[i], pid_server);
    i += 1;
  }

  return (0);
}

/*
** main.c for minitalk in /home/chapui_s/travaux/minitalk/client
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Sun Mar 16 14:02:32 2014 chapui_s
** Last update Tue Mar 18 23:04:40 2014 chapui_s
*/

#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

#include <stdio.h>

char		*str;
int		pid_server;

void		get_usr1(int pid);

void		my_putchar(char c)
{
  write(1, &c, 1);
}

void		my_putstr(char *s)
{
  while (s && *s)
    write(1, s++, 1);
}

int		get_size_bin(int nb)
{
  int		size;

  size = 1;
  while (nb / 2)
  {
    size += 1;
    nb /= 2;
  }
  return (size);
}

int		get_size_decimal(int nb)
{
  int		size;

  size = 1;
  while (nb / 10)
  {
    size += 1;
    nb /= 10;
  }
  return (size);
}

char		*reverse_str(char *str_to_rev)
{
  char		*new_str;
  int		i;
  int		j;

  if ((new_str = (char*)malloc(my_strlen(str_to_rev) + 3)) == NULL)
    return (NULL);
  i = 1;
  j = my_strlen(str_to_rev) - 1;
  while (j >= 0)
  {
    new_str[i] = str_to_rev[j];
    i += 1;
    j -= 1;
  }
  new_str[0] = 0b1111111;
  new_str[i] = 0b1111111;
  new_str[i + 1] = '\0';
  free(str_to_rev);
  return (new_str);
}

void		my_put_binary_pid(int nb, int pid)
{
  if (nb >= 2)
    my_put_binary_pid(nb / 2, pid);
  if ((nb % 2))
  {
    kill(pid, SIGUSR2);
  }
  else
  {
    kill(pid, SIGUSR1);
  }
  usleep(1000);
}

void		complete_size_bin_pid(int nb, int pid)
{
  int		size;
  int		i;

  size = get_size_bin(nb);
  while (size < 7)
  {
    kill(pid, SIGUSR1);
    usleep(1000);
    size += 1;
  }
  my_put_binary_pid(nb, pid);
}

int		give_pid_to_server(int pid_client, int pid_server)
{
  char		*str_pid;
  int		tmp;
  int		size;
  int		i;

  i = 0;
  tmp = pid_client;
  size = get_size_decimal(pid_client);
  if ((str_pid = (char*)malloc(size + 1)) == NULL)
    return (-1);
  while (tmp > 0)
  {
    str_pid[i] = (tmp % 10) + '0';
    tmp = tmp / 10;
    i += 1;
  }
  str_pid[i] = '\0';
  if ((str_pid = reverse_str(str_pid)) == NULL)
    return (-1);
  i = 0;
  while (str_pid[i])
    complete_size_bin_pid(str_pid[i++], pid_server);
  free(str_pid);
  return (0);
}

void		send_bit(void)
{
  static int	i;

  if (!(*str))
  {
    if (i < 7)
      kill(pid_server, SIGUSR1);
    else
      str = NULL;
    i += 1;
  }
  else
  {
    if (i == 0)
      i = 0b1000000;
    kill(pid_server, ((*str & i) > 0) ? (SIGUSR2) : (SIGUSR1));
    i = i >> 1;
    if (i <= 0)
    {
      str = str + 1;
      i = 0;
    }
  }
}

void		get_usr1(int pid)
{
  (void)pid;
  send_bit();
}

int		check_args(int argc, char **argv)
{
  int		value;
  int		i;

  value = 0;
  if (argc < 3)
    value = -1;
  if (value == 0)
  {
    i = 0;
    while (argv[1][i])
    {
      if (argv[1][i] < '0' || argv[1][i] > '9')
	value = -1;
      i += 1;
    }
  }
  if (value == -1)
  {
    my_putstr("usage:\n\tclient [PID_SERVER] [MESSAGE]\n");
    my_putstr("\n\t\t- PID must be numerical\n");
  }
  return (value);
}

void		save_pid(int pid_server)
{

}

int		main(int argc, char **argv)
{
  int		pid_client;

  if (check_args(argc, argv) == -1)
    return (-1);
  str = argv[2];
  signal(SIGUSR1, get_usr1);
  pid_server = my_atoi(argv[1]);
  save_pid(pid_server);
  pid_client = getpid();
  if ((give_pid_to_server(pid_client, pid_server)) == -1)
  {
    my_putstr("error: could not alloc\n");
    return (-1);
  }
  while (str)
    signal(SIGUSR1, get_usr1);
  return (0);
}

/*
** nbr_arg.c for strace in /home/scipio_a/rendu/AUSP_strace
** 
** Made by alexandre scipion
** Login   <scipio_a@epitech.net>
** 
** Started on  Thu May 14 11:51:12 2015 alexandre scipion
** Last update Thu May 21 12:53:39 2015 alexandre scipion
*/

#include "strace.h"

int	analyse_arg(char *arg,
		    struct user_regs_struct regs,
		    pid_t child,
		    char *name)
{
  int	i;
  int	nbr_arg;
  int	type;

  while (arg && arg[0] == ' ' && (nbr_arg = 1))
    arg += 1;
  if (strlen(arg) < 2 || !strncmp(arg, "()", 2) || !strncmp(arg, "(void)", 6))
    return (0);
  else
    {
      i = -1;
      type = 0;
      while (arg[++i])
	{
	  type = return_type(&arg[i]);
	  if (arg[i] == ',')
	    {
	      print_arg(regs, nbr_arg, type, child, name);
	      type = 0;
	      ++nbr_arg;
	    }
	}
      print_arg(regs, nbr_arg, type, child, name);
      return (nbr_arg);
    }
}

int	nbr_args(char *syscall,
		 struct user_regs_struct regs,
		 pid_t child)
{
  FILE	*unistd;
  int	nbr_arg;
  char	name[20];
  char	name_type[20];
  char	arg[2000];

  if (!(nbr_arg = 0) && (unistd  = fopen("./misc/prot_syscall", "r")) == NULL)
    return (0);
  while (!feof(unistd))
    {
      if (fscanf(unistd, "%20s", name) > 0 && !strcmp(name, "extern"))
	{
	  fscanf(unistd, "%20s %s20", name_type, name);
	  if (!strcmp(name_type, "unsigned"))
	    fscanf(unistd, "%20s", name);
	  if (!strcmp(name, syscall)
	      || (name[0] == '*' && !strcmp(name + 1, syscall)))
	    {
	      fscanf(unistd, "%2000[^\n]s", arg);
	      nbr_arg = analyse_arg(arg, regs, child, name);
	      break;
	    }
	}
    }
  return (my_exit(unistd, -1, nbr_arg));
}

void		print_arg(struct user_regs_struct regs,
			  int nbr,
			  int type,
			  pid_t child,
			  char *name)
{
  t_llui	reg;

  reg = return_reg(regs, nbr);
  if (nbr == 2 && !strcmp(name, "execve"))
    printf("%p", (void *)reg);
  else
    {
      if (type == 1)
	printf("%u", (unsigned int )reg);
      if (type == 2)
	printf("%p", (void *)reg);
      if (type == 4)
	printf("%d", (int)reg);
      if (type == 8)
	print_string(reg, child);
      if (type == 16)
	printf("%c", (char)reg);
      if ((!strcmp(name, "write") || !strcmp(name, "read"))
	  && (type == 32 || type == 0))
	print_string(reg, child);
      else if (type == 32 || type == 0)
	explicit_null(name, reg);
    }
}

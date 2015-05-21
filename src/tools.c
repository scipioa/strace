/*
** tools.c for strace in /home/scipio_a/rendu/AUSP_strace
** 
** Made by alexandre scipion
** Login   <scipio_a@epitech.net>
** 
** Started on  Thu May 14 11:51:26 2015 alexandre scipion
** Last update Thu May 21 12:07:56 2015 alexandre scipion
*/

#include "strace.h"

int	return_type(char *ctype)
{
  int	type;

  if (!strncmp(ctype, "unsigned int", 12))
    type = 1;
  else if (!strncmp(ctype, "size_t", 6))
    type = 1;
  else if (!strncmp(ctype, "int *", 5))
    type = 2;
  else if (!strncmp(ctype, "int", 3))
    type = 4;
  else if (!strncmp(ctype, "char *", 6))
    type = 8;
  else if (!strncmp(ctype, "char", 4))
    type = 16;
  else if (!strncmp(ctype, "void *", 6))
    type = 32;
  return (type);
}

t_llui		return_reg(struct user_regs_struct regs, int nbr)
{
  t_llui	reg;

  if (nbr == 1)
    reg = regs.rdi;
  else if (nbr == 2)
    reg = regs.rsi;
  else if (nbr == 3)
    reg = regs.rdx;
  else if (nbr == 4)
    reg = regs.rcx;
  else if (nbr == 5)
    reg = regs.r8;
  else
    reg = regs.r9;
  if (nbr >= 2)
    printf(", ");
  return (reg);
}

void	print_string(t_llui reg, pid_t child)
{
  int	x;
  char	c;

  x = 0;
  printf("\"");
  while ((c = ptrace(PTRACE_PEEKTEXT, child, reg + x, NULL)) != 0)
    {
      if (c == '\n')
	printf("\\n");
      else
	printf("%c", c);
      x += 1;
    }
  printf("\"");
}

void	explicit_null(char *name, t_llui reg)
{
  if (!strcmp(name, "brk") && reg == 0)
    printf("O");
  else if (reg == 0)
    printf("NULL");
  else
    printf("%p", (void *)reg);
}

int	my_exit(FILE *fid, int error, int exit_status)
{
  if (error == 0)
    printf("\n+++ exited with %d +++\n", exit_status);
  else if (error == 1)
    fprintf(stderr, "wait4(): %s\n", strerror(errno));
  else if (error == 2)
    fprintf(stderr, "ptrace: %s\n", strerror(errno));
  if (fclose(fid) == EOF)
    {
      fprintf(stderr, "fclose(): %s\n", strerror(errno));
      return (3);
    }
  if (error == 4)
    {
      printf("<detached ...>\n");
      return (exit_status);
    }
  if (error == -1)
    return (exit_status);
  return (error);
}

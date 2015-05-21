/*
** main.c for strace in /home/bajaze_r/rendu/AUSP_strace
** 
** Made by Ronaël BAJAZET
** Login bajaze_r <bajaze_r@epitech.net>
** 
** Started on  Sun May 17 20:21:38 2015 Ronaël BAJAZET
** Last update Thu May 21 12:54:30 2015 alexandre scipion
*/

#include "strace.h"

void	begin_print(FILE *fid,
		    char *name,
		    struct user_regs_struct regs,
		    pid_t child)
{
  get_name(fid, name, regs.rax);
  printf("%s (", name);
  if (nbr_args(name, regs, child) == 0)
    printf("void");
  printf(")");
}

void	end_print(struct user_regs_struct regs)
{
  if (regs.rax == (long long unsigned int)-2)
    printf("\t= -1\n");
  else
    printf("\t= %lld\n", regs.rax);
}

int	my_fork(char **av, char **env)
{
  pid_t child;
  char	*full_path;

  if (!(full_path = find_file(av[1], env)))
    return (42);
  child = fork();
  if (child == 0)
    {
      ptrace(PTRACE_TRACEME, 0, NULL, NULL);
      kill(getpid(), SIGSTOP);
      if (execve(full_path, &av[1], env) == -1)
	{
	  free(full_path);
	  fprintf(stderr, "ptrace: %s\n", strerror(errno));
	  return (2);
	}
    }
  else if (child == -1)
    {
      fprintf(stderr, "Error with fork()\n");
      return (2);
    }
  else
    return (father(child));
  return (0);
}

int	main(int ac, char **av, char **env)
{
  if (ac < 2 || (ac == 2 && !strcmp(av[1], "-p")))
    {
      write(2, "Usage: strace [-p] pid\n", 23);
      write(2, "Usage: strace program\n", 22);
      return (-1);
    }
  if (ac == 3 && !strcmp(av[1], "-p"))
    return (trace_pid(atoi(av[2])));
  else
    return (my_fork(av, env));
}

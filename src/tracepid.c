/*
** tracepid.c for strace in /home/scipio_a/rendu/AUSP_strace
** 
** Made by alexandre scipion
** Login   <scipio_a@epitech.net>
** 
** Started on  Thu May 14 11:50:53 2015 alexandre scipion
** Last update Sun May 17 21:50:09 2015 alexandre scipion
*/

#include "strace.h"

static int	s_pid;
static FILE	*s_fid;

void	sigHangler(int sig)
{
  if (sig == SIGINT)
    {
      kill(s_pid, SIGSTOP);
      waitpid(s_pid, NULL, 0);
      if (ptrace(PTRACE_DETACH, s_pid, NULL, sig) == -1)
	{
	  fprintf(stderr, "PTRACE_DETACH: %s\n", strerror(errno));
	  exit(2);
	}
      printf("\nProcess %d detached\n", s_pid);
      exit(my_exit(s_fid, 4, 0));
    }
}

int	father(pid_t child)
{
  int status;
  struct user_regs_struct regs;
  char	name[20];
  int first;

  if ((s_fid = open_file()) == NULL && (first = 1))
    return (1);
  while (1)
    {
      if (wait4(child, &status, 0, NULL) == -1)
	return (my_exit(s_fid, 1, 0));
      if (WIFEXITED(status))
	return (my_exit(s_fid, 0, WEXITSTATUS(status)));
      else if (WIFSIGNALED(status))
	return (my_exit(s_fid, 0, WTERMSIG(status)));
      if (ptrace(PTRACE_GETREGS, child, NULL, &regs) == -1)
	return (my_exit(s_fid, 2, 0));
      if (is_syscall(child, &regs) || !first)
	{
	  first ? begin_print(s_fid, name, regs, child) : end_print(regs);
	  first = !first;
	}
      if (ptrace(PTRACE_SINGLESTEP, child, NULL, NULL) == -1)
	return (my_exit(s_fid, 2, 0));
    }
}

int	trace_pid(pid_t pid)
{
  s_pid = pid;
  signal(SIGINT, sigHangler);
      kill(s_pid, SIGSTOP);
  if (ptrace(PTRACE_ATTACH, s_pid, NULL, NULL) == -1)
    {
      fprintf(stderr, "PTRACE_ATACH: %s\n", strerror(errno));
      return (2);
    }
  printf("Process %d attached\n", s_pid);
  return (father(pid));
}

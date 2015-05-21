/*
** parse.c for strace in /home/scipio_a/rendu/strace
** 
** Made by alexandre scipion
** Login   <scipio_a@epitech.net>
** 
** Started on  Sat May  2 10:04:51 2015 alexandre scipion
** Last update Thu May 21 12:48:12 2015 alexandre scipion
*/

#include <stdio.h>

FILE*	open_file()
{
#if __x86_64__
  return (fopen("misc/syscall64", "r"));
#else
  return (fopen("misc/syscall32", "r"));
#endif
}

char*	get_name(FILE* fid, char *name, int syscall)
{
  int	sys;

  if (ftell(fid) != 0)
    fseek(fid, 0, SEEK_SET);
  while (!feof(fid))
    {
      fscanf(fid, "%20s %d\n", name, &sys);
      if (sys == syscall)
	return (name);
    }
  return (NULL);
}

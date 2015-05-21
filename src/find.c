/*
** find.c for strace in /home/scipio_a/rendu/AUSP_strace
** 
** Made by alexandre scipion
** Login   <scipio_a@epitech.net>
** 
** Started on  Thu May 14 11:56:03 2015 alexandre scipion
** Last update Thu May 21 14:04:32 2015 alexandre scipion
*/

#include "strace.h"

/*
**	check if we can execute the prog
*/
char	*check_access(char *name, char *path)
{
  char	*full_path;

  if (!(full_path = calloc(strlen(name) + strlen(path) + 2,
			   sizeof(*full_path))))
    return (NULL);
  full_path = strcpy(full_path, path);
  full_path = strcat(full_path, "/");
  full_path = strcat(full_path, name);
  if (access(full_path, X_OK) == 0)
    return (full_path);
  else
    {
      free(full_path);
      return (NULL);
    }
}

char	*set_path(char *name, char *full_path, char *backup, char *path)
{
  char	check_path[400];

  if ((full_path = strdup(name)) != NULL)
    {
      if (access(full_path, X_OK) == 0)
	return (full_path);
      else
	free(full_path);
    }
  else
    return (NULL);
  while (path && path[0] && sscanf(path, "%400[^:]s", check_path))
    {
      if ((full_path = check_access(name, check_path)))
	{
	  free(backup);
	  return (full_path);
	}
      path += strlen(check_path);
      if (path && path[0] == ':')
	++path;
    }
  return (NULL);
}

/*
**	return the path of the name.
**	try ./ and all PATH in env
**	return NULL if nothing is found
*/
char	*find_file(char *name, char **env)
{
  int	i;
  char	path_env[5];
  char	*full_path;
  char	*path;
  char	*backup;

  i = 0;
  full_path = NULL;
  while (env && env[i])
    {
      sscanf(env[i], "%5s\n", path_env);
      if (!strcmp("PATH=", path_env))
	{
	  if (!(path = strdup(env[i] + 5)))
	    return (NULL);
	  backup = path;
	  if ((full_path = set_path(name, full_path, backup, path)) != NULL)
	    return (full_path);
	  free(backup);
	  break;
	}
      ++i;
    }
  fprintf(stderr, "Impossible to open %s :(\n", name);
  return (NULL);
}

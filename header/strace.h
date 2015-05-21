/*
** strace.h for strace in /home/scipio_a/rendu/AUSP_strace
** 
** Made by alexandre scipion
** Login   <scipio_a@epitech.net>
** 
** Started on  Wed May  6 18:36:48 2015 alexandre scipion
** Last update Sun May 17 21:49:20 2015 alexandre scipion
*/

#ifndef			STRACE_H_
# define		STRACE_H_

# define		_POSIX_SOURCE
# define		_BSD_SOURCE

# include		<sys/ptrace.h>
# include		<sys/types.h>
# include		<sys/wait.h>
# include		<signal.h>
# include		<sys/time.h>
# include		<sys/resource.h>
# include		<unistd.h>
# include		<sys/user.h>
# include		<sys/reg.h>
# include		<sys/syscall.h>
# include		<stdio.h>
# include		<stdlib.h>
# include		<string.h>
# include		<errno.h>

typedef	struct		s_param
{
  struct s_param	*next;
  char			type[20];
}			t_param;

typedef union		u_lchar
{
  long			val;
  unsigned char		tab[sizeof(long) / sizeof(char)];
}			t_lchar;

typedef			long long unsigned int
			t_llui;

int			nbr_args(char *syscall, struct user_regs_struct regs,
				 pid_t child);
void			print_arg(struct user_regs_struct regs, int nbr,
				  int type, pid_t child, char *name);
char*			get_name(FILE* fid, char *name, int syscall);
FILE*			open_file();
int			is_syscall(pid_t, struct user_regs_struct *);
int			my_exit(FILE *fid, int error, int exit_status);
int			return_type(char *ctype);
t_llui			return_reg(struct user_regs_struct regs, int nbr);
void			print_string(t_llui reg, pid_t child);
void			explicit_null(char *name, t_llui reg);
int			father(pid_t child);
int			trace_pid(pid_t pid);
void			begin_print(FILE *fid, char *name,
				    struct user_regs_struct regs, pid_t child);
void			end_print(struct user_regs_struct regs);
char			*find_file(char *name, char **env);

#endif	/* !STRACE_H_ */

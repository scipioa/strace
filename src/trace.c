/*
** trace.c for strace in /home/scipio_a/rendu/strace
** 
** Made by alexandre scipion
** Login   <scipio_a@epitech.net>
** 
** Started on  Sat May  2 10:45:31 2015 alexandre scipion
** Last update Thu May 21 14:09:14 2015 alexandre scipion
*/

#include "strace.h"

int		is_syscall(pid_t child,   struct user_regs_struct *regs)
{
  t_lchar	opcode;
  unsigned char	syscall[2];
  unsigned char	int80[2];
  unsigned char	sysenter[2];

  syscall[0] = 0x0f;
  syscall[1] = 0x05;
  int80[0] = 0xcd;
  int80[1] = 0x80;
  sysenter[0] = 0x0f;
  sysenter[1] = 0x34;
  opcode.val = ptrace(PTRACE_PEEKTEXT, child, regs->rip, NULL);
  if ((opcode.tab[0] == syscall[0] && opcode.tab[1] == syscall[1])
      || (opcode.tab[0] == int80[0] && opcode.tab[1] == int80[1])
      || (opcode.tab[0] == sysenter[0] && opcode.tab[1] == sysenter[1]))
    return (1);
  return (0);
}

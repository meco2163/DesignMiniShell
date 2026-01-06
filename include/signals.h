/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 05:12:14 by mekaplan          #+#    #+#             */
/*   Updated: 2026/01/03 05:16:49 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# define _POSIX_C_SOURCE 200809L
# include <signal.h>

# ifndef SA_RESTART
#  define SA_RESTART 0
# endif

typedef enum e_sigmode
{
	SM_PROMPT,
	SM_CHILD,
	SM_HEREDOC
}	t_sigmode;

extern volatile sig_atomic_t	g_sig;
extern t_sigmode				g_sigmode;

void	sig_set_mode(t_sigmode mode);
void	sig_set_sa(int sig, void (*fn)(int), int flags);

void	sig_on_int(int signo);
void	sig_on_quit(int signo);

void	sig_init_prompt(void);
void	sig_init_wait_parent(void);
void	sig_init_child(void);
void	sig_init_heredoc(void);

#endif

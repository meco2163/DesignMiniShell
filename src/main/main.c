/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 05:10:41 by mekaplan          #+#    #+#             */
/*   Updated: 2026/01/03 05:21:15 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "signals.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <stdlib.h>

static int	main_loop(t_shell *sh)
{
	char	*line;

	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
		{
			write(1, "exit\n", 5);
			break ;
		}
		if (g_sig == SIGINT)
		{
			sh_set_status(sh, 130);
			g_sig = 0;
		}
		if (*line)
			add_history(line);
		run_once(sh, line);
		free(line);
	}
	return (sh_status(sh));
}

int	main(int ac, char **av)
{
	t_shell	sh;

	sh.last_status = 0;
	sig_init_prompt();
	if (ac == 1)
		return (main_loop(&sh));
	if (ac == 2)
		return (run_once(&sh, av[1]));
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_once.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 05:10:47 by mekaplan          #+#    #+#             */
/*   Updated: 2026/01/07 01:59:56 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "heredoc.h"
#include <stdio.h>

int	run_once(t_shell *sh, const char *line)
{
	t_tok	*toks;
	t_cmd	*cmds;

	toks = tokenize(line);
	if (!toks)
		return (sh_set_status(sh, 1), fprintf(stderr, "*run_once: tokenize failed*\n"), 1);
	if (!syntax_check(toks))
	{
		tok_clear(&toks);
		return (sh_set_status(sh, 2), fprintf(stderr, "*run_once: syntax_check failed*\n"), 2);
	}
	cmds = parse_tokens(toks);
	tok_clear(&toks);
	if (!cmds)
		return (sh_set_status(sh, 3), fprintf(stderr, "*run_once: parse_tokens failed*\n"), 3);
	if (prepare_heredocs(sh, cmds) != 0)
	{
		cmd_clear(&cmds);
		return (fprintf(stderr, "*run_once: prepare_heredocs failed*\n"), sh_status(sh));
	}
	cmd_clear(&cmds);
	sh_set_status(sh, 0);
	return (0);
}

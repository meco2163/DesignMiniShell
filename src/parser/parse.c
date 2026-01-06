/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekaplan <mekaplan@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 05:11:01 by mekaplan          #+#    #+#             */
/*   Updated: 2026/01/03 05:36:45 by mekaplan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdlib.h>
#include "utils.h"
#include <stdio.h>

static int	count_argv(t_tok *t)
{
	int	n;

	n = 0;
	while (t && t->type != T_EOF && t->type != T_PIPE)
	{
		if (is_redir(t->type))
		{
			t = t->next;
			if (t)
				t = t->next;
			continue ;
		}
		if (t->type == T_WORD)
			n++;
		t = t->next;
	}
	return (n);
}

static void	fill_argv_cleanup(char **argv, int count)
{
	int	j;

	j = 0;
	while (j < count)
	{
		free(argv[j]);
		j++;
	}
}

static int	fill_argv(t_cmd *c, t_tok *t)
{
	int	i;

	i = 0;
	while (t && t->type != T_EOF && t->type != T_PIPE)
	{
		if (is_redir(t->type))
		{
			t = t->next;
			if (t)
				t = t->next;
			continue ;
		}
		if (t->type == T_WORD)
		{
			c->argv[i] = ft_strdup(t->val);
			if (!c->argv[i])
				return (fill_argv_cleanup(c->argv, i), fprintf(stderr, "*fill_argv: ft_strdup failed at index %d*\n", i), 0);
			i++;
		}
		t = t->next;
	}
	c->argv[i] = NULL;
	return (1);
}

static t_tok	*parse_redirs(t_cmd *cur, t_tok *lst)
{
	while (lst && lst->type != T_EOF && lst->type != T_PIPE)
	{
		if (is_redir(lst->type))
		{
			if (!parse_redir(cur, &lst))
				return (fprintf(stderr, "*parse_redirs: parse_redir failed*\n"), NULL);
		}
		else
			lst = lst->next;
	}
	return (lst);
}

t_cmd	*parse_tokens(t_tok *lst)
{
	t_cmd	*cmds;
	t_cmd	*cur;
	int		n;

	cmds = NULL;
	while (lst && lst->type != T_EOF)
	{
		cur = cmd_new();
		if (!cur)
			return (cmd_clear(&cmds), fprintf(stderr, "*parse_tokens: cmd_new failed*\n"), NULL);
		cmd_add_back(&cmds, cur);
		n = count_argv(lst);
		cur->argv = malloc(sizeof(char *) * (n + 1));
		if (!cur->argv)
			return (cmd_clear(&cmds), fprintf(stderr, "*parse_tokens: argv malloc failed*\n"), NULL);
		if (!fill_argv(cur, lst))
			return (cmd_clear(&cmds), fprintf(stderr, "*parse_tokens: fill_argv failed*\n"), NULL);
		lst = parse_redirs(cur, lst);
		if (!lst)
			return (cmd_clear(&cmds), fprintf(stderr, "*parse_tokens: parse_redirs failed*\n"), NULL);
		if (lst && lst->type == T_PIPE)
			lst = lst->next;
	}
	return (cmds);
}

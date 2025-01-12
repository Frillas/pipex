/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <aroullea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 14:01:04 by aroullea          #+#    #+#             */
/*   Updated: 2025/01/12 13:31:37 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

static int	count_args(char const *s, int count)
{
	t_bool	in_word;
	t_bool	in_quotes;
	t_bool	in_single_quotes;
	int		i;

	in_word = FALSE;
	in_quotes = FALSE;
	in_single_quotes = FALSE;
	i = 0;
	while (s[i])
	{
		if ((s[i] == '"') && (s[i - 1] != '\\'))
			in_quotes = !in_quotes;
		else if ((s[i] == '\'') && (!in_quotes))
			in_single_quotes = !in_single_quotes;
		else if ((!in_quotes) && (!in_single_quotes) && (s[i] == ' '))
			in_word = FALSE;
		else if (!in_word)
		{
			in_word = TRUE;
			count++;
		}
		i++;
	}
	return (count);
}

static int	wordlen(char const *s)
{
	int		len;
	t_bool	in_quotes;
	t_bool	in_single_quotes;

	len = 0;
	in_quotes = FALSE;
	in_single_quotes = FALSE;
	while (s[len])
	{
		if ((s[len] == '"') && (s[len - 1] != '\\'))
			in_quotes = !in_quotes;
		else if ((s[len] == '\'') && (!in_quotes))
			in_single_quotes = !in_single_quotes;
		else if ((!in_quotes) && (!in_single_quotes) && (s[len] == ' '))
			break ;
		len++;
	}
	return (len);
}

static void	copyword(char *dest, char const *s, int len, int i)
{
	int		j;
	t_bool	in_quotes;
	t_bool	single;

	j = 0;
	in_quotes = FALSE;
	single = FALSE;
	while (i < len)
	{
		if ((s[i] == '"' && (s[i - 1] != '\\') && !single)
			|| (s[i] == '\'' && !in_quotes))
		{
			if (s[i] == '"')
				in_quotes = !in_quotes;
			else
				single = !single;
			i++;
		}
		else if (s[i] == '\\' && s[i + 1] == '"')
			i++;
		else
			dest[j++] = s[i++];
	}
	dest[j] = '\0';
}

static char	**sort(char const *s, char **str, int nb_args)
{
	int	len;
	int	k;

	k = 0;
	while (k < nb_args)
	{
		while (*s == ' ')
			s++;
		len = wordlen(s);
		str[k] = (char *) malloc(sizeof(char) * (len + 1));
		if (str[k] == NULL)
		{
			while (k >= 0)
				free (str[k--]);
			free (str);
			return (NULL);
		}
		copyword(str[k], s, len, 0);
		k++;
		s += len;
	}
	str[nb_args] = NULL;
	return (str);
}

char	**arg_split(char const *s)
{
	int		nb_args;
	char	**str;

	if (!s)
		return (NULL);
	nb_args = count_args(s, 0);
	str = (char **) malloc(sizeof(char *) * (nb_args + 1));
	if (str == NULL)
		return (NULL);
	str = sort(s, str, nb_args);
	return (str);
}

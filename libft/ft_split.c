/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dajesus- <dajesus-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 15:17:08 by dajesus-          #+#    #+#             */
/*   Updated: 2024/12/17 21:11:41 by dajesus-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_tokens(char const *s, char sep)
{
	size_t		i;
	size_t		tokens;

	i = 0;
	tokens = 0;
	while (s[i])
	{
		if (s[i] != sep && (s[i + 1] == sep || s[i + 1] == '\0'))
			tokens++;
		i++;
	}
	return (tokens);
}

static char	*get_word(const char *s, size_t *index, char sep)
{
	size_t		i;
	size_t		len;
	size_t		start;
	char		*word;

	len = 0;
	while (s[*index] == sep)
		(*index)++;
	start = *index;
	while (s[*index] != sep && s[*index])
	{
		len++;
		(*index)++;
	}
	word = malloc(len + 1);
	if (!word)
		return (NULL);
	i = 0;
	while (i < len)
	{
		word[i] = s[start + i];
		i++;
	}
	word[len] = '\0';
	return (word);
}

static char	**free_tokens(char **tokens, size_t count)
{
	size_t		i;

	i = 0;
	while (i < count)
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	size_t		i;
	size_t		j;
	char		**token_vector;

	if (!s)
		return (NULL);
	token_vector = malloc((count_tokens(s, c) + 1) * sizeof(char *));
	if (token_vector == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] == '\0')
			break ;
		token_vector[j] = get_word(s, &i, c);
		if (!token_vector[j])
			return (free_tokens(token_vector, j));
		j++;
	}
	token_vector[j] = NULL;
	return (token_vector);
}

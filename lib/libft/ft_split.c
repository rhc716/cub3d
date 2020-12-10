/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hroh <hroh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 11:06:53 by hroh              #+#    #+#             */
/*   Updated: 2020/10/19 15:40:49 by hroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char			**ft_all_free(char **re)
{
	unsigned int	i;

	i = 0;
	while (re[i])
	{
		free(re[i]);
		i++;
	}
	free(re);
	return (NULL);
}

static unsigned int	ft_get_wd_cnt(char const *s, char c)
{
	unsigned int	i;
	unsigned int	wd_cnt;

	if (!s[0])
		return (0);
	i = 0;
	wd_cnt = 0;
	while (s[i] && s[i] == c)
		i++;
	while (s[i])
	{
		if (s[i] == c)
		{
			wd_cnt++;
			while (s[i] && s[i] == c)
				i++;
			continue ;
		}
		i++;
	}
	if (s[i - 1] != c)
		wd_cnt++;
	return (wd_cnt);
}

static void			ft_get_next_wd(char **next_wd, unsigned int *next_wd_len,
					char c)
{
	unsigned int i;

	*next_wd += *next_wd_len;
	*next_wd_len = 0;
	i = 0;
	while (**next_wd && **next_wd == c)
		(*next_wd)++;
	while ((*next_wd)[i])
	{
		if ((*next_wd)[i] == c)
			return ;
		(*next_wd_len)++;
		i++;
	}
}

char				**ft_split(char const *s, char c)
{
	char			**re;
	char			*next_wd;
	unsigned int	next_wd_len;
	unsigned int	wd_cnt;
	unsigned int	i;

	if (!s)
		return (NULL);
	wd_cnt = ft_get_wd_cnt(s, c);
	if (!(re = (char **)malloc(sizeof(char *) * (wd_cnt + 1))))
		return (NULL);
	i = 0;
	next_wd = (char *)s;
	next_wd_len = 0;
	while (i < wd_cnt)
	{
		ft_get_next_wd(&next_wd, &next_wd_len, c);
		if (!(re[i] = (char *)malloc(sizeof(char) * (next_wd_len + 1))))
			return (ft_all_free(re));
		ft_strlcpy(re[i], next_wd, next_wd_len + 1);
		i++;
	}
	re[i] = NULL;
	return (re);
}

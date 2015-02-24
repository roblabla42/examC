/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: exam <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/29 14:05:02 by exam              #+#    #+#             */
/*   Updated: 2015/01/29 15:39:07 by exam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

size_t	ft_max(size_t s1, size_t s2)
{
	return (s1 > s2 ? s1 : s2);
}

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	while (*s++ != '\0')
		i++;
	return (i);
}

char	*ft_strdup(char *s)
{
	char	*ret;
	size_t	i;

	ret = malloc(ft_strlen(s) + 1);
	i = 0;
	while (s[i])
	{
		ret[i] = s[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

void	*ft_memalloc(size_t size)
{
	char	*mem;
	size_t	i;

	mem = (char*)malloc(size);
	if (mem == NULL)
		return (NULL);
	i = 0;
	while (i < size)
		mem[i++] = 0;
	return (mem);
}

char	*ft_mult(char *s1, size_t s1_len, char mult_by, unsigned pad_zero)
{
	int		retenue;
	int		tmp;
	char	*ret;
	ssize_t	i;

	ret = ft_memalloc(s1_len + 2 + pad_zero);
	i = s1_len - 1;
	retenue = 0;
	while (i >= 0)
	{
		tmp = (s1[i] - '0') * mult_by + retenue;
		ret[i + 1] = (tmp % 10) + '0';
		retenue = tmp / 10;
		i--;
	}
	while (pad_zero > 0)
		ret[s1_len + pad_zero--] = '0';
	ret[0] = retenue + '0';
	return (ret);
}

void	ft_putstr(char *s, int neg)
{
	while (*s == '0')
		s++;
	if (*s == '\0')
		write(1, "0", 1);
	else
	{
		if (neg)
			write(1, "-", 1);
		while (*s)
			write(1, s++, 1);
	}
}

char	*sum_str(char *s1, char *s2)
{
	int		retenue;
	int		tmp;
	char	*s1_end;
	char	*s2_end;
	char	*ret;
	size_t	i;

	s1_end = s1;
	while (*s1_end)
		s1_end++;
	s2_end = s2;
	while (*s2_end)
		s2_end++;
	ret = ft_memalloc(ft_max(s2_end-- - s2, s1_end-- - s1) + 2);
	i = ft_max(s2_end - s2, s1_end - s1) + 1;
	retenue = 0;
	while (s1_end >= s1 && s2_end >= s2)
	{
		tmp = (*s1_end-- - '0') + (*s2_end-- - '0') + retenue;
		ret[i] = (tmp % 10) + '0';
		retenue = tmp / 10;
		i--;
	}
	if (s1_end < s1)
	{
		s1_end = s2_end;
		s1 = s2;
	}
	while (s1_end >= s1)
	{
		tmp = (*s1_end-- - '0') + retenue;
		ret[i] = (tmp % 10) + '0';
		retenue = tmp / 10;
		i--;
	}
	ret[0] = retenue + '0';
	return (ret);
}

void	print_sum_tab_strs(char **tab_strs, size_t tab_len, int neg)
{
	char	*res;
	char	*tmp;
	size_t	i;

	res = ft_strdup(tab_strs[0]);
	i = 1;
	while (i < tab_len)
	{
		tmp = res;
		res = sum_str(tmp, tab_strs[i++]);
		free(tmp);
	}
	ft_putstr(res, neg);
	free(res);
}

void	ft_print_multiply(char *s1, size_t s1_len, char *s2, size_t s2_len, int neg)
{
	char	**tab_strs;
	size_t	i;

	tab_strs = (char**)malloc(sizeof(char*) * s2_len);
	i = 0;
	while (i < s2_len)
	{
		tab_strs[i] = ft_mult(s1, s1_len, s2[s2_len - 1 - i] - '0', i);
		i++;
	}
	print_sum_tab_strs(tab_strs, s2_len, neg);
	i = 0;
	while (i < s2_len)
		free(tab_strs[i++]);
	free(tab_strs);
}

int		main(int argc, char **argv)
{
	char	*s1;
	size_t	s1_len;
	char	*s2;
	size_t	s2_len;
	int		neg;

	(void)argc;
	s1 = argv[1];
	s2 = argv[2];
	neg = 0;
	if ((*s1 == '-' && *s2 != '-') || (*s1 != '-' && *s2 == '-'))
		neg = 1;
	if (*s1 == '-')
		s1++;
	if (*s2 == '-')
		s2++;
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	if (s1_len < s2_len)
		ft_print_multiply(s2, s2_len, s1, s1_len, neg);
	else
		ft_print_multiply(s1, s1_len, s2, s2_len, neg);
	write(1, "\n", 1);
	return (0);
}

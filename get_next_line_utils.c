/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmlee <junmlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 20:51:02 by junmlee           #+#    #+#             */
/*   Updated: 2023/11/06 22:37:24 by junmlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*free_setnull(char **ptr)
{
	void	*temp;

	temp = *ptr;
	if (*ptr != NULL)
		*ptr = NULL;
	free(temp);
	return (NULL);
}

size_t	gnl_strlen(const char *str)
{
	size_t	i;

	if (str == NULL)
		return (-1);
	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

size_t	gnl_strlcpy(char *dest, const char *src, size_t size)
{
	unsigned int	i;
	unsigned int	src_size;

	src_size = gnl_strlen(src);
	if (size == 0)
		return (src_size);
	i = 0;
	while (*(src + i) != '\0' && (i + 1) < size)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (src_size);
}

char	*gnl_append(char *s1, char *s2)
{
	unsigned int	s1_len;
	unsigned int	s2_len;
	char			*arr;

	s2_len = gnl_strlen(s2);
	if (s1 == NULL)
	{
		free_setnull(&(s1));
		return (gnl_strndup(s2, s2_len));
	}
	s1_len = gnl_strlen(s1);
	arr = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (arr == NULL)
	{
		free_setnull(&(s1));
		return (NULL);
	}
	gnl_strlcpy(arr, s1, s1_len + 1);
	gnl_strlcpy(arr + s1_len, s2, s2_len + 1);
	arr[s1_len + s2_len] = '\0';
	free_setnull(&(s1));
	return (arr);
}

char	*gnl_strndup(char *s1, size_t len)
{
	size_t	i;
	char	*arr;

	if (s1 == NULL || len == 0)
		return (NULL);
	arr = (char *)malloc(sizeof(char) * (len + 1));
	if (arr == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		arr[i] = s1[i];
		i++;
	}
	arr[i] = '\0';
	return (arr);
}

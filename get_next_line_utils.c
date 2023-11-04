/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmlee <junmlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 20:51:02 by junmlee           #+#    #+#             */
/*   Updated: 2023/11/05 05:48:05 by junmlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	g_str(char *ret, t_buf *buf, ssize_t len)
{
	ssize_t	dst_size;
	ssize_t	i;

	dst_size = 0;
	i = 0;
	if (buf->data != NULL)
	{
		while (buf->data[dst_size] && i < len)
		{
			ret[dst_size] = buf->data[dst_size];
			dst_size++;
		}
	}
	if (buf->new != NULL)
	{
		while (buf->new[i] && (i + dst_size) < len)
		{
			ret[i + dst_size] = buf->new[i];
			i++;
		}
	}
	ret[i + dst_size] = '\0';
	return ;
}

void	gnl_strcat(t_buf *buf, ssize_t read_byte)
{
	char	*replace;
	char	*temp;

	temp = (buf)->data;
	replace = (char *)malloc((buf)->data_len + read_byte + 1);
	if (replace == NULL)
	{
		(buf)->error = 1;
		return ;
	}
	g_str(replace, buf, buf->data_len + read_byte);
	(buf)->data = replace;
	if (temp != NULL)
		free(temp);
}

char	*g_strdup(char *s1, ssize_t start, ssize_t idx)
{
	ssize_t	i;
	char	*arr;

	arr = (char *)malloc(sizeof(char) * (idx - start + 1));
	if (arr == NULL)
		return (NULL);
	i = start;
	while (i < idx)
	{
		arr[i - start] = s1[i];
		i++;
	}
	arr[i - start] = '\0';
	return (arr);
}

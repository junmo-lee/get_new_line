/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmlee <junmlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 20:50:49 by junmlee           #+#    #+#             */
/*   Updated: 2023/11/06 22:37:01 by junmlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	update_buf(t_buf *buf)
{
	ssize_t	i;
	int		once;

	buf->n_idx = -1;
	if (buf->data == NULL)
	{
		buf->len_data = 0;
		buf->end_flag = 1;
	}
	else
	{
		once = 1;
		i = 0;
		while (buf->data[i] != '\0')
		{
			if (buf->data[i] == '\n' && once)
			{
				buf->n_idx = i;
				once = 0;
			}
			i++;
		}
		buf->len_data = i;
		buf->end_flag = 0;
	}
}

int	read_line(t_buf *buf, char *buffer, int fd)
{
	while (1)
	{
		update_buf(buf);
		if (buf->n_idx >= 0)
			return (0);
		buf->ret_read = read(fd, buffer, BUFFER_SIZE);
		if (buf->ret_read == -1)
			return (3);
		if (buf->ret_read == 0)
			return (2);
		buffer[buf->ret_read] = '\0';
		buf->data = gnl_append(buf->data, buffer);
		if (buf->data == NULL)
			return (1);
	}
	return (0);
}

char	*get_next_line(int fd)
{
	static t_buf	arr[OPEN_MAX];
	char			*buffer;
	char			*ret;

	if (0 > fd || fd > OPEN_MAX || BUFFER_SIZE < 1)
		return (NULL);
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buffer == NULL)
	{
		free_setnull(&(arr[fd].data));
		return (NULL);
	}
	arr[fd].end_flag = read_line(&(arr[fd]), buffer, fd);
	free_setnull(&(buffer));
	ret = make_ret(&(arr[fd]));
	if (ret == NULL)
	{
		free_setnull(&(arr[fd].data));
		free_setnull(&ret);
	}
	return (ret);
}

char	*make_ret(t_buf *buf)
{
	char	*temp;
	char	*ret;
	ssize_t	rest_len;

	ret = NULL;
	if (buf->end_flag == 1)
		free_setnull(&(buf->data));
	else if (buf->end_flag == 2)
	{
		ret = gnl_strndup(buf->data, buf->len_data);
		free_setnull(&(buf->data));
	}
	else if (buf->end_flag == 3)
		free_setnull(&(buf->data));
	else
	{
		temp = buf->data;
		ret = gnl_strndup(temp, buf->n_idx + 1);
		rest_len = buf->len_data - buf->n_idx;
		buf->data = gnl_strndup(temp + buf->n_idx + 1, rest_len);
		free_setnull(&temp);
	}
	return (ret);
}

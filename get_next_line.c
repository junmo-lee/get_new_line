/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmlee <junmlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 20:50:49 by junmlee           #+#    #+#             */
/*   Updated: 2023/11/05 05:49:27 by junmlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	set_pos(t_buf *buf, ssize_t read_byte, ssize_t newline_index)
{
	if (newline_index == 0)
	{
		buf->ret_end = read_byte;
		buf->data_start = -1;
	}
	else if (buf->new == NULL)
	{
		buf->ret_end = buf->data_len;
		buf->data_start = -1;
	}
	else
	{
		buf->ret_end = newline_index;
		if (buf->ret_end == read_byte)
			buf->data_start = -1;
		else
			buf->data_start = buf->ret_end + 1;
	}
}

char	*free_null(t_buf *buf)
{
	t_buf	*temp;

	temp = buf;
	return (NULL);
}

ssize_t	find_newline_index(char *arr, char c)
{
	ssize_t	i;

	if (arr == NULL)
		return (0);
	i = 0;
	while (1)
	{
		if (arr[i] == c)
			return (i);
		if (arr[i] == '\0')
			return (0);
		i++;
	}
}

char	*get_next_line(int fd)
{
	static t_buf	buff[OPEN_MAX];
	ssize_t			newline_index;
	ssize_t			read_byte;

	if (0 > fd || fd > OPEN_MAX || BUFFER_SIZE < 1)
		return (free_null(buff));
	read_byte = BUFFER_SIZE;
	newline_index = find_newline_index(buff[fd].data, '\n');
	while (newline_index == 0 && read_byte == BUFFER_SIZE)
	{
		buff[fd].new = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (buff[fd].new == NULL)
			return (free_null(buff));
		read_byte = read(fd, buff[fd].new, BUFFER_SIZE);
		(buff[fd].new)[read_byte] = '\0';
		if (read_byte < 0)
			return (free_null(buff));
		newline_index = find_newline_index(buff[fd].new, '\n');
		if (newline_index == 0)
			gnl_strcat(&(buff[fd]), read_byte);
		if (buff[fd].error == 1)
			return (free_null(buff));
		buff[fd].data_len += read_byte;
	}
	return (gnl_retup(&buff[fd], read_byte, newline_index));
}

char	*gnl_retup(t_buf *buf, ssize_t read_byte, ssize_t newline_index)
{
	char	*ret;

	buf->data_len = find_newline_index(buf->data, '\0');
	set_pos(buf, read_byte, newline_index);
	ret = (char *)malloc(buf->data_len + buf->ret_end + 1);
	if (ret == NULL)
		return (NULL);
	g_str(ret, buf, buf->data_len + buf->ret_end + 1);
	free(buf->data);
	if (buf->data_start < 0)
		buf->data = NULL;
	else
		buf->data = g_strdup(buf->new, buf->data_start, read_byte);
	free(buf->new);
	buf->new = NULL;
	return (ret);
}

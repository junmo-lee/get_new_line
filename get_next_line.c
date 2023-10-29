/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmlee <junmlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 20:50:49 by junmlee           #+#    #+#             */
/*   Updated: 2023/10/29 22:28:45 by junmlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <string.h>

char	*get_next_line(int fd)
{
	char		*buf;
	static char	*backup;
	int			eof_flag;
	char		*newline;
	ssize_t		read_byte;

	if (0 > fd || fd > OPEN_MAX || BUFFER_SIZE < 1)
		return (NULL);
	buf = (char *)malloc(sizeof(char) *(BUFFER_SIZE + 1));
	if (buf == NULL)
		return (NULL);
	eof_flag = 1;
	while (eof_flag)
	{
		read_byte = read(fd, buf, BUFFER_SIZE);
		if (read_byte <= 0)
			eof_flag = 0;
		buf[read_byte] = '\0';
		if (backup == NULL)
			backup = strdup(buf);
		else
			strcat(backup, buf);
		newline = strchr(backup, '\n');
	}
}

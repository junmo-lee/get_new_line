/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmlee <junmlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 21:01:15 by junmlee           #+#    #+#             */
/*   Updated: 2023/11/06 23:09:16 by junmlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

// # define BUFFER_SIZE 10

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

typedef struct s_buf{
	char	*data;
	ssize_t	n_idx;
	ssize_t	len_data;
	ssize_t	ret_read;
	int		end_flag;
}	t_buf;

void	*free_setnull(char **ptr);
void	update_buf(t_buf *buf);
ssize_t	gnl_strlen(const char *str);
ssize_t	gnl_strlcpy(char *dest, const char *src, ssize_t size, ssize_t src_size);
char	*gnl_append(char *s1, char *s2, t_buf *buf);
char	*gnl_strndup(char *s1, size_t len);
int		read_line(t_buf *buf, char *buffer, int fd);
char	*make_ret(t_buf *buf);
char	*get_next_line(int fd);

#endif
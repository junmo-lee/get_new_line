/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmlee <junmlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 21:01:15 by junmlee           #+#    #+#             */
/*   Updated: 2023/11/06 20:12:07 by junmlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFFER_SIZE 10

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

void	update_buf(t_buf *buf);
size_t	ft_strlen(const char *str);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
char	*gnl_append(char const *s1, char const *s2);
char	*g_strndup(const char *s1, size_t len);
int		read_line(t_buf *buf, char *buffer, int fd);
char	*make_ret(t_buf *buf);
char	*get_next_line(int fd);

#endif
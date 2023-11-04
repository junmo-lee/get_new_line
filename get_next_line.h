/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmlee <junmlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 21:01:15 by junmlee           #+#    #+#             */
/*   Updated: 2023/11/05 05:50:48 by junmlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFFER_SIZE 5
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

typedef struct s_buf{
	char	*data;
	char	*new;
	ssize_t	data_len;
	ssize_t	ret_end;
	ssize_t	data_start;
	int		error;
}	t_buf;

char	*free_null(t_buf *buf);
void	gnl_strcat(t_buf *buf, ssize_t read_byte);
void	g_str(char *arr, t_buf *buf, ssize_t len);
char	*g_strdup(char *s1, ssize_t start, ssize_t end);
void	set_pos(t_buf *buf, ssize_t read_byte, ssize_t newline_index);
char	*gnl_retup(t_buf *buf, ssize_t read_byte, ssize_t newline_index);
ssize_t	find_newline_index(char *arr, char a);
char	*get_next_line(int fd);

#endif
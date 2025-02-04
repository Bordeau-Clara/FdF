/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbordeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 18:10:42 by cbordeau          #+#    #+#             */
/*   Updated: 2024/11/26 10:49:57 by cbordeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 21
# endif

char	*get_next_line(int fd);
char	*ft_empty_buf(char *buffer, char *line);
void	ft_strcpy(char *temp, char *line, char *buffer);
char	*ft_strdup_gnl(char *s);
int		ft_is_line(char *line);
void	ft_empty_buf2(char *buffer);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caliaga- <caliaga-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 14:41:24 by caliaga-          #+#    #+#             */
/*   Updated: 2024/04/04 16:16:11 by caliaga-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <string.h>
# include <errno.h>
# include <fcntl.h>
#define READ    0
#define WRITE   1

char	**matrix_free(char **arr, size_t row);
char	**error_matrix_free(char **arr, size_t row);
void	open_err_ctl(int exe, char *url);
void	command_err_ctl(int exe, const char *url);
void	command_err_env(int exe, const char *url);
void	err_ctl(int exe, char *msg);
size_t	ft_cuts(const char *str, int c);
size_t	ft_reels(const char *str, char c, size_t *reel);
void	ft_fill(char *arr, const char *str, size_t letters, size_t *reel);
char	**split_reel(const char *str, char c, size_t reel);
char	*select_env(char **env);
size_t	ft_strlen(const char *str);
char	*ft_strjoin_slash(const char *s1, const char *s2);
char	*check_argv(const char *argv);
char	*filepath_generator(const char *argv, char **env);
int		fd_openfile(char *url, char opt);
void	exec(char *argv, char **env);
void	child(int *fd_pipe, char **argv, char **env);
void	parent(int *fd_pipe, char **argv, char **env);

#endif

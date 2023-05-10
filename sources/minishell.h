/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdidesmartin <mehdidesmartin@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 11:23:19 by jmoutous          #+#    #+#             */
/*   Updated: 2023/05/09 14:11:22 by mehdidesmar      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define _GNU_SOURCE
# include "libft/sources/libft.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <termios.h>
# include <sys/ioctl.h>

// < = 1
// << = 2
// > = 3
// >> = 6

// input[0] : 0 = < ; 1 = <<
// input[1] : file or limiter
// output[0] : 0 = > ; 1 = >>
// output[1] : file if output[0] == 0

typedef struct s_pipeline
{
	char			**command;
	char			**input;
	char			**output;
}					t_pipeline;

typedef struct s_envp
{
	char			*variable;
	char			*value;
	struct s_envp	*next;
}				t_envp;

typedef struct s_data
{
	t_list	*cmd;
	t_envp	*envp;
	char	**envp_tab;
	int		**pipes;
	int		here_doc_fd[2];
	int		nb_cmd;
	int		exit_code;
}				t_data;

void		ft_data_init(t_data *data);
void		ft_close_fds(t_data *data, int *here_doc_fd);
void		ft_error(t_data *data, char *s);
void		ft_perror(t_data *data, char *str, int code);
void		ft_quit(t_data *data, int code);
void		ft_free_tab(char **tab);
void		ft_rfree_tab(char **tab, int i);
int			ft_is_c_in(char *str, char c);
void		ft_free_envptab(t_data *data);
void		ft_free_envplst(t_data *data);
void		ft_putstr3_fd(char *s1, char *s2, char *s3);
void		ft_print_tabtab(char **tab);

void		ft_envp(t_data *data);
void		ft_creat_envp(t_data *data);
void		ft_check_envp(t_data *data);
void		ft_check_pwd(t_data *data);
int			ft_check_exportvar(char *variable);
void		ft_print_env(t_data *data);
void		ft_export(t_data *data, char **command);
void		ft_unset(t_data *data, char **command);
void		ft_envadd_back(t_envp **lst, t_envp *new);
t_envp		*ft_envlast(t_envp *lst);
void		ft_print_export(t_data *data);
char		**ft_lst_to_tabtab(t_data *data, t_envp *envp);
char		*ft_strjoin3(char const *s1, char const *s2, char const *s3);
char		**ft_split_var(t_data *data, char *var);
void		ft_update_envptab(t_data *data);
int			ft_inredic_count(char **tab);
int			ft_outredic_count(char **tab);
void		ft_input_heredoc(t_data *data, char *limiter, int last_redir);
char		**ft_redirection(t_data *data, int i);

void		ft_cmd(t_data *data);
void		ft_child(t_data *data, int **pipes, int i);
char		*ft_get_arg_path(t_data *data, char **command);
char		*ft_getenv(t_envp *envp, char *variable);
int			ft_builtin(t_data *data, char **command);
void		ft_builtin_cd(t_data *data, char **command);
void		ft_builtin_exit(t_data *data, char **command);
void		ft_builtin_slash(t_data *data, char *directory);
void		ft_builtin_echo(char **command);
void		ft_check_envarg(t_data *data, char **command);
void		get_rediction(t_data *data, int i);
void		ft_extract_outputredir(t_data *data, t_pipeline *pipe);
void		ft_extract_inputredir(t_data *data, t_pipeline *pipe);
void		ft_input_redirection(t_data *data, char **input);
void		ft_output_redirection(t_data *data, char **output);

//signal
void		signal_init(void (*handler)(int signum));
void		signal_handler(int signum);
void		signal_heredoc(int signum);

//parsing
int			parsing(t_data *data, char *readed);
void		expands(t_data *data, char **pipe_tab);
int			nb_pipes(char *input);
char		**create_tab(char **pipe_tab, char *input, int nb_pipe);
char		*trim_quotes(char *dest);
char		**split_tokens(char *s, char *charset);

//check_input
int			in_quotes(char *str, int index);
int			check_input(char *input, t_data *data);
void		print_error(char *error);
int			is_whitespace(char c);
int			check_chevrons(char *input);
char		*space_chevrons(char *pipe);
int			is_whitespace_or_end(char c);
int			check_pipes_n_and(char *input);
int			check_quotes(char *input);

//free
void		free_lst(t_list **cmd);
void		*free_tab(char **tab);

//s_access
void		*s_init(char **content, char **input, char **output);
t_pipeline	*s_read_cnt(t_list *cmd);
t_pipeline	*s_convert_content(void *content);

//expands
char		*expand_handler(t_data *data, char *pipe_tab, int *start);
char		*trim_from_to(char *pipe_tab, int *start, int end);
char		*trim_by_exitcode(char *value, char *pipe_tab, int *start, int end);
char		*trim_by(char *value, char *pipe_tab, int *start, int end);

#endif
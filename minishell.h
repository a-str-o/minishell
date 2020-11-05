#ifndef MINISHELL_H
# define MINISHELL_H

# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <stdio.h>
# include <pwd.h>
# include <grp.h>
# include "libft/libft.h"
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <string.h>
# include <sys/mman.h>
# include <errno.h>

int		ft_is_there(char *str, char c);
void    minishell(char *str,char **argv ,char **env);

#endif

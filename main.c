
#include "minishell.h"

int		main(int ac, char **av, char **env)
{
    char		buff[1];
    char *str;

    str = ft_strdup("\0");
    av = NULL;
    
    ac = 0;
    ft_putstr("$> ");
    while (read(1, buff, 1))
        {
            
            str = ft_strjoin(str,buff);
            if (ft_is_there(buff,'\n') == 1)
                {
                    minishell(str,av,env);
                    free(str);
                    str = ft_strdup("\0");
                    ft_putstr("$> ");
                }
        }
    env = NULL;
    return 0;
}

#include "./../minishell.h"

static int is_builtin(const char *cmd)
{
    static const char *builtins[] = {
        "cd", "echo", "pwd", "export",
        "unset", "env", "exit", NULL
    };
    int i;

    i = 0;
    while (builtins[i])
    {
        if (strcmp(cmd, builtins[i]) == 0)
            return (1);
        i++;
    }
    return (0);
}

int exec_builtin(char **cmd, t_mini *mini)
{
    int status;

    status = 127;
    if (!is_builtin(cmd[0]))
        return status;        
    if (strcmp(cmd[0], "cd") == 0)
        exec_cd(cmd, mini);
    else if (strcmp(cmd[0], "echo") == 0)
        exec_echo(cmd, mini);
    else if (strcmp(cmd[0], "pwd") == 0)
        exec_pwd(cmd);
    else if (strcmp(cmd[0], "export") == 0)
        exec_export(cmd, mini);
    else if (strcmp(cmd[0], "unset") == 0)
        exec_unset(cmd, mini);
    else if (strcmp(cmd[0], "env") == 0)
        exec_env(cmd, mini);
    else if (strcmp(cmd[0], "exit") == 0)
        exec_exit(cmd);
    return status;
}

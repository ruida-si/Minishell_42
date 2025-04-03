#include "./../minishell.h"

int exec_redirect(t_token *token)
{
    int status;
    (void)token;

    int fd = open(token->next->cmd, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    dup2(fd, STDOUT_FILENO);
    close(fd);
    status = 127;
    return status;
}
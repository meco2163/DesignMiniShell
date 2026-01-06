# Exec tarafı: waitpid sonucu → shell exit status

Executor (fork/exec/waitpid) yazılınca, `waitpid()`’den dönen `int status`
değeri shell’in `$?` (last_status) değerine **aşağıdaki kuralla** çevrilmeli.

## Kural (bash uyumlu)

```c
if (WIFEXITED(status))
    code = WEXITSTATUS(status);
else if (WIFSIGNALED(status))
    code = 128 + WTERMSIG(status);
else
    code = 1;

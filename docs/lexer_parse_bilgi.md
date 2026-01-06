Parser çıktım şu formatta:
t_cmd *cmds (pipeline listesi)

Her cmd:
- argv: char** (NULL terminated), argv stringleri ft_strdup ile kopya
- redirs: t_redir* (R_IN, R_OUT, R_APP, R_HDOC) + target stringi ft_strdup ile kopya
- next: sonraki pipe komutu

Sorumluluklar:
- Ben: tokenize + syntax_check + parse (argv/redir doldurma) + cmd_clear
- Sen: pipe/fork/execve + redir uygulama + exit status/wait

Not: Token listesi parser sonrası free edilebilir; argv/target token’a bağlı değil.
İş bitince cmd_clear(&cmds) çağıracağız.

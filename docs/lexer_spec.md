# Lexer Spec (minishell)

## Goal
Turn an input line into a linear token list that the parser can consume.
The lexer does NOT execute commands. It only produces tokens.

## Token Types
- T_WORD
- T_PIPE          |
- T_REDIR_IN      <
- T_REDIR_OUT     >
- T_REDIR_APPEND  >>
- T_HEREDOC       <<
- T_EOF

## Core Guarantees
1) Operators are always separate tokens, even if attached to words.
   - `ls|wc`   -> WORD("ls") PIPE WORD("wc")
   - `echo>a`  -> WORD("echo") REDIR_OUT WORD("a")

2) Whitespace (space/tab) separates tokens only when outside quotes.
   - `echo   hi` -> WORD("echo") WORD("hi")

3) Quotes are consumed by the lexer and do not appear in token values.
   - Single quotes `'...'` keep content literal (no special meaning inside).
   - Double quotes `"..."` keep content as text; `$` expansion is allowed later.
   - Unclosed quotes are a lexer error.

4) The token list always ends with T_EOF.

## What is a WORD?
A WORD is any non-empty sequence that is not an operator token,
built by reading characters while respecting quote state.

Examples:
- `ls` -> WORD("ls")
- `-la` -> WORD("-la")
- `"hello world"` -> WORD("hello world")
- `'a|b'` -> WORD("a|b")

## Operators
Recognize these as tokens:
- `|`  -> T_PIPE
- `<`  -> T_REDIR_IN
- `>`  -> T_REDIR_OUT
- `<<` -> T_HEREDOC
- `>>` -> T_REDIR_APPEND

Two-character operators (`<<`, `>>`) must be matched before one-character ones.

## Minimum Error Rules (lexer-level)
- Unclosed quote -> ERROR
- Unknown characters are treated as part of WORD (for now)
- Logical ops like `||` / `&&` are out of scope -> ERROR (reject)

## Examples (expected tokens)
1) `ls`
   -> WORD("ls") EOF

2) `echo "hello world"`
   -> WORD("echo") WORD("hello world") EOF

3) `echo '$USER'`
   -> WORD("echo") WORD("$USER") EOF

4) `ls|grep a`
   -> WORD("ls") PIPE WORD("grep") WORD("a") EOF

5) `cat < in.txt`
   -> WORD("cat") REDIR_IN WORD("in.txt") EOF

6) `echo hi > out.txt`
   -> WORD("echo") WORD("hi") REDIR_OUT WORD("out.txt") EOF

7) `cat file|grep a|wc -l`
   -> WORD("cat") WORD("file") PIPE WORD("grep") WORD("a") PIPE WORD("wc") WORD("-l") EOF

----
# Lexer Tanımı (minishell) — Türkçe

## Amaç
Kullanıcıdan alınan bir satırı, parser’ın tüketebileceği doğrusal bir token listesine dönüştürmek.
Lexer komut **çalıştırmaz**. Sadece token üretir.

## Token Türleri
- T_WORD
- T_PIPE          |
- T_REDIR_IN      <
- T_REDIR_OUT     >
- T_REDIR_APPEND  >>
- T_HEREDOC       <<
- T_EOF

## Temel Garantiler
1) Operatörler her zaman ayrı token olarak üretilir, kelimeye bitişik olsalar bile.
   - `ls|wc`   -> WORD("ls") PIPE WORD("wc")
   - `echo>a`  -> WORD("echo") REDIR_OUT WORD("a")

2) Boşluklar (space/tab) yalnızca **quote dışında** token ayırıcıdır.
   - `echo   hi` -> WORD("echo") WORD("hi")

3) Quote karakterleri lexer tarafından tüketilir ve token değerine girmez.
   - Tek tırnak `'...'` içeriği tamamen **literal** kabul eder.
   - Çift tırnak `"..."` içeriği metindir, `$` genişletmesi sonradan yapılabilir.
   - Kapanmayan quote lexer hatasıdır.

4) Token listesi her zaman `T_EOF` ile biter.

## WORD Nedir?
WORD, operatör olmayan ve boş olmayan her karakter dizisidir.
Quote durumuna göre okunarak oluşturulur.

Örnekler:
- `ls` -> WORD("ls")
- `-la` -> WORD("-la")
- `"hello world"` -> WORD("hello world")
- `'a|b'` -> WORD("a|b")

## Operatörler
Aşağıdakiler özel token olarak tanınır:
- `|`  -> T_PIPE
- `<`  -> T_REDIR_IN
- `>`  -> T_REDIR_OUT
- `<<` -> T_HEREDOC
- `>>` -> T_REDIR_APPEND

İki karakterli operatörler (`<<`, `>>`) tek karakterlilerden önce kontrol edilir.

## Minimum Hata Kuralları (lexer seviyesi)
- Kapanmayan quote -> ERROR
- Bilinmeyen karakterler şimdilik WORD parçası sayılır
- `||`, `&&` gibi mantıksal operatörler kapsam dışıdır -> ERROR

## Örnekler (beklenen tokenlar)
1) `ls`
   -> WORD("ls") EOF

2) `echo "hello world"`
   -> WORD("echo") WORD("hello world") EOF

3) `echo '$USER'`
   -> WORD("echo") WORD("$USER") EOF

4) `ls|grep a`
   -> WORD("ls") PIPE WORD("grep") WORD("a") EOF

5) `cat < in.txt`
   -> WORD("cat") REDIR_IN WORD("in.txt") EOF

6) `echo hi > out.txt`
   -> WORD("echo") WORD("hi") REDIR_OUT WORD("out.txt") EOF

7) `cat file|grep a|wc -l`
   -> WORD("cat") WORD("file") PIPE WORD("grep") WORD("a") PIPE WORD("wc") WORD("-l") EOF

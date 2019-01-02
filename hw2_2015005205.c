#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

// Simplifed xv6 shell.

#define MAXARGS 10

// All commands have at least a type. Have looked at the type, the code
// typically casts the *cmd to some specific cmd type.
struct cmd {
  int type;          //  ' ' (exec), | (pipe), '<' or '>' for redirection
};

struct execcmd {
  int type;              // ' '
  char *argv[MAXARGS];   // arguments to the command to be exec-ed
};

struct redircmd {
  int type;          // < or > 
  struct cmd *cmd;   // the command to be run (e.g., an execcmd)
  char *file;        // the input/output file
  int flags;         // flags for open() indicating read or write
  int fd;            // the file descriptor number to use for the file
};

struct pipecmd {
  int type;          // |
  struct cmd *left;  // left side of pipe
  struct cmd *right; // right side of pipe
};

int fork1(void);  // Fork but exits on failure.
struct cmd *parsecmd(char*);

// Execute cmd.  Never returns.
void
runcmd(struct cmd *cmd)
{
  int p[2], r;
  struct execcmd *ecmd;
  struct pipecmd *pcmd;
  struct redircmd *rcmd;

  if(cmd == 0)
    _exit(0);
  
  switch(cmd->type){
  default:
    fprintf(stderr, "unknown runcmd\n");
    _exit(-1);

  case ' '://exec을 실행해야하는 케이스입니다.
    ecmd = (struct execcmd*)cmd;
    if(ecmd->argv[0] == 0)
      _exit(0);
	if(strcmp(ecmd->argv[0],"cat")==0 || strcmp(ecmd->argv[0],"ls")==0 || strcmp(ecmd->argv[0],"echo")==0 || strcmp(ecmd->argv[0],"rm")==0){
	//execv 함수를 통해 cat,ls,echo,rm 를 실행하기 위해선 프로그램이 있는 디렉토리PATH가 필요합니다.
		char arr[20]="/bin/";
		strcat(arr,ecmd->argv[0]);// command 앞에 PATH를 같이 붙여 주었습니다. /bin/command
		if(execv(arr,ecmd->argv)==-1){//execv는 호출에 실패했을 시 return 값이 -1입니다.
			fprintf(stderr,"exec not implemented\n");
			exit(-1);
		}
	}
	else if(strcmp(ecmd->argv[0],"sort")==0 || strcmp(ecmd->argv[0],"uniq")==0 || strcmp(ecmd->argv[0],"wc")==0){
	//sort,uniq,wc는 위와는 다르게 디렉토리PATH가 /usr/bin 이라 경우를 나누어주었습니다.
		char arr[20]="/usr/bin/";
		strcat(arr,ecmd->argv[0]);// /usr/bin/command
		if(execv(arr,ecmd->argv)==-1){//execv는 호출에 실패했을 시 return 값이 -1입니다.
			fprintf(stderr,"exec not implemented\n");
			exit(-1);
		}
	}
    break;

  case '>'://파일에 쓰기
  case '<'://파일 읽기
    rcmd = (struct redircmd*)cmd;
    if(close(rcmd->fd)==-1){//close함수호출이 실패하면 -1을 return 해줍니다.
        //불필요한 파일 디스크립션을 닫아줍니다.
		fprintf(stderr,"redirection not implemented\n");
		exit(-1);
	}
	if(open(rcmd->file, rcmd->flags,0644)<0){//open함수에는 대상파일이름, 파일에 대한 열기 옵션, 접근권한이 필요합니다.
        //함수 호출 실패시 -1을 return 합니다.
		fprintf(stderr,"redirection not implemented\n");
		exit(-1);
	}
    runcmd(rcmd->cmd);
    break;

  case '|'://Pipe과정을 구현해야합니다.
    pcmd = (struct pipecmd*)cmd;
	pid_t cpid;//manpage를 참고 하여 pid값을 받아줄 pid_t의 변수를 만들어주었습니다.
    if(pipe(p) <0){//함수호출 실패시 -1을 return 합니다.
		fprintf(stderr,"pipe not implemented\n");
		exit(-1);
	}
	cpid = fork1(); 
	if(cpid == -1){//fork가 오류가 났을 때 오류메세지를 출력하고 프로세스를 종료합니다.
		fprintf(stderr,"pipe not implemented\n");
		exit(-1);
	}
	if(cpid ==0){//자식프로세서일때 0을 return하므로 자식 프로세서에서 실행됩니다.
		if(close(1)==-1){//표준출력을 닫습니다.
			fprintf(stderr,"pipe not implemented\n");
			exit(-1);
		}
		if(dup(p[1])==-1){//파이프의 출력을 표준출력과 연결하여 자식프로세서의 출력을 부모프로세서로 출력값을 보냅니다.
			fprintf(stderr,"pipe not implemetned\n");
			exit(-1);
		}
		if(close(p[0])==-1){//자식의 입력을 닫습니다.
			fprintf(stderr,"pipe not implemented\n");
			exit(-1);
		}
		if(close(p[1])==-1){//자식의 출력을 닫습니다.
			fprintf(stderr,"pipe not implemented\n");
			exit(-1);
		}
		runcmd(pcmd->left);//파이프 기준 왼쪽 명령어를 오른쪽 명령어에게 전달합니다.
        //따라서 자식프로세서는 왼쪽 명령어를 실행한 뒤 출력값을 부모프로세서로 전달해줍니다.
	}
	else{//부모프로세스에서 돌아갑니다.
		if(close(0)==-1){//표준입력을 닫습니다.
			fprintf(stderr,"pipe not implemented\n");
			exit(-1);
		}
		if(dup(p[0])==-1){//파이프의 입력을 표준입력과 연결합니다.
			fprintf(stderr,"pipe not implemented\n");
			exit(-1);
		}
		if(close(p[0])==-1){//부모의 입력을 닫습니다.
			fprintf(stderr,"pipe not implemented\n");
			exit(-1);
		}
		if(close(p[1])==-1){//부모의 출력을 닫습니다.
			fprintf(stderr,"pipe not implemented\n");
			exit(-1);
		}
		runcmd(pcmd->right);//파이프의 오른쪽 명령어를 실행한다.
	}
	if(close(p[0])==-1){//입력을 닫습니다.
		fprintf(stderr,"pipe not implemented\n");
		exit(-1);
	}
	if(close(p[1])==-1){//출력을 닫습니다.
		fprintf(stderr,"pipe not implemented\n");
		exit(-1);
	}
	if(wait(0)==-1){//부모프로세서에서 자식프로세서가 끝나기를 기다립니다.
		fprintf(stderr,"pipe not implemented\n");
		exit(-1);
	}
	if(wait(0)==-1){
		fprintf(stderr,"pipe not implemented\n");
		exit(-1);
	}

    break;
  }    
}

int
getcmd(char *buf, int nbuf)
{
  if (isatty(fileno(stdin)))
    fprintf(stdout, "sysprog$ ");
  memset(buf, 0, nbuf);
  if(fgets(buf, nbuf, stdin) == 0)
    return -1; // EOF
  return 0;
}

int
main(void)
{
  static char buf[100];
  int fd, r;

  // Read and run input commands.
  while(getcmd(buf, sizeof(buf)) >= 0){
    if(buf[0] == 'c' && buf[1] == 'd' && buf[2] == ' '){
      // Clumsy but will have to do for now.
      // Chdir has no effect on the parent if run in the child.
      buf[strlen(buf)-1] = 0;  // chop \n
      if(chdir(buf+3) < 0)
        fprintf(stderr, "cannot cd %s\n", buf+3);
      continue;
    }
    if(fork1() == 0)
      runcmd(parsecmd(buf));
    wait(&r);
  }
  exit(0);
}

int
fork1(void)
{
  int pid;
  
  pid = fork();
  if(pid == -1)
    perror("fork");
  return pid;
}

struct cmd*
execcmd(void)
{
  struct execcmd *cmd;

  cmd = malloc(sizeof(*cmd));
  memset(cmd, 0, sizeof(*cmd));
  cmd->type = ' ';
  return (struct cmd*)cmd;
}

struct cmd*
redircmd(struct cmd *subcmd, char *file, int type)
{
  struct redircmd *cmd;

  cmd = malloc(sizeof(*cmd));
  memset(cmd, 0, sizeof(*cmd));
  cmd->type = type;
  cmd->cmd = subcmd;
  cmd->file = file;
  cmd->flags = (type == '<') ?  O_RDONLY : O_WRONLY|O_CREAT|O_TRUNC;
  cmd->fd = (type == '<') ? 0 : 1;
  return (struct cmd*)cmd;
}

struct cmd*
pipecmd(struct cmd *left, struct cmd *right)
{
  struct pipecmd *cmd;

  cmd = malloc(sizeof(*cmd));
  memset(cmd, 0, sizeof(*cmd));
  cmd->type = '|';
  cmd->left = left;
  cmd->right = right;
  return (struct cmd*)cmd;
}

// Parsing

char whitespace[] = " \t\r\n\v";
char symbols[] = "<|>";

int
gettoken(char **ps, char *es, char **q, char **eq)
{
  char *s;
  int ret;
  
  s = *ps;
  while(s < es && strchr(whitespace, *s))
    s++;
  if(q)
    *q = s;
  ret = *s;
  switch(*s){
  case 0:
    break;
  case '|':
  case '<':
    s++;
    break;
  case '>':
    s++;
    break;
  default:
    ret = 'a';
    while(s < es && !strchr(whitespace, *s) && !strchr(symbols, *s))
      s++;
    break;
  }
  if(eq)
    *eq = s;
  
  while(s < es && strchr(whitespace, *s))
    s++;
  *ps = s;
  return ret;
}

int
peek(char **ps, char *es, char *toks)
{
  char *s;
  
  s = *ps;
  while(s < es && strchr(whitespace, *s))
    s++;
  *ps = s;
  return *s && strchr(toks, *s);
}

struct cmd *parseline(char**, char*);
struct cmd *parsepipe(char**, char*);
struct cmd *parseexec(char**, char*);

// make a copy of the characters in the input buffer, starting from s through es.
// null-terminate the copy to make it a string.
char 
*mkcopy(char *s, char *es)
{
  int n = es - s;
  char *c = malloc(n+1);
  assert(c);
  strncpy(c, s, n);
  c[n] = 0;
  return c;
}

struct cmd*
parsecmd(char *s)
{
  char *es;
  struct cmd *cmd;

  es = s + strlen(s);
  cmd = parseline(&s, es);
  peek(&s, es, "");
  if(s != es){
    fprintf(stderr, "leftovers: %s\n", s);
    exit(-1);
  }
  return cmd;
}

struct cmd*
parseline(char **ps, char *es)
{
  struct cmd *cmd;
  cmd = parsepipe(ps, es);
  return cmd;
}

struct cmd*
parsepipe(char **ps, char *es)
{
  struct cmd *cmd;

  cmd = parseexec(ps, es);
  if(peek(ps, es, "|")){
    gettoken(ps, es, 0, 0);
    cmd = pipecmd(cmd, parsepipe(ps, es));
  }
  return cmd;
}

struct cmd*
parseredirs(struct cmd *cmd, char **ps, char *es)
{
  int tok;
  char *q, *eq;

  while(peek(ps, es, "<>")){
    tok = gettoken(ps, es, 0, 0);
    if(gettoken(ps, es, &q, &eq) != 'a') {
      fprintf(stderr, "missing file for redirection\n");
      exit(-1);
    }
    switch(tok){
    case '<':
      cmd = redircmd(cmd, mkcopy(q, eq), '<');
      break;
    case '>':
      cmd = redircmd(cmd, mkcopy(q, eq), '>');
      break;
    }
  }
  return cmd;
}

struct cmd*
parseexec(char **ps, char *es)
{
  char *q, *eq;
  int tok, argc;
  struct execcmd *cmd;
  struct cmd *ret;
  
  ret = execcmd();
  cmd = (struct execcmd*)ret;

  argc = 0;
  ret = parseredirs(ret, ps, es);
  while(!peek(ps, es, "|")){
    if((tok=gettoken(ps, es, &q, &eq)) == 0)
      break;
    if(tok != 'a') {
      fprintf(stderr, "syntax error\n");
      exit(-1);
    }
    cmd->argv[argc] = mkcopy(q, eq);
    argc++;
    if(argc >= MAXARGS) {
      fprintf(stderr, "too many args\n");
      exit(-1);
    }
    ret = parseredirs(ret, ps, es);
  }
  cmd->argv[argc] = 0;
  return ret;
}

using namespace std;

void handleredirection(string input,int index)
{
    char **args = parseString(input,0,index);
    int k=0;
    index = index+2;
    char *filename = getToken(input,&index,input.size());
    int fd_filew = open(filename, O_CREAT| O_WRONLY | O_TRUNC, 0700);
    pid_t child = fork();
    if(child == 0)
    {
        dup2(fd_filew,1);
        executecommandwithoutfork(args);
    }
    else{
        while(wait(NULL)>0);
    }
}

void handleappend(string input,int index)
{
    char **args = parseString(input,0,index);
    int k=0;
    index = index+3;
    char *filename = getToken(input,&index,input.size());
    int fd_filew = open(filename, O_APPEND | O_WRONLY);
    pid_t child = fork();
    if(child == 0)
    {
        dup2(fd_filew,1);
        executecommandwithoutfork(args);
    }
    else{
        while(wait(NULL)>0);
    }
}

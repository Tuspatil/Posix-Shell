using namespace std;



char** parseString(string input,int lim1,int lim2)
{
    //as an abstract, the function can tokenize between specified limits
    int i=lim1,argcount=0;
    char **args = new char*[ARGLIMIT]();
    char* token;
    for(int i=lim1;i<lim2;i++)
    {
        if(input[i]=='|')
        {
            i++;
            while(input[i]!='\0')
            {
                if(input[i]=='>')
                {
                    if(input[i+1]=='>')
                    {
                        handlepiperedirected(input,i,true);
                    }else{
                        handlepiperedirected(input,i,false);
                    }
                    return NULL;
                }
                i++;
            }
            handlepipe(input);
            return NULL;
        }
        if(input[i]=='>')
        {
            if(input[i+1]=='>')
            {
                handleappend(input,i);
                return NULL;
            }else{
            handleredirection(input,i);
            return NULL;
            }
        }
        //if you wish to handle another operator seperately, add it here
    }
    //I assume first token is always a command
    char* command = getCommand(input,&i,lim2);
    args[argcount] = command;
    argcount++;
    while((i<lim2) && (input[i]!='\0'))
    {
        switch(input[i])
        {
            //rest cases are covered here.
            //it can be string or option.
            //other cases can be added here
            case '"' :
            {
                token = getStringToken(input,&i,lim2);
            }
            break;
            default :
            {
                token = getToken(input,&i,lim2);
            }
            break;
        }
        args[argcount] = token;
        argcount++;
    }
    args[argcount]=NULL;
    return args;
}



char* getToken(string input,int* ptr,int lim2)
{
    int count=0;
    int k=0;
    int i=*ptr;
    int j=i;
    while(input[i]!=' ' && input[i]!= '\0' && i<lim2)
    {
        count++;
        i++;
    }
    char* a = new char[count+1];
    while(count-- && input[j]!='\0')    //creating token
    {
        a[k] = input[j];
        k++;
        j++;
    }
    a[k]='\0';
    while(input[i]==' ' && input[i]!='\0' && i<lim2)
    {
        i++;
    }
    *ptr = i;
    //cout<<"get token "<<a<<endl;
    return a;
}

char* getCommand(string input,int* ptr, int lim2)
{
    int i=*ptr;
    int count=0;
    while(input[i]!='\0' && input[i]!=' ' && i<lim2)
    {
        count++;
        i++;
    }
    i=*ptr;
    char *a = new char[count+6];
    int k=5;
    a[0] = '/';
    a[1] = 'b';
    a[2] = 'i';
    a[3] = 'n';
    a[4] = '/';
    while(input[i]!='\0' && input[i]!=' ' && i<lim2)
    {
        a[k] = input[i];
        i++;
        k++;
    }
    a[k]= '\0';
    while((input[i]==' ') && input[i]!='\0' && i<lim2)
    {
        i++;
    }
    *ptr = i;
    //cout<<"get command "<<a<<endl;
    return a;
}

char* getStringToken(string input,int* ptr, int lim2)
{
    int i=*ptr;
    i++;
    int j=i;
    int count=0;
    while(input[i]!='"' && i<lim2)    //scan for the next " and blindly create a token
    {
        count++;
        i++;
    }
    char *a = new char[count+1];
    int k=0;
    while(j!=i)
    {
        a[k]=input[j];
        k++;
        j++;
    }
    a[k]='\0';
    i++;
    while((input[i]==' ') && input[i]!='\0' && i<lim2)    //ignore white spaces
    {
        i++;
    }
    *ptr = i;
    //cout<<"get string token "<<a<<endl;
    return a;
}

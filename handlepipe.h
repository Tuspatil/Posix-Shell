using namespace std;


void handlepipe(string input)
{
    vector<int> indices;
    int count=0;
    int lim1,lim2;
    int j=0;
    int l;
    int i=0;
    int m=0;
    int tempcount=0;
    char** token = new char*[20];
    for(i=0;i<input.size();i++)
    {
        tempcount++;
        if(input[i]=='|')
        {
            count++;
            indices.push_back(i);
            l=0;
            char *temp = new char[tempcount-1];
            for(int k=j;k<(i-1);k++)
            {
                temp[l] = input[k];
                l++;
            }
            temp[l]='\0';
            token[m]=temp;
            m++;
            tempcount=0;
            i++;
            j=i+1;
        }
    }
    indices.push_back(input.size());
    l=0;
    char *temp = new char[tempcount-1];
    for(int k=j;k<(i-1);k++)
    {
        temp[l] = input[k];
        l++;
    }
    temp[l]='\0';
    token[m]=temp;
    m++;
    token[m]=NULL;
    //now count has the number of pipes present in the string.
    //we would require that many pipes
    int fdarray[count][2];
    for(int i=0;i<count;i++)
    {
        pipe(fdarray[i]);
    }
    //pipes have been initialized
    pid_t pidrecord[count+1];   //there will be pipe+1 processes
    //cout<<"count is "<<count<<endl;
    for(int i=0;i<=count;i++)
    {
        //the loop creates childs for each Command
        pid_t pid = fork();
        pidrecord[i]=pid;
        if(pid==0)
        {
            char **args;
            //we are inside the child process
            //we need to consider 3 cases here.
            //1. The child is executing the first Command
            //2. The child is executing an intermediate Command
            //3. The child is executing the last Command
            if(i==0)
            {
                //the first command
                dup2(fdarray[0][1],1);
                //cout<<token[i]<<"  llll  f  ";
                args = parseString(token[i],0,indices[i]-1);
                /*int p=0;
                while(args[p]!=NULL)
                {
                    cout<<args[p]<<" /\\";
                    p++;
                }*/
            }else{
                if(i==count)
                {
                    //the last command
                    dup2(fdarray[i-1][0],0);
                    int index = indices[i]-indices[i-1]-2;
                    //cout<<token[i]<<"  llll  l  ";
                    args = parseString(token[i],0,index);
                    /*int p=0;
                    while(args[p]!=NULL)
                    {
                        cout<<args[p]<<" /\\";
                        p++;
                    }*/
                }else{
                    dup2(fdarray[i-1][0],0);
                    dup2(fdarray[i][1],1);
                    int index = indices[i]-indices[i-1]-2;
                    //cout<<token[i]<<"  llll  i  ";
                    args = parseString(token[i],0,index);
                    /*int p=0;
                    while(args[p]!=NULL)
                    {
                        cout<<args[p]<<" /\\";
                        p++;
                    }*/
                    //an intermediate Command
                }
            }
            //exit(0);
            for(int j=0;j<count;j++)
            {
                close(fdarray[j][0]);
                close(fdarray[j][1]);
            }
            //execv(args[0],args);
            executecommandwithoutfork(args);
        }       //the child process ends here
        //cout<<"\n"<<token[i]<<"  "<<indices[i]<<endl;
    }
    //we are out of loop now. Lets make sure all processes are executed
    for(int j=0;j<count;j++)
    {
        close(fdarray[j][0]);
        close(fdarray[j][1]);
    }
    while(wait(NULL)>0);
}

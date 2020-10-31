using namespace std;

int executecommand(char** args)
{
    int isinbuilt = checkinbuilt(args[0]+5);
    /* use this code to see what arguments are received
    cout<<"Args .. ";
    int i=0;
    while(args[i]!=NULL)
    {
        cout<<".. "<<args[i]<<endl;
        i++;
    }*/
    switch(isinbuilt)
    {
        case 0:     //linux command
        {
            pid_t childid = fork();
            if(childid < 0)
            {
                //error occured. Print msg and exit
                cout<<"Error forking"<<endl;
                return -1;
            }
            if(childid == 0)
            {
                //I'm in child process
                ofstream ofs;
                ofs.open("status.txt");
                ofs<<0;
                ofs.close();
                int status = execv(args[0],args);
                if(status)
                {
                    cout<<strerror(errno)<<errno<<endl;
                    ofstream ofs;
                    ofs.open("status.txt");
                    ofs<<errno;
                    ofs.close();
                    exit(-1);
                }
            }
            if(childid > 0)
            {
                //I'm in parent process
                int status=0;
                wait(&status);
                return 1;
            }
            exit(0);
        }

        case 1 :    //cd
        {
            if((args[1]!=NULL) && (!strcmp(args[1],"~")))
            {
                args[1] = getenv("HOME");
            }
            chdir(args[1]);
            return 1;
        }
        case 2 :    //exit
        {
        	savetohistory();
            cout<<"Bye"<<endl;
            exit(0);
        }
        break;
        case 3 :    //alias
        {
            int h=2;
            string p;
            p=args[1];
            while(args[h]!=NULL)
            {
                p=p+" "+args[h];
                h++;
            }
            h=0;
            while(p[h]!=' ' && p[h]!='=')
                h++;
            int i=0;
            char* aliasname = getToken(p,&i,h);
            while(p[h]==' ' || p[h]=='=')
                h++;
            i=h;
            int count=0;
            while(p[h]!='\0')
            {
                count++;
                h++;
            }
            char* aliascomm = new char[count+1];
            int j=0;
            while(count--)
            {
                aliascomm[j]=p[i];
                j++;
                i++;
            }
            aliascomm[j]='\0';
            //cout<<"key "<<aliasname<<" val "<<aliascomm<<endl;
            al[aliasname]=aliascomm;
        }
        break;
        case 4 :    //$$
        {
            cout<<getpid()<<endl;
            return 1;
        }
        break;
        case 5 :    //$?
        {
            ifstream ifs;
            ifs.open("status.txt");
            int prev_status;
            ifs>>prev_status;
            cout<<prev_status<<endl;
            return 1;
        }
        break;
        case 6 :
        {
            string p;
            int h=2;
            p=args[1];
            while(args[h]!=NULL)
            {
                p=p+" "+args[h];
                h++;
            }
            cout<<getRecentStr(p)<<endl;
            return 1;
        }
        break;
        case 7 :
        {
            //abc.txt
            // int p=0;
            // while(args[p]!=NULL)
            // {
            //     cout<<args[p]<<" "<<endl;
            //     p++;
            // }
            string s = args[1];
            int i=0;
            while(s[i]!='.')
                i++;
            i++;
            string format="";
            while(s[i]!='\0')
            {
                format=format+s[i];
                i++;
            }
            //cout<<format;
            auto it = def.find(format);
            if(it!=def.end())
            {
                string path1 = it->second;
                char* path1arr = new char[path1.size()+1];
                strcpy(path1arr,path1.c_str());
                args[0]=path1arr;
                char* open = new char[4];
                open[0]='o';
                open[1]='p';
                open[2]='e';
                open[3]='n';
                strcpy(path1arr,path1.c_str());
                args[0]=path1arr;
                if(format=="pdf")
                {
                    args[2]=args[1];
                    args[1]=open;
                    args[3]=NULL;
                }else{
                args[2]=NULL;
                }
                pid_t tempid = fork();
                if(tempid==0)
                {
                    int status = execv(args[0],args);
                    if(status)
                    {
                        cout<<strerror(errno)<<errno<<endl;
                        ofstream ofs;
                        ofs.open("status.txt");
                        ofs<<errno;
                        ofs.close();
                        exit(-1);
                    }
                }else{
                    while(wait(NULL)>0);
                }
            }
            return 1;
        }
        break;
        case 8 :
        {
            t* root;
            vector<string> v;
        	getFileLists("/home/gauravkc/bin",v);
        	getFileLists("/usr/local/sbin",v);
        	getFileLists("/usr/local/bin",v);
        	getFileLists("/usr/sbin",v);
        	getFileLists("/sbin",v);
        	getFileLists("/bin",v);
        	getFileLists("/usr/games",v);
        	getFileLists("/usr/local/games",v);
        	getFileLists("/snap/bin",v);
        	root = constructTries(v);
            char** lel = getAllStrings(root,args[1]);
        	int i=0;
        	while(lel[i]!=NULL)
        	{
        		cout<<lel[i]<<"\t";
        		i++;
        	}
            cout<<endl;
            return 1;
        }
    }
}

int executecommandwithoutfork(char** args)
{
    //this function executes a command without forking.
    // I use this function instead of execv directly to handle errors or
    //call builtin functions
    int isinbuilt = checkinbuilt(args[0]+5);
    /* use this code to see what arguments are received
    cout<<"Args .. ";
    int i=0;
    while(args[i]!=NULL)
    {
        cout<<".. "<<args[i]<<endl;
        i++;
    }*/
    switch(isinbuilt)
    {
        case 0:     //linux command
        {
            ofstream ofs;
            ofs.open("status.txt");
            ofs<<0;
            ofs.close();
            int status = execv(args[0],args);
            if(status)
            {
                cout<<strerror(errno)<<errno<<endl;
                ofstream ofs;
                ofs.open("status.txt");
                ofs<<errno;
                ofs.close();
                exit(-1);
            }
        }
        case 1 :    //cd
        {
            if((args[1]!=NULL) && (!strcmp(args[1],"~")))
            {
                args[1] = getenv("HOME");
            }
            chdir(args[1]);
            return 1;
        }
        case 2 :    //exit
        {
        	savetohistory();
            cout<<"Bye"<<endl;
            exit(0);
        }
        break;
        case 3 :    //alias
        {
                int h=2;
                string p;
                p=args[1];
                while(args[h]!=NULL)
                {
                    p=p+" "+args[h];
                    h++;
                }
                h=0;
                while(p[h]!=' ' && p[h]!='=')
                    h++;
                int i=0;
                char* aliasname = getToken(p,&i,h);
                while(p[h]==' ' || p[h]=='=')
                    h++;
                i=h;
                int count=0;
                while(p[h]!='\0')
                {
                    count++;
                    h++;
                }
                char* aliascomm = new char[count+1];
                int j=0;
                while(count--)
                {
                    aliascomm[j]=p[i];
                    j++;
                    i++;
                }
                aliascomm[j]='\0';
                //cout<<"key "<<aliasname<<" val "<<aliascomm<<endl;
                al[aliasname]=aliascomm;
        }
        break;
        case 4 :    //$$
        {
            cout<<getpid()<<endl;
            return 1;
        }
        break;
        case 5 :    //$?
        {
            ifstream ifs;
            ifs.open("status.txt");
            int prev_status;
            ifs>>prev_status;
            cout<<prev_status<<endl;
            return 1;
        }
        break;

        case 6 :
        {
            string p;
            int h=2;
            p=args[1];
            while(args[h]!=NULL)
            {
                p=p+" "+args[h];
                h++;
            }
            cout<<getRecentStr(p)<<endl;
            return 1;
        }
        break;
        case 7 :
        {
            //abc.txt
            // int p=0;
            // while(args[p]!=NULL)
            // {
            //     cout<<args[p]<<" "<<endl;
            //     p++;
            // }
            string s = args[1];
            int i=0;
            while(s[i]!='.')
                i++;
            i++;
            string format="";
            while(s[i]!='\0')
            {
                format=format+s[i];
                i++;
            }
            //cout<<format;
            auto it = def.find(format);
            if(it!=def.end())
            {
                string path1 = it->second;
                char* path1arr = new char[path1.size()+1];
                char* open = new char[4];
                open[0]='o';
                open[1]='p';
                open[2]='e';
                open[3]='n';
                strcpy(path1arr,path1.c_str());
                args[0]=path1arr;
                if(format=="pdf")
                {
                    args[2]=args[1];
                    args[1]=open;
                    args[3]=NULL;
                }else{
                args[2]=NULL;
                }
                pid_t tempid = fork();
                if(tempid==0)
                {
                    int status = execv(args[0],args);
                    if(status)
                    {
                        cout<<strerror(errno)<<errno<<endl;
                        ofstream ofs;
                        ofs.open("status.txt");
                        ofs<<errno;
                        ofs.close();
                        exit(-1);
                    }
                }else{
                    while(wait(NULL)>0);
                }
            }
            return 1;
        }
        break;
        case 8 :
        {
            t* root;
            vector<string> v;
        	getFileLists("/home/gauravkc/bin",v);
        	getFileLists("/usr/local/sbin",v);
        	getFileLists("/usr/local/bin",v);
        	getFileLists("/usr/sbin",v);
        	getFileLists("/sbin",v);
        	getFileLists("/bin",v);
        	getFileLists("/usr/games",v);
        	getFileLists("/usr/local/games",v);
        	getFileLists("/snap/bin",v);
        	root = constructTries(v);
            char** lel = getAllStrings(root,args[1]);
        	int i=0;
        	while(lel[i]!=NULL)
        	{
        		cout<<lel[i]<<"\t";
        		i++;
        	}
            return 1;
        }
        cout<<endl;
    }
}


void set_def()
{
    def["txt"] = "/usr/bin/gedit";
    def["odt"] = "/usr/bin/libreoffice";
    def["ott"] = "/usr/bin/libreoffice";
    def["odm"] = "/usr/bin/libreoffice";
    def["html"] = "/usr/bin/firefox";
    def["oth"] = "/usr/bin/libreoffice";
    def["ods"] = "/usr/bin/libreoffice";
    def["ots"] = "/usr/bin/libreoffice";
    def["odg"] = "/usr/bin/libreoffice";
    def["otg"] = "/usr/bin/libreoffice";
    def["odp"] = "/usr/bin/libreoffice";
    def["otp"] = "/usr/bin/libreoffice";
    def["odf"] = "/usr/bin/libreoffice";
    def["odb"] = "/usr/bin/libreoffice";
    def["oxt"] = "/usr/bin/libreoffice";
    def["mp4"] = "/usr/bin/vlc";
    def["jpg"] = "/usr/bin/eog";
    def["jpeg"] = "/usr/bin/eog";
    def["png"] = "/usr/bin/eog";
    def["pdf"] = "/usr/bin/gio";
}


void set_alias()
{
    string command = "alias ls = \"ls --color=auto";
    char **args;
    args=parseString(command,0,command.size());
    if(args!=NULL)
        executecommand(args);
}

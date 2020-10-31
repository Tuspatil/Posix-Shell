
#include<iostream>
#include<unistd.h>
#include<sys/wait.h>
#include<string.h>
#include<dirent.h>
#include<stack>
#include<errno.h>
#include<unordered_map>
#include<vector>
#include<fcntl.h>
#include<fstream>

using namespace std;

unordered_map<string,string> al;
unordered_map<string,string> def;
vector<string> v;
#define ARGLIMIT 10
#define HISTSIZE 10
#include "mydeque.h"
#include "prototypes.h"
#include "trie.h"
#include "historyhandler.h"
#include "handlepipe.h"
#include "handlepiperedirected.h"
#include "parser.h"
#include "commandexecution.h"
#include "ioredirection.h"
#include "suggestions.h"
using namespace std;

int checkinbuilt(string command)
{
    if(command == "cd")
        return 1;
    if(command == "exit")
        return 2;
    if(command == "alias")
        return 3;
    if(command == "$$")
        return 4;
    if(command == "$?")
        return 5;
    if(command == "search")
        return 6;
    if(command == "open")
        return 7;
    if(command == "complete")
        return 8;
    //handle custom command in executecommand and executecommandwithoutfork functions
    return 0;
}

using namespace std;

string checkAlias(string command)
{
    int i=0;
    string commandname = getToken(command,&i,command.size());
    auto it = al.find(commandname);
    if(it!=al.end())
    {
        //alias exists
        auto it2 = al.find(commandname);
        while(it2!=al.end())
        {
            commandname = it2->second;
            it2 = al.find(commandname);
        }
        //commandname is final command namespace
        int j=0;
        int count=0;
        int k=i;
        while(command[i]!='\0')
        {
            count++;
            i++;
        }
        char* reststuff = new char[count+1];
        while(count--)
        {
            reststuff[j]=command[k];
            j++;
            k++;
        }
        reststuff[j]='\0';
        string newcommand = commandname+" "+reststuff;
        return newcommand;
    }else{
        return command;
    }
}

int loop()
{
    int status;
    string command;
    char** args;
	sethistory(HISTSIZE);
    load_history();
    set_def();
    set_alias();
    string ps1string = "> ";
    do{
        cout<<ps1string;
        getline(cin,command);
        insertinhistory(command);
        command = checkAlias(command);
        args=parseString(command,0,command.size());
        /*int p=0;
        while(args[p]!=NULL)
        {
            cout<<args[p]<<" "<<endl;
            p++;
        }*/
        if(args!=NULL)
            status=executecommand(args);
        //cout<<getRecent();
    }while(1);
}

int main()
{
    loop();
    return 0;
}

using namespace std;


char** his;
int limit;
int head;
int tail;
t* root;
void sethistory(int lim)
{
    his = new char*[lim+1];
    limit = lim+1;
    head=0;
}
void load_history()
{
    FILE *fp = fopen("history.txt","r");
    char c;
    int i=0;
    int j=0;
    int count = limit;
    c=getc(fp);
    if(c==EOF)
    {
    	//file is empty
    	head=0;
    	tail=1;
    	return;
    }
    while(c!=EOF && count--)
    {
        char* temp = new char[20];
        j=0;
        while(c!='\n' && c!=EOF)
        {
            temp[j]=c;
            j++;
            c=getc(fp);
        }
        temp[j]='\0';
        his[i]=temp;
        v.push_back(temp);
        i++;
        c=getc(fp);
    }
    root = constructTrie(v);
    tail=i;
    fclose(fp);
}
void insertinhistory(string command)
{
    char *temp = new char[command.size()];
    strcpy(temp,command.c_str());
    insertinTrie(root,command);
    his[tail] = temp;
    tail=(tail+1)%limit;
    if(tail == head)
    {
        free(his[head]);
        head=(head+1)%limit;
    }
}
string getRecent()
{
    string s = his[(tail-1+limit)%limit];
    return s;
}

string getRecentStr(string str)
{
    return getSuggestion(root,str);
}
void reset()
{

}
void savetohistory()
{
    FILE *fp = fopen("history.txt","w");
    int j=0;
    int i=head;
    while(i!=tail)
    {
        j=0;
        if(his[i]!=NULL)
        {
            while(his[i][j]!='\0')
            {
                putc(his[i][j],fp);
                j++;
            }
            putc('\n',fp);
        }
        i=(i+1)%limit;
    }
    fclose(fp);
}

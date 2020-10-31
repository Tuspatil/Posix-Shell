/*#include <iostream>
#include <unordered_map>
#include <vector>
#include <stack>
#include <string>
#include<dirent.h>
#include "mydeque.h"
using namespace std;
//using namespace gaurav;

class t{
public:
	gaurav::deque<char> *dq = new gaurav::deque<char>(10);
	unordered_map<char,t*> mp;
	bool isEnd;
	t(){
	}
};
*/

void getFileLists(string path,vector<string> &files)
{
	DIR *dir;
	struct dirent *ent;
	string temp;
	if ((dir = opendir(path.c_str())) != NULL)
	{
		while((ent = readdir (dir)) != NULL) {
			temp = ent->d_name;
			if(temp[0]=='.')
				continue;
	    	files.push_back(ent->d_name);
	  	}
	 	closedir (dir);
	}else
	{
		cout<<"Error opening directory";
	}
}

char* createCopys(char* arr,int size)
{
	//cout<<"I got "<<arr<<endl;
	char* temp = new char[size+1];
	int i;
	for(i=0;i<size;i++)
	{
		temp[i]=arr[i];
	}
	temp[i]='\0';
	return temp;
}

t* createNodes()
{
	t *temp = new t();
	temp->isEnd = false;
	return temp;
}

void insertinTries(t *root, string val)
{
	t *temp = root;
	t *temp2;
	for (int i = 0; i < val.length(); i++)
	{
		char tp = val[i];
		//cout<<tp;
		if (temp->mp.find(tp) == temp->mp.end())
		{
			//temp->dq->removekey(tp);
			temp->dq->push_back(tp);
			temp2 = createNodes();
			temp->mp.insert({tp,temp2});
		}else{
            temp->dq->removekey(tp);
            temp->dq->push_back(tp);
		}
		auto it = temp->mp.find(tp);
		//if(it==temp->mp.end())
        //    cout<<"lol. didnt find"<<endl;
		//temp->isEnd = false;
		char* lol = temp->dq->getArray();
		/*int j =0;
		while(lol[j]!='\0')
		{
			cout<<lol[j]<<" ";
			j++;
		}
		cout<<" isend is "<<temp->isEnd;
		cout<<endl;*/
		temp = (*it).second;
	}
	char* lol = temp->dq->getArray();
	/*int j =0;
	cout<<"out "<<" ";
	while(lol[j]!='\0')
	{
		cout<<lol[j]<<" ";
		j++;
	}
	cout<<" isend is "<<temp->isEnd;
	cout<<endl;*/
	temp->isEnd = true;
}

t* constructTries(vector<string> v)
{
	t* root = createNodes();
	auto it = v.begin();
	while(it!=v.end())
	{
		insertinTries(root,*it);
		it++;
	}
	return root;
}
/*
string getSuggestion(t* root,string str)
{
    int k=0;
    char* result = new char[100];
    t* temp=root;
    for(int i=0;i<str.size();i++)
    {
        //cout<<str[i];
        if(temp->mp.find(str[i])==temp->mp.end())
        {
            //doesnt exist. return
            return "Doesn't Exist";
        }else{
            result[k]=str[i];
            temp=temp->mp[str[i]];
            k++;
        }
    }
    //cout<<temp->dq->back();
    //return "lel";

    while(!(temp->dq->empty()))
    {
        result[k] = temp->dq->back();
        temp=temp->mp[temp->dq->back()];
        k++;
    }
	result[k]='\0';
    return result;
}*/

char** getAllStrings(t* node, string str)
{
	stack<pair<char,t*>> nodes;
	stack<pair<char,int>> noofchildren;
	pair<char,t*> p;
	pair<char,int> c;
	int children;
	char* temp=new char[100];
	char** result = new char*[100];
	int temp_index=0;
	int result_index=0;
	for(int i=0;i<str.length();i++)
	{
		temp[i]=str[i];
		temp_index++;
		auto it = node->mp.find(str[i]);
		if(it!= node->mp.end())
			node=(*it).second;
		else
			cout<<"Error in for loop";
	}
	char* t1 = node->dq->getArray();
	int i,j,k;
	i=0;
	while(t1[i]!='\0')
		i++;
	char root = str[str.length()-1];
	nodes.push({root,node});
	noofchildren.push({root,i});
	/*temp[temp_index]=root;
	temp_index++;*/
	while(!nodes.empty())
	{
		p = nodes.top();
		char * t7 = p.second->dq->getArray();
		i=0;
		c = noofchildren.top();
		/*cout<<".. "<<c.first<<" .. "<<c.second<<" ; ";
		while(t7[i]!='\0')
		{
			cout<<t7[i]<<" ";
			i++;
		};
		cout<<endl;*/
		if(c.second == 0)
		{
			nodes.pop();
			noofchildren.pop();
			temp_index--;
			continue;
		}
		if(c.second == 1)
		{
			auto it = p.second->mp.find(p.second->dq->back());
			bool isitend = p.second->isEnd;
			if(isitend)
			{
				char* t2 = createCopys(temp,temp_index);
				result[result_index]=t2;
				result_index++;
				i=0;
				char *t8=p.second->dq->getArray();
				while(t8[i]!='\0')
					i++;
				//cout<<",lll"<<i<<" lll,";
				noofchildren.pop();
				int newsize = c.second - 1;
				noofchildren.push({c.first,newsize});
			}else{
				noofchildren.pop();
				int newsize = c.second - 1;
				noofchildren.push({c.first,newsize});
				char *t3 = (*it).second->dq->getArray();
				char tp = (*it).first;
				i=0;
				while(t3[i]!='\0')
					i++;
				nodes.push({tp, (*it).second});
				if(i==0)
					noofchildren.push({tp,i+1});
				else
					noofchildren.push({tp,i});
				temp[temp_index]=tp;
				temp_index++;
			}
			continue;
		}
		if(c.second > 1)
		{
			noofchildren.pop();
			int newsize = c.second - 1;
			noofchildren.push({c.first,newsize});
			char t4 = p.second->dq->back();
			auto it = p.second->mp.find(t4);
			char* t5 = (*it).second->dq->getArray();
			i=0;
			while(t5[i]!='\0')
				i++;
			p.second->dq->removekey(t4);
			p.second->dq->push_front(t4);
			nodes.push({t4,(*it).second});
			noofchildren.push({t4,i});
			temp[temp_index]=t4;
			temp_index++;
		}
	}
	result[result_index]=NULL;
	return result;
}
/*
int main()
{
    t* root;
	/*vector<string> v;
	v.push_back("Gauravk");
	v.push_back("Gaurav");
	v.push_back("Gauravi");
	v.push_back("Gauri");
	v.push_back("Gaurang");
	v.push_back("Gauresh");
	v.push_back("Gourav");
	//v.push_back("Gauresh");
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
	root = constructTrie(v);
    //cout<<getSuggestion(root,"Gou");
	string input;
	getline(cin,input);
	char** lel = getAllStrings(root,input);
	int i=0;
	while(lel[i]!=NULL)
	{
		cout<<lel[i]<<"\t";
		i++;
	}
	return 0;
}
*/

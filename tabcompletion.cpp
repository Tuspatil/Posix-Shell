#include<iostream>
#include<dirent.h>
#include<vector>
#include<string.h>
#include <unordered_map>
#include "mydeque.h"
#include "prototypes.h"
#include "trie.h"
using namespace std;

void getFileList(string path,vector<string> &files)
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


int main() {
	vector<string> v;
	getFileList("/home/gauravkc/bin",v);
	getFileList("/usr/local/sbin",v);
	getFileList("/usr/local/bin",v);
	getFileList("/usr/sbin",v);
	getFileList("/sbin",v);
	getFileList("/bin",v);
	getFileList("/usr/games",v);
	getFileList("/usr/local/games",v);
	getFileList("/snap/bin",v);
	/*auto it = v.begin();
	while(it!=v.end())
	{
		cout<<*it<<endl;
		it++;
	}*/
	t* commroot;
	commroot = constructTrie(v);
	cout<<getSuggestion(commroot,"ls");
	return 0;
}

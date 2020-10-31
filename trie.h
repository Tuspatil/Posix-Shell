/*#include <iostream>
#include <unordered_map>
#include <vector>*/
using namespace std;
// #include "mydeque.h"

// class t{
// public:
// 	deque<char> *dq = new deque<char>(10);
// 	unordered_map<char,t*> mp;
// 	bool isEnd;
// 	t(){
// 	}
// };

t* createNode()
{
	t *temp = new t();
	temp->isEnd = false;
	return temp;
}

void insertinTrie(t *root, string val)
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
			temp2 = createNode();
			temp->mp.insert({tp,temp2});
		}else{
            temp->dq->removekey(tp);
            temp->dq->push_back(tp);
		}
		auto it = temp->mp.find(tp);
		//if(it==temp->mp.end())
        //    cout<<"lol. didnt find"<<endl;
		//temp->isEnd = false;
		temp = (*it).second;
	}
	temp->isEnd = true;
}

t* constructTrie(vector<string> v)
{
	t* root = createNode();
	auto it = v.begin();
	while(it!=v.end())
	{
		insertinTrie(root,*it);
		it++;
	}
	return root;
}

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
}
/*int main()
{
    t* root;
	vector<string> v;
	v.push_back("Gauravk");
	v.push_back("Gaurav");
	v.push_back("Gauravi");
	v.push_back("Gauri");
	v.push_back("Gaurang");
	v.push_back("Gauresh");
	v.push_back("Gourav");
	v.push_back("Gauresh");
	root = constructTrie(v);
    cout<<getSuggestion(root,"Gou");
	return 0;
}
*/

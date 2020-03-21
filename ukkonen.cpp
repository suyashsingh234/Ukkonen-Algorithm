/*
Implementation of Ukkonen's algorithm for
linear time suffix tree construction

Algorithm implementation by Suyash Singh
Applications by
*/
#include<bits/stdc++.h>
using namespace std;
struct node
{
    int start;
    int *end;
    vector<struct node*>alpha;
    struct node* suffixlink;
};
struct node* getnode()
{
    struct node* newnode= new node;
    newnode->end=new int;
    newnode->alpha.resize(26);
    newnode->alpha.clear();
    newnode->suffixlink=nullptr;
    return newnode;
}
//suffix tree
class suffix
{
    public:
    int END; //global end
    struct node* root;
    struct node* curnode;   //active node
    int active_edge;
    int active_length;
    string str;
    int remainder;

    suffix()
    {
        remainder=0;
        END=-1;
        //root has start and end -1
        root=getnode();
        root->start=-1;
        *(root->end)=-1;

        curnode=root;
        active_edge=-1;
        active_length=0;
    }

    void insert(char c)
    {
        END++;
        int cint=c-'a';
        struct node* lastnode=nullptr;
        if(curnode->alpha[cint]==nullptr)
        {
            struct node* newnode=getnode();
            newnode->start=cint;
            newnode->end=&END;
            curnode->alpha[cint]=newnode;
        }
        else{
            remainder++;
            if(active_edge==-1)
            {
                active_edge=cint;
                active_length=1;
            }
            else if(str[END] == str[curnode->alpha[active_edge]->start+active_length]){
                active_length++;
            }
            else{

            }
        }

    }

    struct node* make(string s)
    {
        int len=s.size();
        str=s;
        for(int i=0;i<len;i++)
            insert(s[i]);
        return root;
    }
    void levelorder()
    {
        int prev=-1;
        queue<pair<struct node*,int>>q;    //node, current level
        q.push(make_pair(root,0));
        while(!q.empty())
        {
            pair<struct node*,int>p=q.front();
            q.pop();
            if(p.second!=prev)
            {
                prev=p.second;
                cout<<endl;
            }
            cout<<p.first->start<<","<<*(p.first->end)<<"   ";
            for(int i=0;i<26;i++)
            {
                if(p.first->alpha[i]!=nullptr)
                    q.push(make_pair(p.first->alpha[i],p.second+1));
            }
        }
    }
};
int main()
{
    suffix s;
    s.make("abcab");
    s.levelorder();
    return 0;
}

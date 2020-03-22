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
        remainder++;
        int r=remainder;
        while(r>0)
        {
            if(active_length==0)
            {
                lastnode=nullptr;
                curnode=root;
                if(curnode->alpha[cint]==nullptr)
                {
                    curnode->alpha[cint]=getnode();
                    curnode->alpha[cint]->start=END;
                    curnode->alpha[cint]->end=&END;
                    remainder--;
                }
                else{
                    active_length=1;
                    active_edge=cint;
                }
            }
            else{
                if(str[curnode->alpha[active_edge]->start+active_length]==str[END])
                {
                    lastnode=nullptr;
                    active_length++;
                    remainder++;
                    r=0;
                }
                else{

                    curnode->alpha[active_edge]->alpha[str[END]-'a']=getnode();
                    curnode->alpha[active_edge]->alpha[str[END]-'a']->start=END;
                    curnode->alpha[active_edge]->alpha[str[END]-'a']->end=&END;

                    int nxtpos=curnode->alpha[active_edge]->start+active_length;

                    curnode->alpha[active_edge]->alpha[str[nxtpos]-'a']=getnode();
                    curnode->alpha[active_edge]->alpha[str[nxtpos]-'a']->start=nxtpos;
                    curnode->alpha[active_edge]->alpha[str[nxtpos]-'a']->end=&END;

                    delete curnode->alpha[active_edge]->end;
                    curnode->alpha[active_edge]->end=new int;
                    *(curnode->alpha[active_edge]->end)=nxtpos-1;


                    if(lastnode!=nullptr)
                        lastnode->suffixlink=curnode->alpha[active_edge];

                    lastnode=curnode->alpha[active_edge];
                    active_edge=str[curnode->alpha[active_edge]->start+1]-'a';
                    curnode=root;
                    active_length--;
                    remainder--;
                }
            }
            r--;
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
    s.make("abcabx");
    s.levelorder();
    return 0;
}

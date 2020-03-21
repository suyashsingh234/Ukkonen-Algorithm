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
};
struct node* getnode()
{
    struct node* newnode= new node;
    newnode->end=new int;
    newnode->alpha.resize(26);
    newnode->alpha.clear();
    return newnode;
}
//suffix tree
class suffix
{
    public:
    int END; //global end
    struct node* root;
    struct node* curnode;   //active node
    suffix()
    {
        END=-1;
        //root has start and end -1
        root=getnode();
        root->start=-1;
        *(root->end)=-1;

        curnode=root;
    }
    void insert(char c)
    {
        END++;
        int cint=c-'a';
        if(curnode->alpha[cint]==nullptr)
        {
            struct node* newnode=getnode();
            newnode->start=END;
            newnode->end=&END;
        }
    }
    struct node* make(string s)
    {
        int len=s.size();
        for(int i=0;i<len;i++)
            insert(s[i]);
        return root;
    }
    void levelorder()
    {
        int prev=-1;
        queue<pair<struct node*,int>>q;
        q.push(make_pair(root,0));
        while(!q.empty())
        {

        }
    }
};
int main()
{
    suffix s;
    s.insert("abc");
    s.levelorder();
    return 0;
}

#include <stdio.h>
#include <stdlib.h>

struct Node
{
    struct Node *left,*right;
    int val;
} *root=NULL;

int rec[1000006];
void addNode(int,struct Node*);
void printTree(struct Node* curr,int depth)
{
    int i;
    if(curr==NULL)return;
    printf("\t");
    for(i=0;i<depth;i++)
        if(i==depth-1)
            // printf("%s\u2014\u2014\u2014",rec[depth-1]?"\u0371":"\u221F");
            printf("%s└──",rec[depth-1]?"":"");
        else
            printf("%s   ",rec[i]?"*":"  ⎸");
    printf("%d\n",curr->val);
    rec[depth]=1;
    printTree(curr->left,depth+1);
    rec[depth]=0;
    printTree(curr->right,depth+1);
}
int main()
{
    root=(struct Node*)malloc(sizeof(struct Node));
    root->val=50;
    //addNode(50,root);
    addNode(75,root);    addNode(25,root);
    addNode(15,root);    addNode(30,root);
    addNode(100,root);    addNode(60,root);
    addNode(27,root);    addNode(31,root);
    addNode(101,root);    addNode(99,root);
    addNode(5,root);    addNode(61,root);
    addNode(55,root);    addNode(20,root);
    addNode(0,root);    addNode(21,root);
    //deleteNode(5,root);

    printTree(root,0);
    return 0;
}

void addNode(int v,struct Node* traveller)
{
    struct Node *newEle=(struct Node*)malloc(sizeof(struct Node));
    newEle->val=v;
    for(;;)
    {
        if(v<traveller->val)
        {
            if(traveller->left==NULL){traveller->left=newEle;return;}
            traveller=traveller->left;
        }
        else if(v>traveller->val)
        {
            if(traveller->right==NULL){traveller->right=newEle;return;}
            traveller=traveller->right;
        }
        else
        {
            printf("%d Input Value is already present in the Tree !!!\n",v);
            return;
        }
    }
}
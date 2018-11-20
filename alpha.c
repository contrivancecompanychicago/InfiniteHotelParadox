#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define data room_no

/*struct Guest{
  char name[10];
  int room_no;
  char pass_key[20];

}guest[2];*/

struct node
{
    char name[10];
    int room_no;
    char pass_key[20];
    struct node* left;
    struct node* right;
};

struct node* getnode(int item,char name[],char key[])
{
    struct node* newNode = (struct node *)malloc(sizeof(struct node));
    newNode->data = item;
    strcpy(newNode->name,name);
    strcpy(newNode->pass_key,key);
    newNode->left = newNode->right = NULL;
    return newNode;
}


struct node* insert(struct node* root,int item, char name[],char key[])
{
    if(root == NULL)       //empty node
    {
        root = getnode(item,name,key);
        return root;
    }
    else if( item <= root->data)
        root->left = insert(root->left,item,name,key);
    else
        root->right = insert(root->right,item,name,key);
    return root;

}

void inorder(struct node* root)
{
    if(root != NULL)
    {
        inorder(root->left);
        printf("%s\n",root->name);
        printf(" %d\n ",root->data);
        printf("%s\n",root->pass_key);
        inorder(root->right);
    }
}
/*
struct node* findmin(struct node* root)
{
    struct node* temp = root;
    while(temp->left!=NULL)
    {
        temp=temp->left;
    }
    return temp;
}

struct node* deletenode(struct node* root,int data)
{
    //search element
    if(root == NULL)
        return root;
    else if(data < root->data)
        root->left=deletenode(root->left,data);
    else if(data > root->data)
        root->right=deletenode(root->right,data);
    else
    {
        //case 1 : deleting a leaf node
        if(root->left==NULL && root->right==NULL)
        {
            free(root);
            root=NULL;
            return root;
        }
        //case 2 : deleting a node with single right child
        else if(root->left==NULL && root->right!=NULL)
        {
            struct node* temp = root->right;
            free(root);
            return temp;
        }
        //case 3 : deleting a node with single left child
        else if(root->right==NULL && root->left!=NULL)
        {
            struct node* temp = root->left;
            free(root);
            return temp;
        }
        //case 4 : deleting a node with two childs
        else
        {
            struct node* temp=findmin(root->right);
            root->data=temp->data;
            root->right=deletenode(root->right,temp->data);
            return root;
        }
    }
}*/

int main()
{
      struct node* root = NULL;
      int rm,choice,room,i;
      char naam[20], pk[10];
      for(;;)
    {
        printf("\n\n## Hotel  ##");
        printf("\n1.INSERT \n2.DISPLAY\n3.Exit \n");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:printf("How many rooms do you want?\n");
                   scanf("%d",&room);
                   for(i=0;i<room;i++)
                   {
                     printf("Enter name\n");
                     scanf("%s",naam);
                     printf("Enter Room no\n");
                     scanf("%d",&rm);
                     printf("Enter key\n");
                     scanf("%s",pk);
                     root = insert(root,rm,naam,pk);
                   }
                   break;
            case 2: inorder(root);
                    break;
            case 3: exit(1);
                    break;
                  }
                }


     return 0;

}

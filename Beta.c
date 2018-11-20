#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define data room_no

/*struct Guest{
  char name[10];
  int room_no;
  char pass_key[20];

}guest[2];*/
void gen_random(char *s, const int len) {
    static const char alphanum[] =
        "abcdefghijklmnopqrstuvwxyz";

    for (int i = 0; i < len; ++i) {
        s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    s[len] = 0;
}


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

/*void inorder1(struct node* root)
{
  printf("%s\n",root->name);
  printf(" %d\n ",root->data);
  printf("%s\n",root->pass_key);
}*/
int search(struct node* root, int key)
{
    if (root == NULL)
        return 0;
    else if (root->data == key)
    {
        return 1; }

    else if (root->data < key)
       return search(root->right, key);

    else
        return search(root->left, key);
}


struct node * final(struct node* root, int key)
{
    struct node* temp = NULL;
    if (root == NULL)
        return temp;
    else if (root->data == key)
    {
        temp = root;
        return temp; }

    else if (root->data < key)
       return final(root->right, key);

    else
        return final(root->left, key);
}

int search1(struct node* root, int key, char *s)
{
    if (root == NULL)
        return 0;
    else if (root->data == key)
    {
      int i;
      for(i=0; i<15; i++)
      {
        s[i] = root->pass_key[i];
      }

    }

    else if (root->data < key)
        return search(root->right, key);

    else
        return search(root->left, key);
}


struct node* findmin(struct node* root)
{
    struct node* temp = root;
    while(temp->left!=NULL)
    {
        temp=temp->left;
    }
    return temp;
}

struct node* deletenode(struct node* root,int itemm)
{
    //search element
    if(root == NULL)
        return root;
    else if(itemm < root->data)
        root->left=deletenode(root->left,itemm);
    else if(itemm > root->data)
        root->right=deletenode(root->right,itemm);
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
}

void computeLPSArray(char* pat, int M, int* lps);

// Prints occurrences of txt[] in pat[]
void KMPSearch(char* pat, char* txt,struct node* root,int key)
{
    int M = strlen(pat);
    int N = strlen(txt);

    // create lps[] that will hold the longest prefix suffix
    // values for pattern
    int lps[M];

    // Preprocess the pattern (calculate lps[] array)
    computeLPSArray(pat, M, lps);

    int i = 0; // index for txt[]
    int j = 0; // index for pat[]
    while (i < N) {
        if (pat[j] == txt[i]) {
            j++;
            i++;
        }

        if (j == M) {//Checking for the aptness of the key for the hotel roonm.
            j = lps[j - 1];
            struct node* temp1 = final(root,key);
            printf("Congrats, You entered correct key\n");
            printf("The name is %s\n",temp1->name);
        }

        // mismatch after j matches
        else if (i < N && pat[j] != txt[i]) {
            // Do not match lps[0..lps[j-1]] characters,
            // they will match anyway
            if (j != 0)

                j = lps[j - 1];
            else
                i = i + 1;
                if (i==N)
                {
                    printf("\nYou entered a wrong key");
                }

        }

    }
}

// Fills lps[] for given patttern pat[0..M-1]
void computeLPSArray(char* pat, int M, int* lps)
{
    // length of the previous longest prefix suffix
    int len = 0;

    lps[0] = 0; // lps[0] is always 0

    // the loop calculates lps[i] for i = 1 to M-1
    int i = 1;
    while (i < M) {
        if (pat[i] == pat[len]) {
            len++;
            lps[i] = len;
            i++;
        }
        else // (pat[i] != pat[len])
        {
            if (len != 0) {
                len = lps[len - 1];

                // Also, note that we do not increment
                // i here
            }
            else // if (len == 0)
            {
                lps[i] = 0;
                i++;
            }
        }
    }
}



int main()
{
      char assigned_key[100], key_entered[100];

      struct node* root = NULL;
      int rm,choice,room,i,key,keyy;
      char naam[20], pk[10];
      for(;;)
    {
        printf("\n\n## Hotel  ##");
        printf("\n1.Get an available room \n2.Rooms Occupied\n3.Access the Data of a Room \n4.Room Availablity Check\n5.Delete\n");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:printf("How many rooms do you want?\n");
                   scanf("%d",&room);
                   for(i=0;i<room;i++)
                   {
                     gen_random(assigned_key, 14);
                     printf("Enter name\n");
                     scanf("%s",naam);
                     printf("Enter Room no\n");
                     scanf("%d",&rm);
                     printf("Your Assigned Key is: %s", assigned_key);

                     root = insert(root,rm,naam,assigned_key);
                   }
                   break;
            case 2:
                    printf("The rooms occupied as of this moment are:\n");
                    inorder(root);
                    break;
            case 3:
                    printf("Enter the Room Number: ");
                    scanf("%d", &key);
                    struct node* temp1 = final(root,key);

                    if(final(root,key))
                    {
                      printf("Enter the key for this room: ");
                      scanf("%s", key_entered);
                      KMPSearch(key_entered, temp1->pass_key,root,key);

                    }
                    break;

            case 4:printf("Enter the Room to be searched\n");
                   scanf("%d",&key);
                   if(search(root,key) == 1)
                    printf("Room is already occupied!\n");
                   else
                    printf("Room is available.\n");
                   break;
            case 5: printf("Enter the room to be vacated: ");
                   scanf("%d",&keyy);
                   deletenode(root,keyy);
                   break;
                  }
                }


     return 0;

}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100
typedef struct node
{
    char* data;
    struct node* left, *right;
    int height;
} node;

node* balancer(node*root);
node* leftRotate(node*n);
node* rightRotate(node*n);

node* newNode (char* word)
{
    node*n = malloc(sizeof (node));
    n->left = n->right = NULL;
    n->height = 1;
    n->data = malloc(strlen(word)+1);
    strcpy(n->data,word);
    return n;
}

node* search (node *root, char *word)
{
    if (root == NULL)
        return NULL;
    else if (!strcasecmp(root->data,word))
        return root;
    else if (strcasecmp(root->data,word) > 0)
        return search ( root->left,word);
    else
        return search (root->right,word);
}
node* searchBefore (node *root, char *word)
{
    node *a=root,*b=root;
    if(!root) return NULL;
    else
    {
        while(a)
        {
            int s = strcasecmp(word,a->data);
            if(!s) break;
            else if(s < 0)
            {
                b=a;
                a=a->left;
            }
            else
            {
                b=a;
                a=a->right;
            }
        }
    }
    return b;
}

void inOrder(node *root)
{
    if (root)
    {
        inOrder(root->left);
        printf("%s\t", root->data);
        inOrder(root->right);
    }
}
node* findmin (node *root)
{
    if (root == NULL)
        return root;
    else if (root ->left == NULL)
        return root;
    else
        return findmin (root->left);
}
node* delete(node* root, const char* word) {
    if (!root)
        return NULL;

    int cmp = strcasecmp(word, root->data);
    if (cmp < 0)
        root->left = delete(root->left, word);
    else if (cmp > 0)
        root->right = delete(root->right, word);
    else {
        // Node to delete found
        if (!root->left || !root->right) {
            node* temp = root->left ? root->left : root->right;
            if (!temp) {
                // No child
                free(root->data);
                free(root);
                return NULL;
            } else {
                // One child
                node* toFree = root;
                root = temp;
                free(toFree->data);
                free(toFree);
            }
        } else {
            // Two children
            node* min = findmin(root->right);
            free(root->data);
            root->data = malloc(strlen(min->data) + 1);
            strcpy(root->data, min->data);
            root->right = delete(root->right, min->data);
        }
    }

    // Update height
    root->height = 1 + max(height(root->left), height(root->right));

    // Balance the tree
    root = balancer(root);

    return root;
}

void freeTree(node *r) 
{
    if (!r) return;
    freeTree(r->left);
    freeTree(r->right);
    free(r->data);
    free(r);
}
//AVL Code
int max(int a, int b) 
{
    return (a > b) ? a : b;
}
int height(node* n) 
{
    if (!n) return 0;
    return n->height;
}
int getBalance(node* n) 
{
    if (!n) return 0;
    return height(n->left) - height(n->right);
}
int count(node* root) 
{
    if (!root) return 0;
    return 1 + count(root->left) + count(root->right);
}
node* balancer(node*root)
{
    int balance = getBalance(root);

    if (balance >= 2 && getBalance(root->left) >= 0) // LL
        return rightRotate(root);
    if (balance >= 2 && getBalance(root->left) < 0) // LR
    { 
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (balance <= -2 && getBalance(root->right) <= 0) // RR
        return leftRotate(root);
    if (balance <= -2 && getBalance(root->right) > 0) // RL
    { 
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}

node* leftRotate(node*n)
{
    node* x = n->right;
    node* T2 = x->left;

    x->left=n;
    n->right=T2;

    n->height = 1 + max(height(n->left), height(n->right));
    x->height = 1 + max(height(x->left), height(x->right));
    return x;
}

node* rightRotate(node*n)
{
    node* x = n->left;
    node* T2 = x->right;

    x->right=n;
    n->left=T2;

    n->height = 1 + max(height(n->left), height(n->right));
    x->height = 1 + max(height(x->left), height(x->right));
    return x;
}

node* insert(node* root, const char* word)
{
    if (!root)
        return newNode(word);
    if (strcasecmp(word, root->data) < 0)
        root->left = insert(root->left, word);
    else if (strcasecmp(word, root->data) > 0)
        root->right = insert(root->right, word);
    else
        return root; // word already exists

    root->height = 1 + max(height(root->left), height(root->right));

    int balance = getBalance(root);

    root = balancer(root);

    return root;
}
node* loadTree(char* filename)
{
    FILE* fp = fopen(filename, "r");
    if (!fp)
    {
        printf("Error opening file");
        return NULL;
    }

    char buffer[MAX];
    node* root = NULL;

    while (fgets(buffer, sizeof(buffer), fp)) //while fgets() is reading something
    {
        buffer[strcspn(buffer, "\n")] = '\0'; // Remove trailing newline
        root = insert(root, buffer);
    }

    fclose(fp);
    return root;
}

void checkDictionary(node*root,char* word)
{
    if (search(root, word))
        printf("Found!\n");
    else
    {
        node*n=searchBefore(root,word);
        printf("Suggestions:\n");
        printf("- %s\n",n->data);
        if(n->left) printf("- %s\n",n->left->data);
        if(n->right) printf("- %s\n",n->right->data);
    }
}
void func()
{
    char word[MAX];
    node* root = loadTree("Dictionary.txt");
    printf("Welcome to the Fifth Assignment\n\n");
    printf("Number of Nodes: %d\n",count(root));
    printf("Tree Height: %d\n",height(root));

    printf("\nEnter a word to search: ");
    scanf("%s", word);
    checkDictionary(root,word);
    freeTree(root);
}

int main()
{
    func();
    return 0;
}
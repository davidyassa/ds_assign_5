#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 1000
typedef struct node
{
    char *data; // data is string
    struct node *left, *right;
    int height;
} node;

node *balancer(node *root);
node *leftRotate(node *n);
node *rightRotate(node *n);
int maxx(int a, int b);
int height(node *n);

node *newNode(const char *word)
{
    node *n = malloc(sizeof(node));
    n->left = n->right = NULL;
    n->height = 1;
    n->data = malloc(strlen(word) + 1);
    strcpy(n->data, word);
    return n;
}
// searching is now done with strcasecmp() instead of integer operations
node *search(node *root, char *word)
{
    if (root == NULL)
        return NULL;
    else if (!strcasecmp(root->data, word))
        return root;
    else if (strcasecmp(root->data, word) > 0)
        return search(root->left, word);
    else
        return search(root->right, word);
}
// get the last accessed node before the null if the word isn't found
node *searchBefore(node *root, const char *word, node **last)
{
    *last = NULL;
    while (root)
    {
        *last = root;
        int s = strcasecmp(word, root->data);
        if (!s)
            return root;
        else if (s < 0)
        {
            root = root->left;
        }
        else // s>0
        {
            root = root->right;
        }
    }
    return NULL;
}

void inOrder(node *root)
{
    if (root)
    {
        inOrder(root->left);
        printf("%s ", root->data);
        inOrder(root->right);
    }
}
node *findMin(node *root)
{
    if (root == NULL)
        return root;
    else if (root->left == NULL)
        return root;
    else
        return findMin(root->left);
}
node *findMax(node *root)
{
    if (root == NULL)
        return root;
    else if (root->right == NULL)
        return root;
    else
        return findMax(root->right);
}
node *delete(node *root, const char *word)
{
    if (!root)
        return NULL;

    int s = strcasecmp(word, root->data);
    if (s < 0)
        root->left = delete(root->left, word);
    else if (s > 0)
        root->right = delete(root->right, word);
    else // Node to delete found
    {
        if (!root->left || !root->right)
        {
            node *temp = root->left ? root->left : root->right;
            if (!temp) // No child
            {
                free(root->data);
                free(root);
                return NULL;
            }
            else // One child
            {
                node *toFree = root;
                root = temp;
                free(toFree->data);
                free(toFree);
            }
        }
        else
        {
            // Two children
            node *min = findMin(root->right);
            free(root->data);
            root->data = malloc(strlen(min->data) + 1);
            strcpy(root->data, min->data);
            root->right = delete(root->right, min->data);
        }
    }

    // Update height
    root->height = 1 + maxx(height(root->left), height(root->right));

    // Balance the tree
    root = balancer(root);

    return root;
}

void freeTree(node *r)
{
    if (!r)
        return;
    freeTree(r->left);
    freeTree(r->right);
    free(r->data);
    free(r);
}
// AVL Code
int maxx(int a, int b)
{
    return (a > b) ? a : b;
}
int height(node *n)
{
    if (!n)
        return 0;
    return n->height;
}
int getBalance(node *n)
{
    if (!n)
        return 0;
    return height(n->left) - height(n->right);
}
int count(node *root)
{
    if (!root)
        return 0;
    return 1 + count(root->left) + count(root->right);
}
node *balancer(node *root)
{
    int balance = getBalance(root);

    if (balance >= 2 && getBalance(root->left) >= 0) // LL violation
        return rightRotate(root);
    if (balance >= 2 && getBalance(root->left) < 0) // LR violation
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (balance <= -2 && getBalance(root->right) <= 0) // RR violation
        return leftRotate(root);
    if (balance <= -2 && getBalance(root->right) > 0) // RL violation
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}

node *leftRotate(node *n)
{
    node *x = n->right;
    node *T2 = x->left;

    x->left = n;
    n->right = T2;

    n->height = 1 + maxx(height(n->left), height(n->right));
    x->height = 1 + maxx(height(x->left), height(x->right));
    return x;
}

node *rightRotate(node *n)
{
    node *x = n->left;
    node *T2 = x->right;

    x->right = n;
    n->left = T2;

    n->height = 1 + maxx(height(n->left), height(n->right));
    x->height = 1 + maxx(height(x->left), height(x->right));
    return x;
}

node *insert(node *root, const char *word)
{
    if (!root)
        return newNode(word);
    if (strcasecmp(word, root->data) < 0)
        root->left = insert(root->left, word);
    else if (strcasecmp(word, root->data) > 0)
        root->right = insert(root->right, word);
    else
        return root; // word already exists

    root->height = 1 + maxx(height(root->left), height(root->right));

    int balance = getBalance(root);

    root = balancer(root);

    return root;
}
node *loadTree(char *filename)
{
    FILE *fp = fopen(filename, "r");
    if (!fp)
    {
        printf("Error opening file");
        return NULL;
    }

    char buffer[MAX];
    node *root = NULL;

    while (fgets(buffer, sizeof(buffer), fp)) // while fgets() is reading something
    {
        buffer[strcspn(buffer, "\n")] = '\0'; // Remove trailing newline
        root = insert(root, buffer);
    }

    fclose(fp);
    return root;
}
node *predecessor(node *root, node *target)
{
    node *r = root;
    node *p = NULL;
    if (!root || !target)
        return NULL;
    if (target->left)
        return findMax(target->left);
    else
    {
        while (r)
        {
            int s = strcasecmp(target->data, r->data);
            if (s > 0)
            {
                p = r;
                r = r->right;
            }
            else
            {
                r = r->left;
            }
        }
    }
    return p;
}
node *successor(node *root, node *target)
{
    node *r = root;
    node *p = NULL;
    if (!root || !target)
        return NULL;
    if (target->right)
        return findMin(target->right);
    else
    {
        while (r)
        {
            int s = strcasecmp(target->data, r->data);
            if (s < 0)
            {
                p = r;
                r = r->left;
            }
            else
            {
                r = r->right;
            }
        }
    }
    return p;
}
void toLowerStr(char *str) //makes a word lowercase
{
    for (int i = 0; str[i]; i++)
        str[i] = tolower(str[i]);
}
void checkDictionary(node *root, char *word)
{
    toLowerStr(word);
    node *lastvisited = NULL;
    node *found = searchBefore(root, word, &lastvisited);

    if (found)
        printf("-\"%s\"\t\tFound!\n", word);
    else
    {
        node *a = predecessor(root, lastvisited);
        node *b = successor(root, lastvisited);

        printf("-\"%s\"\tNot Found!\t", word);
        printf("Suggestions: ");
        if (lastvisited)
            printf("%s, ", lastvisited->data);
        if (a)
            printf("%s, ", a->data);
        if (b)
            printf("%s. \n", b->data);
    }
}

void func()
{
    char string[MAX], delim[] = " \n1234567890.,!@#$^&*()-=_+";
    node *root = loadTree("Dictionary.txt");
    printf("Welcome to the Spell-checking System\n\n");
    printf("Number of Nodes: %d\n", count(root));
    printf("Tree Height: %d\n", height(root));
    
    printf("\nEnter a sentence to search: ");
    fgets(string, sizeof(string), stdin);
    printf("\n");
    char *tok = strtok(string, delim);
    while (tok)
    {
        checkDictionary(root, tok);
        tok = strtok(NULL, delim);
    }
    freeTree(root);
}

int main()
{
    system("cls");
    func();
    return 0;
}
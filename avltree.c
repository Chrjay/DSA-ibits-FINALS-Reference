#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Node Structure
struct Node{
    int key;
    struct Node* left;
    struct Node* right;
    int height;
};

// Function to get the height of a Node
int getHeight(struct Node* n){
    if(n == NULL){
        return 0;
    }

    return n->height;
}

// Function to create a Node
struct Node* createNode(int key){
    struct Node* node = malloc(sizeof(struct Node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1; // Leaf Node = 1
}

// Function to get the max value
int max(int a, int b){ return (a > b) ? a : b; }

// Function to get balance factor of a node
int getBalanceFactor(struct Node* n){
    if(n == NULL){
        return 0;
    }

    return getHeight(n->left) - getHeight(n->right);
}


// SIMPLE ROTATIONS

// Right Rotation (y -> (L)t1 -> (R)t2 TO t1 -> (R)y -> (L)t2)
struct Node* rightRotate(struct Node* y){
    struct Node* t1 = y->left;
    struct Node* t2 = t1->right;

    t1->right = y;
    y->left = t2;
    
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    t1->height = max(getHeight(t1->left), getHeight(t1->right)) + 1;

    return t1;
}
// Left Rotation (x -> (R)t1 -> (L)t2 TO t1 -> (L)x -> (R)t2)
struct Node* leftRotate(struct Node* x){
    struct Node* t1 = x->right;
    struct Node* t2 = t1->left;

    t1->left = x;
    x->right = t2;
    
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    t1->height = max(getHeight(t1->left), getHeight(t1->right)) + 1;

    return t1;
}


// Function to Balance
struct Node* rebalance(struct Node* node){
    int balance = getBalanceFactor(node);

    // If the node is unbalanced, there are 4 possible scenarios of rotations
    // NOTE: bal > 1 = LEFT HEAVY ; bal < -1 = RIGHT HEAVY

    if(balance > 1){
        if(getBalanceFactor(node->left) < 0){
            node->left = leftRotate(node->left); // LR
        }
        return rightRotate(node); // LL
    }

    if(balance < -1){
        if(getBalanceFactor(node->right) > 0){
            node->right = rightRotate(node->right); // RL
        }
        return leftRotate(node); // RR
    }
    

    return node; // Node is already balanced
}

// Function to find the minimum value (Inorder Successor)
struct Node* minValue(struct Node* node){
    struct Node* current = node;

    while(current->left != NULL){
        current = current->left;
    }

    return current;
}

// Function for INSERTION
struct Node* insertkey(struct Node* node, int key){
    if(node == NULL){
        return createNode(key);
    }

    if(key < node->key){
        node->left = insertkey(node->left, key);
    }else if(key > node->key){
        node->right = insertkey(node->right, key);
    }else{
        return node;
    }

    node->height = 1 + max(getHeight(node->left), getHeight(node->right));

    return rebalance(node);
}

// Function for DELETION
struct Node* deleteKey(struct Node* node, int key){
    if(node == NULL){
        printf("==============================================\n");
        printf("Tree is Empty!\n");
        return node;
    }

    if(key < node->key){
        node->left = deleteKey(node->left, key);
    }else if(key > node->key){
        node->right = deleteKey(node->right, key);
    }else{
        if((node->left == NULL) || (node->right == NULL)){
            struct Node* temp = node->left ? node->left : node->right;

            if(temp == NULL){
                temp = node;
                node = NULL;
            }else{
                *node = *temp;
            }

            free(temp);
        }else{
            struct Node* temp = minValue(node->right);
            node->key = temp->key;
            node->right = deleteKey(node->right, temp->key);
        }
    }

    if(node == NULL){
        return node;
    }

    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;

    return rebalance(node);
}

// Function for finding a Value
void valFind(struct Node *node, int x){
    if(node != NULL){
        if(x > node->key){
            valFind(node->right, x);
        }else if(x < node->key){
            valFind(node->left, x);
        }else{
            printf("==============================================\n");
            printf("Value %d found at height %d\n", x, node->height);
        }
    }else{
        printf("==============================================\n");
        printf("Value not Found!\n");
    }
}

// Functions for Printing 
void inOrder(struct Node* root){
    if(!root) return;
    
    inOrder(root->left);
    printf("%d ", root->key);
    inOrder(root->right);
}  
void preOrder(struct Node* root){
    if(!root) return;

    printf("%d ", root->key);
    preOrder(root->left);
    preOrder(root->right);
}    
void postOrder(struct Node* root){
    if(!root) return;

    postOrder(root->left);
    postOrder(root->right);
    printf("%d ", root->key);
}

int main(void){
    struct Node* root = NULL;
    bool quit = false;
    int choices, temp;

    while(!quit){
        printf("==============================================\n");
        printf("What would you like to do?\n");
        printf("[1] Insert          [2] Find a value\n");
        printf("[3] Delete          [4] Print all Order\n");
        printf("[5] Exit\n");
        printf("==============================================\n= ");
        scanf(" %d", &choices);

        switch(choices){
            case 1:
                printf("==============================================\n");
                printf("Input a value: ");
                scanf("%d", &temp);
                
                root = insertkey(root, temp);

                printf("==============================================\n");
                printf("Value Successfully added\n");
                break;
            case 2:
                printf("==============================================\n");
                printf("Value to Find: ");
                scanf("%d", &temp);

                valFind(root, temp);
                break;
            case 3:
                printf("==============================================\n");
                printf("Delete a value: ");
                scanf("%d", &temp);

                root = deleteKey(root, temp);
                printf("==============================================\n");
                printf("Value Successfully deleted\n");
                break;
            case 4:
                printf("In Order: ");
                inOrder(root);
                printf("\n");

                printf("Pre Order: ");
                preOrder(root);
                printf("\n");

                printf("Post Order: ");
                postOrder(root);
                printf("\n");

                break;
            case 5:
                printf("==============================================\n");
                printf("Exiting....\n");
                printf("==============================================\n");

                quit = true;
                break;
            default:
                printf("==============================================\n");
                printf("Invalid Input!\n");

                
        }

    }


}



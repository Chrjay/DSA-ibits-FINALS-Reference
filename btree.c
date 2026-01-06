#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Minimum degree parameter (t).
// Minimum keys = t-1, Maximum keys = 2*t-1
#define T 3

// A B-Tree Node structure
struct BTreeNode {
    int *keys;              // Array of keys
    struct BTreeNode **C;   // Array of child pointers
    int n;                  // Current number of keys
    bool leaf;              // True if node is a leaf, False otherwise
};

// Function to create a new B-Tree node
struct BTreeNode* createNode(bool leaf) {
    struct BTreeNode* newNode = (struct BTreeNode*)malloc(sizeof(struct BTreeNode));
    
    // Allocate memory for maximum possible keys (2*T - 1)
    newNode->keys = (int*)malloc((2 * T - 1) * sizeof(int));
    
    // Allocate memory for maximum possible children (2*T)
    newNode->C = (struct BTreeNode**)malloc((2 * T) * sizeof(struct BTreeNode*));
    
    newNode->leaf = leaf;
    newNode->n = 0; // Initially 0 keys
    return newNode;
}

// Function to traverse the tree (In-order)
void traverse(struct BTreeNode* root) {
    if (root != NULL) {
        int i;
        for (i = 0; i < root->n; i++) {
            // If not leaf, traverse the child before printing key[i]
            if (!root->leaf) {
                traverse(root->C[i]);
            }
            printf(" %d", root->keys[i]);
        }
        // Print the subtree rooted with last child
        if (!root->leaf) {
            traverse(root->C[i]);
        }
    }
}

// Function to search for a key in the B-Tree
struct BTreeNode* search(struct BTreeNode* root, int k) {
    int i = 0;
    
    // Find the first key greater than or equal to k
    while (i < root->n && k > root->keys[i]) {
        i++;
    }

    // If the found key is equal to k, return this node
    if (i < root->n && root->keys[i] == k) {
        return root;
    }

    // If key is not found here and this is a leaf node
    if (root->leaf) {
        return NULL;
    }

    // Go to the appropriate child
    return search(root->C[i], k);
}

// Split the child y of node x. i is the index of y in x->C
void splitChild(struct BTreeNode* x, int i, struct BTreeNode* y) {
    // Create a new node z which will store (t-1) keys of y
    struct BTreeNode* z = createNode(y->leaf);
    z->n = T - 1;

    // Copy the last (t-1) keys of y to z
    for (int j = 0; j < T - 1; j++) {
        z->keys[j] = y->keys[j + T];
    }

    // Copy the last t children of y to z (if not leaf)
    if (!y->leaf) {
        for (int j = 0; j < T; j++) {
            z->C[j] = y->C[j + T];
        }
    }

    // Reduce the number of keys in y
    y->n = T - 1;

    // Since this node is going to have a new child,
    // create space of new child
    for (int j = x->n; j >= i + 1; j--) {
        x->C[j + 1] = x->C[j];
    }

    // Link the new child z to this node
    x->C[i + 1] = z;

    // A key of y will move to this node. Find location of
    // new key and move all greater keys one space ahead
    for (int j = x->n - 1; j >= i; j--) {
        x->keys[j + 1] = x->keys[j];
    }

    // Copy the middle key of y to this node
    x->keys[i] = y->keys[T - 1];

    // Increment count of keys in this node
    x->n = x->n + 1;
}

// Insert a key k into a non-full node x
void insertNonFull(struct BTreeNode* x, int k) {
    int i = x->n - 1;

    if (x->leaf) {
        // If true, the new key goes into this node
        // Find the location of new key and move all greater keys one place ahead
        while (i >= 0 && x->keys[i] > k) {
            x->keys[i + 1] = x->keys[i];
            i--;
        }

        // Insert the new key at found location
        x->keys[i + 1] = k;
        x->n = x->n + 1;
    } else {
        // If this node is not leaf, find the child which is going to have the new key
        while (i >= 0 && x->keys[i] > k) {
            i--;
        }

        // Check if the found child is full
        if (x->C[i + 1]->n == 2 * T - 1) {
            // If the child is full, then split it
            splitChild(x, i + 1, x->C[i + 1]);

            // After split, the middle key of C[i] goes up and
            // C[i] is splitted into two. See which of the two
            // is going to have the new key
            if (x->keys[i + 1] < k) {
                i++;
            }
        }
        insertNonFull(x->C[i + 1], k);
    }
}

// Main function to insert a new key in the B-Tree
// Note: We pass the address of root because root may change
void insert(struct BTreeNode** root, int k) {
    // If tree is empty
    if (*root == NULL) {
        *root = createNode(true);
        (*root)->keys[0] = k;
        (*root)->n = 1;
    } else {
        // If root is full, then tree grows in height
        if ((*root)->n == 2 * T - 1) {
            // Allocate memory for new root
            struct BTreeNode* s = createNode(false);

            // Make old root as child of new root
            s->C[0] = *root;

            // Split the old root and move 1 key to the new root
            splitChild(s, 0, *root);

            // New root has two children now. Decide which of the
            // two children is going to have new key
            int i = 0;
            if (s->keys[0] < k) {
                i++;
            }
            insertNonFull(s->C[i], k);

            // Change root
            *root = s;
        } else {
            // If root is not full, call insertNonFull for root
            insertNonFull(*root, k);
        }
    }
}

int main() {
    struct BTreeNode* root = NULL;

    printf("Inserting keys: 10, 20, 5, 6, 12, 30, 7, 17\n");
    insert(&root, 10);
    insert(&root, 20);
    insert(&root, 5);
    insert(&root, 6);
    insert(&root, 12);
    insert(&root, 30);
    insert(&root, 7);
    insert(&root, 17);

    printf("Traversal of the constructed tree is:\n");
    traverse(root);
    printf("\n");

    int keyToSearch = 6;
    if (search(root, keyToSearch) != NULL)
        printf("Key %d found in the tree.\n", keyToSearch);
    else
        printf("Key %d not found.\n", keyToSearch);

    keyToSearch = 15;
    if (search(root, keyToSearch) != NULL)
        printf("Key %d found in the tree.\n", keyToSearch);
    else
        printf("Key %d not found.\n", keyToSearch);

    return 0;
}
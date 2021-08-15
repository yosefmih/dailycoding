#include <stdio.h>
#include <stdlib.h>

typedef __uint32_t uint32_t;
struct Node {
    uint32_t key;
    struct Node *left;
    struct Node *right;
};
typedef struct Node Node;

void add(Node *root, uint32_t key) {
    if (key < root->key) {
        if (root->left != NULL) {
            add(root->left, key);
        } else {
            Node *node = (Node *)malloc(sizeof(Node));
            node->key = key;
            node->left = NULL;
            node->right = NULL;
            root->left = node; 
        }
    } else if (key > root->key) {
        if (root->right != NULL) {
            add(root->right, key);
        } else {
            Node *node = (Node *)malloc(sizeof(Node));
            node->key = key;
            node->left = NULL;
            node->right = NULL;
            root->right = node;
        }
    }
}

char *getIndentation(uint32_t depth) {
    char *indentation = malloc(2*depth+1);
    for (int i = 0; i < depth; i++) {
        indentation[i] = ' ';
        indentation[i + depth] = ' ';
    }
    indentation[2*depth] = 0;
    return indentation;
}

void printTree(Node *root, uint32_t depth) {
    if (root == NULL) {
        return;
    }
    if (depth <= 0) {
        depth = 1;
    }
    printf("%s %d\n", getIndentation(depth), root->key);
    printTree(root->left, depth-5);
    printTree(root->right, depth+5);
}

void mergeTwoBinaryTrees(Node *newRoot, Node *rootOne, Node *rootTwo) {
    newRoot->key = 0;
    Node *leftLeft = NULL;
    Node *leftRight = NULL;
    Node *rightRight = NULL;
    Node *rightLeft = NULL;
    Node *newNode;
    if (rootOne != NULL) {
        newRoot->key += rootOne->key;
        leftLeft = rootOne->left;
        leftRight = rootOne->right;
    }
    if (rootTwo != NULL) {
        newRoot->key += rootTwo->key;
        rightRight = rootTwo->right;
        rightLeft = rootTwo->left;
    }
    if (leftLeft != NULL || rightLeft != NULL) {
        newNode = (Node *)malloc(sizeof(Node));
        newNode->left = NULL;
        newNode->right = NULL;
        newRoot->left = newNode;
        mergeTwoBinaryTrees(newNode, leftLeft, rightLeft);
    }
    if (leftRight != NULL || rightRight != NULL) {
        newNode = (Node *)malloc(sizeof(Node));
        newNode->left = NULL;
        newNode->right = NULL;
        newRoot->right = newNode;
        mergeTwoBinaryTrees(newNode, leftRight, rightRight);
    }
}

uint32_t genRand(uint32_t max) {
    return rand()%max;
}

void test() {
    Node binaryTreeOne = {10, NULL, NULL};
    for (int i = 0; i < 8; ++i) {
        add(&binaryTreeOne, genRand(20));
        // printTree(&binaryTreeOne, 20);
    }
    Node binaryTreeTwo = {20, NULL, NULL};
    for (int i = 0; i < 10; ++i) {
        add(&binaryTreeTwo, genRand(50));
    }

    Node binaryTreeThree = {0, NULL, NULL};
    mergeTwoBinaryTrees(&binaryTreeThree, &binaryTreeOne, &binaryTreeTwo);
    printTree(&binaryTreeOne, 30);
    printf("\n");
    printTree(&binaryTreeTwo, 30);
    printf("\n");
    printTree(&binaryTreeThree, 30);
}

int main() {
    test();
    return 0;
}
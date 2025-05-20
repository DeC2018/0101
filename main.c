#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_NODES 1000

// Definition for a binary tree node.
struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
};

// Helper function to check if two trees are mirrors of each other
bool isMirror(struct TreeNode* t1, struct TreeNode* t2) {
    if (t1 == NULL && t2 == NULL) return true;
    if (t1 == NULL || t2 == NULL) return false;
    return (t1->val == t2->val)
        && isMirror(t1->left, t2->right)
        && isMirror(t1->right, t2->left);
}

// Main function to check if a tree is symmetric
bool isSymmetric(struct TreeNode* root) {
    if (root == NULL) return true;
    return isMirror(root->left, root->right);
}

// Helper function to create a new tree node
struct TreeNode* newNode(int val) {
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Helper function to parse input string like "[1,2,2,3,4,4,3]"
int parseInput(const char* s, char arr[][16], int* n) {
    int idx = 0, arr_idx = 0;
    char buf[16];
    int buf_idx = 0;
    while (s[idx]) {
        if (s[idx] == '[' || s[idx] == ']' || s[idx] == ' ' || s[idx] == '\n') {
            idx++;
            continue;
        }
        if (s[idx] == ',') {
            if (buf_idx > 0) {
                buf[buf_idx] = '\0';
                strcpy(arr[arr_idx++], buf);
                buf_idx = 0;
            }
            idx++;
            continue;
        }
        buf[buf_idx++] = s[idx++];
    }
    if (buf_idx > 0) {
        buf[buf_idx] = '\0';
        strcpy(arr[arr_idx++], buf);
    }
    *n = arr_idx;
    return arr_idx;
}

// Helper function to build a binary tree from an array of strings (level order, "null" for NULL)
struct TreeNode* buildTree(char arr[][16], int n) {
    if (n == 0 || strcmp(arr[0], "null") == 0) return NULL;
    struct TreeNode* nodes[MAX_NODES] = {0};
    int i, j = 1;
    nodes[0] = newNode(atoi(arr[0]));
    int front = 0, rear = 1;
    while (front < rear && j < n) {
        struct TreeNode* curr = nodes[front++];
        if (j < n && strcmp(arr[j], "null") != 0) {
            curr->left = newNode(atoi(arr[j]));
            nodes[rear++] = curr->left;
        }
        j++;
        if (j < n && strcmp(arr[j], "null") != 0) {
            curr->right = newNode(atoi(arr[j]));
            nodes[rear++] = curr->right;
        }
        j++;
    }
    return nodes[0];
}

// Helper function to free the memory of a tree
void deleteTree(struct TreeNode* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    free(root);
}

int main() {
    const char* inputs[] = {
        "[1,2,2,3,4,4,3]",
        "[1,2,2,null,3,null,3]"
    };
    int num_cases = sizeof(inputs) / sizeof(inputs[0]);

    for (int i = 0; i < num_cases; ++i) {
        printf("Input: root = %s\n", inputs[i]);

        char arr[MAX_NODES][16];
        int n = 0;

        parseInput(inputs[i], arr, &n);
        struct TreeNode* root = buildTree(arr, n);

        printf("Output: %s\n", isSymmetric(root) ? "true" : "false");

        deleteTree(root);
    }

    return 0;
}

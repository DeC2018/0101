#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    bool isSymmetric(TreeNode* root) {
        return isSymmetric(root, root);
    }

private:
    bool isSymmetric(TreeNode* p, TreeNode* q) {
        if (!p || !q)
            return p == q;

        return p->val == q->val &&
               isSymmetric(p->left, q->right) &&
               isSymmetric(p->right, q->left);
    }
};

// Helper function to build a binary tree from a level-order traversal
TreeNode* buildTree(const vector<string>& nodes) {
    if (nodes.empty() || nodes[0] == "null") return nullptr;

    TreeNode* root = new TreeNode(stoi(nodes[0]));
    queue<TreeNode*> q;
    q.push(root);

    int i = 1;
    while (!q.empty() && i < nodes.size()) {
        TreeNode* current = q.front();
        q.pop();

        if (i < nodes.size() && nodes[i] != "null") {
            current->left = new TreeNode(stoi(nodes[i]));
            q.push(current->left);
        }
        i++;

        if (i < nodes.size() && nodes[i] != "null") {
            current->right = new TreeNode(stoi(nodes[i]));
            q.push(current->right);
        }
        i++;
    }

    return root;
}

// Helper function to parse input string like "[1,2,2,3,4,4,3]"
vector<string> parseInput(const string& s) {
    vector<string> res;
    string t = s;
    t.erase(remove(t.begin(), t.end(), '['), t.end());
    t.erase(remove(t.begin(), t.end(), ']'), t.end());
    stringstream ss(t);
    string item;
    while (getline(ss, item, ',')) {
        // Remove whitespace
        item.erase(remove_if(item.begin(), item.end(), ::isspace), item.end());
        res.push_back(item);
    }
    return res;
}

// Helper function to delete a tree and free memory
void deleteTree(TreeNode* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {
    vector<string> inputs = {
        "[1,2,2,3,4,4,3]",
        "[1,2,2,null,3,null,3]"
    };

    Solution solution;

    for (const auto& input : inputs) {
        cout << "Input: root = " << input << endl;

        auto nodes = parseInput(input);
        TreeNode* root = buildTree(nodes);

        cout << "Output: " << (solution.isSymmetric(root) ? "true" : "false") << endl;

        deleteTree(root);
    }

    return 0;
}

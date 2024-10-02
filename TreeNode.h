#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct TreeNode {
    int GatorID;
    string name;
    int height;
    int balance_val = 0;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;

    //this constructor takes in a name and GatorID
    TreeNode(int ID, string n) : GatorID(ID), name(n) {}
};



class AVLTree {
    TreeNode* root;

    //recursive method to delete tree
    void deleteTree(TreeNode* curr) {
        if (!curr) {
            return;
        }

        deleteTree(curr->left);
        deleteTree(curr->right);
        delete curr;
    }

    int getHeight(TreeNode* node) {
        if (!node) {
            return 0;
        }
        return 1 + max(getHeight(node->left), getHeight(node->right));
    }

    int checkBalanceFactor(TreeNode* node) {
        //exception handling for nullptrs
        if (!node) {
            cout << "input is a nullptr" << endl;
        }

        return getHeight(node->left) - getHeight(node->right);
    }

    TreeNode* leftRotation(TreeNode* node) {
        //rotate nodes to balance tree
        TreeNode* new_head = node->right;
        TreeNode* temp = new_head->left;
        new_head->left = node;
        node->right = temp;

        // Update balance values
        node->balance_val = checkBalanceFactor(node);
        new_head->balance_val = checkBalanceFactor(new_head);

        // Update levels
        node->height = getHeight(node);
        new_head->height = getHeight(new_head);

        return new_head;
    }

    TreeNode* rightRotation(TreeNode* node) {
        //rotate nodes to balance tree
        TreeNode* new_head = node->left;
        TreeNode* temp = new_head->right;
        new_head->right = node;
        node->left = temp;

        // Update balance values
        node->balance_val = checkBalanceFactor(node);
        new_head->balance_val = checkBalanceFactor(new_head);

        // Update levels
        node->height = getHeight(node);
        new_head->height = getHeight(new_head);

        return new_head;
    }

    TreeNode* privateInsert(TreeNode* child, TreeNode* curr) {
        if (!curr) {
            //edge case for when tree has no nodes
            child->height = 1;
            cout << "successful" << endl;
            return child;
        }

        if (curr->GatorID == child->GatorID) { //case when ID already exists
            cout << "unsuccessful" << endl;

            //removes new node from memory
            delete child;
            return curr;
        }

        if (child->GatorID < curr->GatorID) {
            curr->left = privateInsert(child, curr->left);
        }
        else {
            curr->right = privateInsert(child, curr->right);
        }

        //recheck balance factor of current node
        curr->balance_val = checkBalanceFactor(curr);

        // Balance the tree
        if (curr->balance_val == 2) {
            if (curr->left && curr->left->balance_val == -1) {
                curr->left = leftRotation(curr->left);
            }
            return rightRotation(curr);
        }

        if (curr->balance_val == -2) {
            if (curr->right && curr->right->balance_val == 1) {
                curr->right = rightRotation(curr->right);
            }
            return leftRotation(curr);
        }

        curr->height = getHeight(curr);

        return curr;
    }

    //in order traversal; creates a vector with all the names
    void inOrderTraversal(TreeNode* curr, vector<string>& names) {
        if (!curr) {
            return;
        }

        inOrderTraversal(curr->left, names);
        names.push_back(curr->name);
        inOrderTraversal(curr->right, names);
    }

    TreeNode* inOrderTraversalSearch(TreeNode* curr_node, int N, int& curr_num) {
        if (!curr_node) {
            return nullptr;
        }

        // Traverse the left subtree
        curr_node->left = inOrderTraversalSearch(curr_node->left, N, curr_num);

        // Check if the current node is the N-th node
        if (curr_num == N) {
            // Delete this node
            TreeNode *node_to_delete = curr_node;

            if (curr_node->right && curr_node->left) {
                TreeNode *new_node = curr_node->right;

                while (new_node->left) {
                    if (!new_node->left->left) {
                        TreeNode *temp = new_node->left;
                        new_node->left = new_node->left->right;
                        new_node = temp;
                        break;
                    }
                    new_node = new_node->left;
                }

                new_node->left = curr_node->left;
                if (new_node != curr_node->right) {
                    new_node->right = curr_node->right;
                }
                curr_node = new_node;
            }

            else if (curr_node->right && !curr_node->left) {
                TreeNode *temp = curr_node->right;
                curr_node = temp;
            }

            else if (!curr_node->right && curr_node->left) {
                TreeNode *temp = curr_node->left;
                curr_node = temp;
            }

            else {
                curr_node = nullptr;
            }

            delete node_to_delete;
            curr_num += 1;
            cout << "successful" << endl;
            return curr_node;
        }

        else {
            curr_num += 1;
        }

        // Traverse the right subtree
        curr_node->right = inOrderTraversalSearch(curr_node->right, N, curr_num);

        return curr_node;
    }

    //pre order traversal; creates a vector with all the names
    void preOrderTraversal(TreeNode* curr, vector<string>& names) {
        if (!curr) {
            return;
        }

        names.push_back(curr->name);
        preOrderTraversal(curr->left, names);
        preOrderTraversal(curr->right, names);
    }


    //pre order traversal to search for people with specified name
    void preOrderTraversalSearch(TreeNode* curr, vector<int>& IDs, string person) {
        if (!curr) {
            return;
        }

        if (curr->name == person) {
            IDs.push_back(curr->GatorID);
        }
        preOrderTraversalSearch(curr->left, IDs, person);
        preOrderTraversalSearch(curr->right, IDs, person);
    }

    //post order traversal; creates vector with all names
    void postOrderTraversal(TreeNode* curr, vector<string>& names) {
        if (!curr) {
            return;
        }

        postOrderTraversal(curr->left, names);
        postOrderTraversal(curr->right, names);
        names.push_back(curr->name);
    }



    TreeNode* privateRemove(int ID, TreeNode* curr) {
        if (!curr) {
            cout << "unsuccessful" << endl;
            return nullptr;
        }

        if (ID < curr->GatorID) {
            curr->left = privateRemove(ID, curr->left);
        } else if (ID > curr->GatorID) {
            curr->right = privateRemove(ID, curr->right);
        } else {
            if (!curr->left) {
                TreeNode* temp = curr->right;
                delete curr;
                cout << "successful" << endl;
                return temp;
            } else if (!curr->right) {
                TreeNode* temp = curr->left;
                delete curr;
                cout << "successful" << endl;
                return temp;
            }

            // Node with two children: Get the inorder successor
            TreeNode* temp = minValueNode(curr->right);
            curr->GatorID = temp->GatorID;
            curr->name = temp->name;
            curr->right = privateRemove(temp->GatorID, curr->right);
        }

        if (!curr) return curr;

        curr->balance_val = checkBalanceFactor(curr);

        // Balance the node if it has become unbalanced
        if (curr->balance_val > 1 && checkBalanceFactor(curr->left) >= 0)
            return rightRotation(curr);

        if (curr->balance_val > 1 && checkBalanceFactor(curr->left) < 0) {
            curr->left = leftRotation(curr->left);
            return rightRotation(curr);
        }

        if (curr->balance_val < -1 && checkBalanceFactor(curr->right) <= 0)
            return leftRotation(curr);

        if (curr->balance_val < -1 && checkBalanceFactor(curr->right) > 0) {
            curr->right = rightRotation(curr->right);
            return leftRotation(curr);
        }

        return curr;
    }

    TreeNode* minValueNode(TreeNode* node) {
        TreeNode* curr = node;
        while (curr && curr->left) {
            curr = curr->left;
        }
        return curr;
    }

public:
    //initializes tree
    AVLTree() {
        root = nullptr;
    }

    void Insert(TreeNode* child) {
        root = privateInsert(child, root);
    }

    void Remove(int ID) {
        root = privateRemove(ID, root);
    }

    void IDSearch(int ID) {
        TreeNode* curr = root;

        while (curr) {
            //print associated name if ID is found
            if (curr->GatorID == ID) {
                cout << curr->name << endl;
                return;
            }

            else if (ID > curr->GatorID) {
                curr = curr->right;
            }

            else {
                curr = curr->left;
            }
        }

        cout << "unsuccessful" << endl;
    }

    void nameSearch(string name) {
        vector<int> IDs;

        preOrderTraversalSearch(root, IDs, name);

        if (IDs.empty()) {
            cout << "unsuccessful" << endl;
            return;
        }

        int last_index = IDs.size() - 1;

        //print out IDs with the searched name
        for (int i = 0; i < last_index; i++) {
            cout << IDs[i] << endl;
        }
        cout << IDs[last_index] << endl;
    }

    int getLevelCount() {
        return getHeight(root);
    }

    void printInOrder() {
        vector<string> names;
        inOrderTraversal(root, names);

        //edge case when no nodes
        if (names.size() == 0) {
            return;
        }

        int largest_index = names.size() - 1;
        for (int i = 0; i < largest_index; i++) {
            cout << names[i] << ", ";
        }

        cout << names[largest_index] << endl;
    }

    void printPreOrder() {
        vector<string> names;
        preOrderTraversal(root, names);

        //edge case when no nodes
        if (names.size() == 0) {
            return;
        }

        int largest_index = names.size() - 1;
        for (int i = 0; i < largest_index; i++) {
            cout << names[i] << ", ";
        }

        cout << names[largest_index] << endl;
    }

    void printPostOrder() {
        vector<string> names;
        postOrderTraversal(root, names);

        //edge case when no nodes
        if (names.size() == 0) {
            return;
        }

        int largest_index = names.size() - 1;
        for (int i = 0; i < largest_index; i++) {
            cout << names[i] << ", ";
        }

        cout << names[largest_index] << endl;
    }

    void removeInOrder(int N) {
        int curr_val = 0;
        root = inOrderTraversalSearch(root, N, curr_val);
        if (N > curr_val - 1) {
            cout << "unsuccessful" << endl;
        }
    }

    ~AVLTree() {
        //use postorder traversal to delete tree
        deleteTree(root);
    }
};
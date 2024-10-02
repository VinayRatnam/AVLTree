#pragma once
#include "TreeNode.h"
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

bool check_Valid_ID(string ID) {
    int len = ID.size();

    //ID has to be 8 digits
    if (len != 8) {
        return false;
    }

    for (int i = 0; i < len; i++) {
        //if one of the characters is not an integer, return false
        if (ID[i] < 48 || ID[i] > 57) {
            return false;
        }
    }
    return true;
}

bool check_Valid_Name(string& name) {
    int len = name.size();

    for (int i = 0; i < len; i++) {
        //if one of the characters is not a letter (or a space), return false
        if (!(name[i] >= 65 && name[i] <= 90) && !(name[i] >= 97 && name[i] <= 122)) {
            if (name[i] != 32) {
                return false;
            }
        }
    }
    return true;
}


void run_Command(string command, istringstream& line, AVLTree& Tree) {

    if (command == "insert") {
        //run code for insert command
        string name;
        string str_gatorID;
        int gatorID;


        //get name and ID
        getline(line, name, '"');
        getline(line, name, '"');
        getline(line, str_gatorID, ' ');
        getline(line, str_gatorID);


        //check if ID and name are valid
        if (!check_Valid_ID(str_gatorID)) {
            cout << "unsuccessful" << endl;
            return;
        }
        else {
            //convert ID to a num
            gatorID = stoi(str_gatorID);
        }

        if (!check_Valid_Name(name)) {
            cout << "unsuccessful" << endl;
            return;
        }

        //create and insert new node
        TreeNode* NewNode = new TreeNode(gatorID, name);
        Tree.Insert(NewNode);
    }

    else if (command == "remove") {
        //run code for remove command
        string str_gatorID;
        getline(line, str_gatorID);

        //check if ID number is valid
        if (!check_Valid_ID(str_gatorID)) {
            cout << "unsuccessful" << endl;
            return;
        }

        //remove node w/ ID
        Tree.Remove(stoi(str_gatorID));
    }

    else if (command == "search") {
        string name_or_ID;
        getline(line, name_or_ID);

        //runs if input is an ID
        if (check_Valid_ID(name_or_ID)) {
            int gatorID = stoi(name_or_ID);
            Tree.IDSearch(gatorID);
            return;
        }

        string potential_name = name_or_ID.substr(1, name_or_ID.size() - 2);
        //runs if input is a name
        if (check_Valid_Name(potential_name)) {
            Tree.nameSearch(potential_name);
        }

        else {
            cout << "unsuccessful" << endl;
        }
    }

    else if (command == "printInorder") {
        Tree.printInOrder();
    }

    else if (command == "printPreorder") {
        Tree.printPreOrder();
    }

    else if (command == "printPostorder") {
        Tree.printPostOrder();
    }

    else if (command == "printLevelCount") {
        cout << Tree.getLevelCount() << endl;
    }

    else if (command == "removeInorder") {
        string str_N;
        getline(line, str_N);

        //check if its a valid number
        for (int i = 0; i < str_N.size(); i++) {
            //if one of the characters is not an integer, print unsuccessful
            if (str_N[i] < 48 || str_N[i] > 57) {
                cout << "unsuccessful" << endl;
                return;
            }
        }

        Tree.removeInOrder(stoi(str_N));
    }

    else {
        cout << "unsuccessful" << endl;
        return;
    }
}


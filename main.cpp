#include <iostream>
#include "TreeNode.h"
#include "Commands.h"
#include <sstream>
#include <string>
using namespace std;


int main() {

    //get the number of commands
    string str_num_of_commands;
    getline(cin, str_num_of_commands);
    int num_of_commands = stoi(str_num_of_commands);

    AVLTree Tree;
    //run commands through a loop
    for (int i = 0; i < num_of_commands; i++) {
        string curr_input;
        getline(cin, curr_input);

        //get the current command
        istringstream curr_line(curr_input);
        string curr_command;
        getline(curr_line, curr_command, ' ');

        run_Command(curr_command, curr_line, Tree);
    }
}

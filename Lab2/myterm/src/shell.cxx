#include <iostream>
#include "command.h"
int main(){

    command cmd;
    do{
        if (!cmd.readline())
        {
            cmd.print_usage();
        }
        else{
// Our command class
// Read command from user
// Show usage
            cmd.execute();
        }
    } while (!cmd.exit_requested());
    return 0;
// Execute command
// Check for termination


}

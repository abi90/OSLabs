#include "command.h"
#include <iostream>
#include <boost/xpressive/xpressive.hpp>
#include <unistd.h>
#include <sys/wait.h>
#define CMD_REGEX "(\\.\\/)?(\\w+)[\\w\\d\\s\\.\\-\\\\\\/\\|\\@\\$\\>\\&]*$"

using namespace std;
using namespace boost::xpressive;

const sregex validatorRgx = sregex::compile(CMD_REGEX);
const sregex token = sregex::compile("[^\\s]+");

command::command()
: exit_requested_(false)
{
}

bool command::readline()
{
    string cmd;
    // TODO: Print prompt for the user.
    cout<<getlogin();
    cout<<" ";
    cout<<get_current_dir_name();
    cout<<" $ ";
    // Read line from user.
    getline(cin, cmd);
    this->history_.push_back(cmd);
    return this->parse_line(cmd);
}
void command::print_usage() const
{
    // TODO: Display usage format to user.
    cout<<"Myterm 1.0.0 "<<endl;
    cout<<"Usage: command [arguments]"<<endl;
    cout<<"help gives this help list"<<endl;
    cout<<"exit terminates Myterm"<<endl;
    cout<<"history gives the list of commands entered in Myterm"<<endl;
}
void command::execute()
{
    std::string cmd = this->parameters_[0];
    if (cmd == "exit")
    {
        this->exit_requested_ = true;
    }
    else if(cmd=="help")
    {
    	this->print_usage();
    }
    else if(cmd=="history")
    {
    	int index=0;
    	for (vector<string>::const_iterator iter = this->history_.begin(); iter != this->history_.end(); ++iter)
    	{
    		cout << index++ << " ";
    		cout << *iter << endl;
    	}
    }
    else
    {
        // TODO: Execute the command.
        // Hint: check execvp
        pid_t  pid=fork();
        if (pid == 0) 
        {
            vector<char *> argv(parameters_.size() + 1);
            for (int i = 0; i < parameters_.size(); i++)
            	argv[i] = &parameters_[i][0];
           
            execvp(argv[0], argv.data());
            exit(0);
        }
        else 
        {
            wait(NULL);
        }
    }
    this->parameters_.clear();
}

bool command::is_valid_command_line(const std::string& line) const
{
    // TODO: Compare line to valid command structure using regex
    // Hint: check boost::expressive::sregex
    return regex_match(line,validatorRgx);
}

bool command::parse_line(const std::string& line)
{
    // TODO: Parse command
    // Hint: check boost::expressive::sregex
    // boost::expressive::sregex_iterator
    bool result = is_valid_command_line(line);
    this->parameters_.clear();
    if(result)
    {
        sregex_iterator cur(line.begin(), line.end(), token);
        sregex_iterator end;
        for (; cur != end; ++cur)
        {
            this->parameters_.push_back(cur->str());
        }
    }
    return  result;
}

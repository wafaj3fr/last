# shell_prototype

This is a representation of a simple shell that replicates a linux based shell

## The shell

The shell is a command-line interface that acts as an intermediary between a user and the operating system. Its primary function is to interpret and execute user commands.

## How the shell works

### The following explains the process or steps that a shell goes through

- Displaying the prompt.
- Reading user input.
- Parsing the command. (Tokenization)
- Searching the command. (PATH)
- Creating a child process. (fork)
- Executing the command. (exec)
- Wait for the command completetion.
- Displaying output.
- Returning to the prompt.
- Exiting the shell.

## Content of this repository

- The header file that contains function prototypes.
- A function that handles execution of commands along with their arguments.
- A function that handles the PATH.
- A main source code file that is an entry point.

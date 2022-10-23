#  Linux Shell in C

## Introduction

This is an implementation of a Linux shell written in C language.


## Run the shell
1. Run the command `make`.
2. Run `./shell` to get a prompt of the form `username@system_name:path`.
3. Run any command in the shell. It can entail as many number of tabs and spaces, the shell accounts for those.
4. In order to exit, run `quit`.

### Description of the files
1. `main.c`  
This contains the main function of the program. The main function includes the primary shell-loop of the program and is responsible for executing other commands.

2. `prompt.c`  
Printing and Implementing the prompt of the shell.

3. `execute.c`
This calls each function and executes one by one that was given in input.

### Commands
1. `cd [file]`
- Changes directory to the directory specified, throws an error if the directory does not exist.
- Implemented in `cd.c`

2. `echo [arguments]`
 - Displays whatever is specified in [arguments]. 
 - Implemented in `echo.c`

3. `pwd`
- Displays the name of the working directory.
- Implemented in `pwd.c`

4. `ls [-l -a] [directory]`
- Lists all the files and directories in the specified directory in alphabetical order.
- Variations such as `ls, ls . , ls ..` also work.
- Also handles multiple directories as arguments. eg. `ls -l dir1 dir2 dir3`.
- Implemented in `ls.c`

5. `pinfo [PID]`
- Prints details about the process status, memory, and executable path.
- Just `pinfo` with no arguments gives details of the shell.
- Implemented in `pinfo.c`

6. `jobs`
- Prints a list of all currently running background processes spawned by the shell in
alphabetical order of the command name, along with their job number
- If the flag specified is -r, then print only the running processes else if the flag is -s then print the stopped
processes only.
- Implemented in `jobs.c`

7. `sig`
- Takes the job number of a running job and sends the signal corresponding to the
signal number to that process.
- Implemented in `sig.c`

8. `fg`
- Brings the running or stopped background job corresponding to job number to the foreground, and changes
its state to running.
- Throws an error if no job with the given job number exists.

9. `bg`
- Changes the state of a stopped background job to running (in the background).
- Throws an error if no background job corresponding to the given job number exists.

10. `quit`
- Exits the shell with return status as success 

### Signal Handling 

1. CTRL-Z
- Pushes any currently running foreground job into the background, and change its state from ‘running’ to ‘stopped.’
- Has no effect on the shell if there is no foreground process running.

2. CTRL-C
- Interrupts any currently running foreground job, by sending it the SIGINT signal.
- Has no effect on the shell if there is no foreground process running.

3. CTRL-D
- Logs you out of your shell, without having any effect on the actual terminal.


### Foreground and Background Processes

- All other commands are treated as system commands like emacs, vim etc.
- To run a process in the background, follow the command with a '&' symbol. Eg. `emacs &`.
- Upon termination of a background process, the shell prints its PID and exit status.
- Implemented in `fgbg.c`
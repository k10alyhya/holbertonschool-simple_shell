# Simple Shell

## Description

Simple Shell is a basic UNIX command interpreter written in C.

The project was developed as part of the Holberton School curriculum to understand how a shell works internally.

It reads commands from standard input, parses command arguments, searches for executable files using the `PATH` environment variable, creates child processes, and executes programs using `execve()`.

The shell supports both interactive and non-interactive modes.

## Features

- Interactive mode
- Non-interactive mode
- Command execution
- Commands with arguments
- Command search using `PATH`
- `exit` built-in command
- `env` built-in command
- End-of-file handling with `Ctrl+D`
- Basic error handling
- Leading and trailing space handling

## How It Works

The shell follows this basic flow:

```text
Read input
    |
    v
Remove extra spaces
    |
    v
Parse command and arguments
    |
    v
Check built-in commands
    |
    v
Search for command using PATH
    |
    v
fork()
    |
    +---- Child -> execve()
    |
    +---- Parent -> wait()
```

## Compilation

All files are compiled on Ubuntu 20.04 LTS using:

```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```

## Usage

### Interactive Mode

Run the shell:

```bash
./hsh
```

Example:

```text
$ ./hsh
$ ls
AUTHORS  README.md  execute_command.c  main.c  main.h  path.c
$ /bin/ls -l
$ exit
```

### Non-Interactive Mode

Commands can also be passed through standard input:

```bash
echo "/bin/ls" | ./hsh
```

Example:

```text
AUTHORS
README.md
execute_command.c
main.c
main.h
path.c
trim_spaces.c
```

Multiple commands can also be executed:

```bash
printf "/bin/ls\n/bin/pwd\n" | ./hsh
```

## Built-in Commands

### `exit`

Exits the shell.

Example:

```text
$ exit
```

### `env`

Displays the current environment variables.

Example:

```text
$ env
```

## PATH Handling

The shell searches for commands using the `PATH` environment variable.

For example:

```text
$ ls
```

The shell searches the directories listed in `PATH` until it finds the executable file.

Commands can also be executed directly using their full or relative path:

```text
$ /bin/ls
$ ./program
```

## Error Handling

If a command cannot be found, the shell displays an error message.

Example:

```text
$ command_that_does_not_exist
./hsh: 1: command_that_does_not_exist: not found
```

## Project Files

| File | Description |
| --- | --- |
| `main.c` | Main shell loop and input handling |
| `execute_command.c` | Parses and executes commands and built-ins |
| `path.c` | Searches for commands using `PATH` |
| `trim_spaces.c` | Removes leading and trailing spaces |
| `main.h` | Header file containing prototypes and includes |
| `man_1_simple_shell` | Manual page for the shell |
| `AUTHORS` | Lists project contributors |
| `README.md` | Project documentation |

## Requirements

- Ubuntu 20.04 LTS
- GCC
- Betty coding style
- No memory leaks
- Maximum of 5 functions per file
- Header files must use include guards

## Authors

- Abdullah Anas Almuqbali
- Khaled Fahd Alyahya

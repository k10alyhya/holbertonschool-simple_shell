# Simple Shell

## Description

Simple Shell is a basic UNIX command interpreter written in C.

The project helps us understand how a shell works, including reading user input, creating processes, executing programs, handling command arguments, searching for commands using `PATH`, and working with basic built-in commands.

## Features

The shell will support:

* Interactive and non-interactive modes
* Commands with arguments
* Command search using `PATH`
* `exit` built-in
* `env` built-in
* Error handling
* End-of-file (`Ctrl+D`)

## Compilation

```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```

## Usage

Run the shell with:

```bash
./hsh
```

Example:

```bash
$ ./hsh
$ ls
$ exit
```

## Authors

* Abdullah Anas Almuqbali
* Khaled Fahd Alyahya

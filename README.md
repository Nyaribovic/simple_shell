Simple UNIX shell components
Typically, a UNIX shell involves several components, including parsing and executing commands, 
managing environment variables, handling built-in commands, history, and more. Below is a list
of components which are part of such this project. The code is organized as categoried as 
indicated:
1.	Core Components:
•	main.c: The main entry point for your program.
•	shell.h: Header file containing function prototypes, data structures, and macros.
2.	Input and Parsing:
•	getLine.c: Functions to read input lines.
•	tokenizer.c: Tokenization of input commands.
•	parser.c: Parsing of tokens into command structures.
3.	Command Execution:
•	builtin.c and builtin1.c: Handling of built-in commands (e.g., cd, exit, echo).
•	environ.c: Managing environment variables.
•	vars.c: Variable handling (user-defined variables).
•	executes.c: Executing external programs.
4.	Error Handling:
•	errors.c and errors1.c: Error handling and reporting functions.
5.	Memory Management:
•	memory.c: Functions for memory allocation and deallocation.
6.	History and Command Lists:
•	history.c: Command history functionality.
•	lists.c and lists1.c: Data structures for managing lists of commands.
7.	String Handling:
•	string.c and string1.c: String manipulation functions.
8.	Additional Functionality:
•	getinfo.c: Collecting information about the system or commands.
•	realloc.c: Handling dynamic memory reallocation.
•	shell_loop.c: The main loop that repeatedly prompts the user for input.


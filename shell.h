#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH NULL 

/* for command chaining */
#define CMD_NORM        0
#define CMD_OR          1
#define CMD_AND         2
#define CMD_CHAIN       3

/* for convert_number() */
#define CONVERT_LOWERCASE       1
#define CONVERT_UNSIGNED        2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE       ".simple_shell_history"
#define HIST_MAX        4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: pointer
 */
 typedef struct liststr
{
        int num;
        char *str;
        struct liststr *next;
} list_t;

/**
 * struct passinfo - contains pseudo-arguments to pass into a function
 * @arg: a string generated from getline containing arguements
 * @argv:an array of strings generated from arg
 * @path: a string path for the current command
 * @argc: the argument
 * @line_count: the error
 * @err_num: the error code for exit()s
 * @linecount_flag: if on count this line of input
 * @fname: the program filename
 * @env: linked list local copy of environ
 * @environ: custom modified copy of environ from LL env
 * @history: the history node
 * @alias: the alias node
 * @env_changed: on if environ was changed
 * @status: the return status of the last exec'd command
 * @cmd_buf: address of pointer to cmd_buf
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: the fd from which to read line input
 * @histcount: the history line number count
 */
 typedef struct passinfo
{
        char *arg;
        char **argv;
        char *path;
        int argc;
        unsigned int line_count;
        int err_num;
        int linecount_flag;
        char *fname;
        list_t *env;
        list_t *history;
        list_t *alias;
        char **environ;
        int env_changed;
        int status;

        char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
        int cmd_buf_type; /* CMD_type ||, &&, ; */
        int readfd;
        int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
                0, 0, 0}

/**
 * struct builtin - contains a builtin string and related function
 * @type: the builtin command flag
 * @func: the function
 */
typedef struct builtin
{
        char *type;
        int (*func)(info_t *);
}
builtin_table;

/*custom_str.c*/

char *_custom_strncpy(char *dest, const char *src, size_t n);
char *_custom_strncat(char *dest, const char *src, size_t n);
char *_custom_strchr(const char *s, int c);

/*errors.c */

void _print_string(char *str);
int _write_character_stderr(int c);
int _write_character_fd(char c, int fd);
int _print_string_fd(char *str, int fd);

/*get_environment.c */

char **get_environ(info_t *info);
int _unsetenv(info_t *info, char *var);
int _setenv(info_t *info, char *var, char *value);

/*history_utils.c */

char *get_history_file(info_t *info);
char *read_history_from_file_internal(info_t *info, char *filename);
int write_history_to_file_internal(info_t *info, char *filename);

/*interactive.c*/

int interactive(info_t *info);
int is_delim(char c, char *delim);
int _isalpha(int c);
int _atoi(char *s);

/*main.c*/

int main(int argc, char **argv);
int open_input_file(const char *filename);
void initialize_environment(info_t *info);
int start_shell(info_t *info, char **argv);
int main_shell_loop(info_t *info, char **argv);

/*realloc.c */

char *_memset(char *s, char c, unsigned int n);
void free_string_array(char **str_array);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);

/*string.c*/

int _strlen(const char *s);
int _strcmp(const char *s1, const char *s2);
char *starts_with(const char *haystack, const char *needle);
char *_strcat(char *dest, const char *src);

/*builtin1.c  */

int print_history(info_t *info);
int unset_alias(info_t *info, char *alias);
int set_alias(info_t *info, char *alias);
int print_alias(list_t *node);

/*environment.c*/

int printEnvironment(info_t *info);
char *getEnvironmentValue(info_t *info, const char *name);
int setEnvironmentVariable(info_t *info);
int unsetEnvironmentVariable(info_t *info);
int populateEnvironmentList(info_t *info);

/*execution1.c */


char **split_path(const char *pathstr);
char *find_command_path(const char *pathstr, const char *cmd);

/*getinfo.c */

void clear_info(info_t *info);
void set_info(info_t *info, char **av);
void free_info(info_t *info, int all);

/*hsh.c */

int hsh(info_t *info, char **argv);
int find_builtin(info_t *info);
void find_cmd(info_t *info);
void fork_cmd(info_t *info);

/*linked_list.c */
list_t *add_node(list_t **head, const char *str, int num);
list_t *add_node_end(list_t **head, const char *str, int num);
void print_node_string(const list_t *node);
size_t print_list_strings(const list_t *head);
int delete_node_at_index(list_t **head, unsigned int index);

/*linked_list1.c */

size_t list_length(const list_t *h);
char **list_to_strings(list_t *head);
size_t print_linked_list(const list_t *h);
list_t *find_node_starts_with(list_t *node, char *prefix, char c);
ssize_t get_node_index(list_t *head, list_t *node);

/*memory.c */

int free_and_null(void **ptr);

/*tokenizer.c*/

static int count_words(const char *str, const char *delimiters);
static char **split_words(const char *str, const char *delimiters, int nmwords);
char **strtow(const char *str, const char *delimiters);

/*builtin.c*/

void print_error(info_t *info, const char *estr);
int exitShell(info_t *info);
int changeDirectory(info_t *info);
int helpCommand(info_t *info);

/*errors1.c*/

int string_to_int(char *s);
void print_error_message(info_t *info, char *error_type);
int print_line_number(int input, int fd);
void remove_comments(char *buf);
void _write_string_stderr(const char *str);

/*execution.c */

int is_executable(const char *path);
char *extract_path(const char *pathstr, int start, int stop);
char *create_full_path(const char *path, const char *cmd);
int is_command_executable(const char *path, const char *cmd);
char *find_command_in_path(const char *path, const char *cmd);

/*history.c */

int read_history_from_file(info_t *info, char *filename);
int build_history_list(info_t *info, char *buf, int line);
void handle_open_file_error(const char *prog_name, const char *file_name);
int read_command_history(info_t *info);

/*input.c */

ssize_t read_input_buffer(info_t *info, char **buf, size_t *len);
ssize_t get_input_line(info_t *info);
int custom_getline(info_t *info, char **ptr, size_t *length);
void sigintHandler(__attribute__((unused)) int sig_num);

/*linked_list.c*/

list_t *add_node(list_t **head, const char *str, int num);
list_t *add_node_end(list_t **head, const char *str, int num);
void print_node_string(const list_t *node);
size_t print_list_strings(const list_t *head);
void free_list(list_t **head);


/*string.c*/
int _strlen(const char *s);
int _strcmp(const char *s1, const char *s2);
char *starts_with(const char *haystack, const char *needle);
char *_strcat(char *dest, const char *src);


/*string1.c*/

char *string_copy(char *dest, const char *src);
char *string_duplicate(const char *str);
void string_print(const char *str);
int character_print(char c);

/*vars.c*/

int is_chain_delimiter(info_t *info, char *buf, size_t *p);
void continue_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len);
int replace_alias(info_t *info);
int replace_vars(info_t *info);
int replace_string(char **old, char *new);

#endif

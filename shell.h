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
#define BUF_FLUSH -1

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
} builtin_table;


/*main.c*/
int main(int argc, char **argv);
int open_input_file(const char *filename);
void initialize_environment(info_t *info);
int start_shell(info_t *info, char **argv);
int main_shell_loop(info_t *info, char **argv);


/*interactive.c*/
int interactive(info_t *info);
int is_delim(char c, char *delim);
int _isalpha(int c);
int _atoi(char *s);

/*memory.c*/
int free_and_null(void **ptr);

/*realloc.c*/
char *_memset(char *s, char c, unsigned int n);
void free_string_array(char **str_array);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);

/* shell_loop.c */
int shell_loop(char **);

/*errors.c*/
void _print_string(char *str);
int _write_character_stderr(char c);
int _write_character_fd(char c, int fd);
int _print_string_fd(char *str, int fd);


/*string1.c */
char *string_copy(char *dest, const char *src);
char *string_duplicate(const char *str);
void string_print(const char *str)
int character_print(char c)

/*custom_str.c */
char *_custom_strchr(const char __attribute__((unused)) *s, int __attribute__((unused))c);
char *_custom_strncpy(char *dest, const char *src, size_t n);
char *_custom_strncat(char *dest, const char *src, size_t n);



/*errors1.c */
int string_to_int(char *s);
void print_error_message(info_t *info, char *error_type);
int print_line_number(int input, int fd);
char *number_to_string(long int num, int base, int flags);
void remove_comments(char *buf);

/*builtin.c */
char *_getenv(info_t *info, const char *name);
int _setenv(info_t *info, const char *name, const char *value);
int exitShell(info_t *info);
int changeDirectory(info_t *info);
int helpCommand(info_t *info);


/*_builtin1.c */
int _myalias(info_t *info);
int print_alias(list_t *node);
int set_alias(info_t *info, char *alias);
int unset_alias(info_t *info, char *alias_name);
int print_history(info_t *info);



/*getline.c */
ssize_t read_input_buffer(info_t *info, char **buf, size_t *len);
void sigintHandler(__attribute__((unused)) int sig_num);
int custom_getline(info_t *info, char **ptr, size_t *length);
ssize_t get_input_line(info_t *info);

ssize_t handle_input(info_t *info, char **buf, size_t *len, ssize_t bytes_read);
void process_command_chain(info_t *info, char *cmd_chain_buffer, size_t *chain_start_pos, size_t current_pos, size_t buffer_len);
void reset_buffer_positions(size_t *current_pos, size_t *buffer_len, info_t *info);
ssize_t read_input_buffer(info_t *info, char **buf, size_t *len);
char *strchr(const char *s, int c);
void handle_memory_error(char *p);
void handle_buffer(info_t *info, char **p, char **new_p, size_t total_bytes_read, char *buffer_pos, size_t length);

/*get_environment.c*/
char **get_environ(info_t *info);
int _unsetenv(info_t *info, char *var);
int _setenv(info_t *info, char *var, char *value);


/*getinfo.c*/
void clear_info(info_t *info);
void set_info(info_t *info, char **av);
void free_info(info_t *info, int all);


/*getinfo.c*/
char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);

/*history_utils.c*/
char *get_history_file(info_t *info);
int write_history_to_file_internal(info_t *info, char *filename);
char *read_history_from_file_internal(info_t *info, char *filename);

/*history.c*/
int read_history_from_file(info_t *info, char *filename)
int build_history_list(info_t *info, char *buf, int linecount)

/* getenv.c 
int printEnvironment(info_t *info);
char *getEnvironmentValue(info_t *info, const char *name);
int populateEnvironmentList(info_t *info);
int setEnvironmentVariable(info_t *info);
int unsetEnvironmentVariable(info_t *info);*/




#endif

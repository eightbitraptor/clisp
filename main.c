#include <stdio.h>
#include <stdlib.h>
#include <editline/readline.h>
#include "extern/mpc/mpc.h"

int
run_repl()
{
    puts("clisp version 0.0.11");
    puts("Press Ctrl+c to exit");

    while(1) {
        char *line = readline("clisp> ");
        add_history(line);

        printf("clox> %s\n", line);
        free(line);
    }
}

int
run_file(char *path)
{
    return 0;
}

void
print_usage()
{
    puts("Usage: clisp <file>");
}

int 
main(int argc, char **argv)
{
    mpc_parser_t *number = mpc_new("number");
    mpc_parser_t *operator = mpc_new("operator");
    mpc_parser_t *expr = mpc_new("expr");
    mpc_parser_t *clisp = mpc_new("clisp");
    int status;

    mpca_lang(MPCA_LANG_DEFAULT,
              "number   : /-?[0-9]+/ ;                            "\
              "operator : '+' | '-' | '*' | '/' ;                 "\
              "expr     : <number> | '(' <operator> <expr>+ ')' ; "\
              "clisp    : /^/ <operator> <expr>+ /$/ ;            ",
              number, operator, expr, clisp);

    if (argc == 1) {
        status = run_repl();
    } else if (argc == 2) {
        status = run_file(argv[1]);
    } else {
        print_usage();
        status = 1;
    }

    mpc_cleanup(4, number, operator, expr, clisp);

    return status;
}

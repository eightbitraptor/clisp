#include <stdio.h>
#include <stdlib.h>
#ifdef __APPLE__
#include <editline/readline.h>
#else
#include <readline/readline.h>
#include <readline/history.h>
#endif
#include "extern/mpc/mpc.h"

#include "interpreter.h"

int
run_repl(mpc_parser_t *p)
{
    puts("clisp version 0.0.11");
    puts("Press Ctrl+c to exit");

    while(1) {
        mpc_result_t r;

        char *line = readline("clisp> ");
        add_history(line);

        if (mpc_parse("<stdin>", line, p, &r)) {
            // eval the AST on successful parse, and print the result
            long result = clisp_eval(r.output);
            printf("%li\n", result);
            mpc_ast_delete(r.output);
        } else {
            // on failure print the error
            mpc_err_print(r.error);
            mpc_err_delete(r.error);
        };


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
        status = run_repl(clisp);
    } else if (argc == 2) {
        status = run_file(argv[1]);
    } else {
        print_usage();
        status = 1;
    }

    mpc_cleanup(4, number, operator, expr, clisp);

    return status;
}

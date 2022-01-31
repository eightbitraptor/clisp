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

    if (argc == 1) {
        return run_repl();
    } else if (argc == 2) {
        return run_file(argv[1]);
    } else {
        print_usage();
        return 1;
    }
}


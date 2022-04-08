#include "interpreter.h"

static long
clisp_eval_operator(long x, char* op, long y)
{
    if (strcmp(op, "+") == 0) { return x + y; }
    if (strcmp(op, "-") == 0) { return x - y; }
    if (strcmp(op, "*") == 0) { return x * y; }
    if (strcmp(op, "/") == 0) { return x / y; }
    return 0;
}

long
clisp_eval(mpc_ast_t *node)
{
    /* If this node is a number, we know it has no children and can be returned directly */
    if (strstr(node->tag, "number")) {
        return atoi(node->contents);
    }

    /* second child is always the operator */
    char *op = node->children[1]->contents;
    /* grab the third child and store it */
    long x = clisp_eval(node->children[2]);

    /* iterate the remaining children to combine them */
    int i = 3;
    while (strstr(node->children[i]->tag, "expr")) {
        x = clisp_eval_operator(x, op, clisp_eval(node->children[i]));
        i++;
    }

    return x;
}

#ifndef CLISP_INTERPRETER_H
#define CLISP_INTERPRETER_H
#include "extern/mpc/mpc.h"

long clisp_eval(mpc_ast_t *node);

#endif /* CLISP_INTERPRETER_H */
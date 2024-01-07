#ifndef command_c
#define command_h

#include <stdio.h>
#include "input.h"
#include "db.h"

void commandExecution(dbObj **db, const char **input_splited, char **returnValue);

#endif

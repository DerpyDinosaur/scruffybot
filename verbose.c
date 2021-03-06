// Verbose
#include "verbose.h"

#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>

/*
    USAGE
        verbose("STRING `FORMAT`", 0);
        
    EXAMPLE
        verbose("This is verbose: %d", 0);
*/

bool Verbose = false;

void setVerbose(bool setting){
	Verbose = setting;
}

// TODO: Make verbose change colours
int verbose(const char * restrict format, ...){
    if( !Verbose ){return 0;}

    va_list args;
    va_start(args, format);
    int ret = vprintf(format, args);
    va_end(args);

    return ret;
}
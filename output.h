#ifndef __OUTPUT__
#define __OUTPUT__

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void init_output(FILE * f, char html);
void end_output(FILE *f, char html);

void print(FILE * f, char html, char * data, ...);
void print_html(FILE * f, char * data, va_list ap);
void print_raw(FILE * f, char * data, va_list ap);

void print_title(FILE * f, char html, char * data, ...);
void print_title_html(FILE * f, char * data, va_list ap);
void print_title_raw(FILE * f, char * data, va_list ap);

void print_nl(FILE * f, char html);

#endif

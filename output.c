#include "output.h"

void init_output(FILE * f, char html)
{
    if(html) {
        fprintf(f, "<!DOCTYPE html>\n");
        fprintf(f, "<html lang=\"en\">\n");
        fprintf(f, "<head>\n");
        fprintf(f, "<meta charset=\"utf-8\" />\n");
        fprintf(f, "<title>Config by merlyx</title>\n");
        fprintf(f, "</head><body>\n");
    }
}

void end_output(FILE * f, char html)
{
    if(html) {
        fprintf(f, "</body></html>");
    }
}

void print(FILE * f, char html, char * data, ...)
{
    va_list ap;
    va_start(ap, data);
    if(html) {
        print_html(f, data, ap);
    } else {
        print_raw(f, data, ap);
    }
    va_end(ap);
}

void print_html(FILE * f, char * data, va_list ap)
{
    fprintf(f, "<pre>");
    vfprintf(f, data, ap);
    fprintf(f, "</pre>\n");
}

void print_raw(FILE * f, char * data, va_list ap)
{
    vfprintf(f, data, ap);
    fprintf(f, "\n");
}

void print_title(FILE * f, char html, char * data, ...)
{
    va_list ap;
    va_start(ap, data);
    if(html) {
        print_title_html(f, data, ap);
    } else {
        print_title_raw(f, data, ap);
    }
    va_end(ap);
}

void print_title_html(FILE * f, char * data, va_list ap)
{
    fprintf(f, "<h2>");
    vfprintf(f, data, ap);
    fprintf(f, "</h2>\n");
}

void print_title_raw(FILE * f, char * data, va_list ap)
{
    fprintf(f, "\n ------ ");
    vfprintf(f, data, ap);
    fprintf(f, " ------\n");
}

void print_nl(FILE * f, char html)
{
    if(html) fprintf(f, "<br>");
    else fprintf(f, "\n");
}

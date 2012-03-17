#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define _HTML_OUTPUT_ index.html
#define _XML_OUTPUT_ config.xml

typedef enum{
	HTML,
	XML,
	UNKNOW
}typeOutput;
typeOutput type=UNKNOW;

FILE * output;

char * title = NULL;

//Cette fonction crée le fichier de sortie avec les balises header necessaire ainsi qu'un fichier de config utile pour les autres fonctions pour savoir si on est en mode html ou xml
int initOuput(FILE* out, typeOutput t){
	FILE * conf = fopen("output.conf", "w+");
	if(conf){
		fputc((int)t, conf);
		fclose(conf);
	}
	else{
		perror("fopen");
		return -1;
	}

	if(t == HTML){
		output = out;
		fputs("<!DOCTYPE html>", output);
		fputs("<html lang=\"en\">", output);
		fputs("<head>", output);
		fputs("<meta charset=\"utf-8\" />", output);
		fputs("<title>Config by merlyx</title>", output);
		fputs("</head><body>", output);
	}
	if(t == XML){
	}
	return 1;
}

void defineTitle(FILE * out, const char * t){
	if(type == UNKNOW){
		FILE * conf = fopen("output.conf", "r");
		if(conf){
			type = (typeOutput)fgetc(conf);
		}
		else
			type = XML;
	}
	output = out;

	if(title == NULL){
		strcpy(title, t);
		if(type == HTML)
			fputs(strcat(strcat("<div id=\"",title),"\">"), output);
		if(type == XML)
			fputs(strcat(strcat("<",title),">"), output);
	}else
		if(strcmp(title, t) != 0){
			free(title);
			strcpy(title, t);
			fputs(strcat(strcat(strcat(strcat("<", title),"><"),t),"\">"), output);
			strcpy(title, t);
		}
}

void setProp(const char * name, const char * value, const char * description){
	//
}
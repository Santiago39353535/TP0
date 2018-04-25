#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <ctype.h>

enum { INICIAL, PALABRA, ESPACIO };
enum { CONTAR_PALABRAS, CONTAR_LINEAS, CONTAR_LETRAS };

void contar_palabras(FILE* fp);
void contar_letras(FILE* fp);
void contar_lineas(FILE* fp);

int main(int argc, char* argv[]) {
  int version = 1;
  if (argc < 2) {
  	printf("Cantidad insuficiente de argumentos. \n");
        return  1;
  }
	
  if (argc > 4) {
  	printf("Cantidad excesiva de argumentos. \n");
  	return  1;
  }

  FILE* fp = NULL;

  if (argc > 2){
	  int c;
	  const char* short_opt = "Vhlwci:";
	  struct option long_opt[] = {
	    {"input",   required_argument,  NULL, 'i'},
	    {"version", no_argument,        NULL, 'V'},
	    {"help",    no_argument,        NULL, 'h'},
	    {"lines",   no_argument,        NULL, 'l'},
	    {"words",   no_argument,        NULL, 'w'},
	    {"chars",   no_argument,        NULL, 'c'},
    	    {NULL,      0,                  NULL,  0 }
  	    };
	
  	int funcion = 0;
  	int option_index = 0;
  	while((c = getopt_long(argc, argv, short_opt, long_opt, &option_index)) != -1) {
	
  	  switch(c) {
	
  	    case 'i':
  	      fp = fopen(optarg, "r");
  	          if (fp == NULL) {
  	            fputs("Error al abrir el archivo\n", stderr);
  	            return 1;
  	          }
  	          break;
	
  	    case 'V':
  	      printf("La versión es %d\n", version);
  	      return 0;
	
  	    case 'h':
  	      printf("Usage: \n");
  	      printf("       tp0 -h\n");
  	      printf("       tp0 -V\n");
  	      printf("       tp0 [options] file\n");
  	      printf("Options:\n");
  	      printf("         -V, --version   Print version and quit.\n");
  	      printf("         -h, --help      Print this information.\n");
  	      printf("         -l  --words     Print number of lines in file.\n");
  	      printf("         -w, --words     Print number of words in file.\n");
  	      printf("         -c, --words     Print number of characters in file.\n");
  	      printf("         -i, --input     Path to input file.\n");
  	      printf("Examples: \n\n");
  	      printf("          tp0 -w -i input.txt\n");
  	      return 0;
	
  	    case 'l':
  	      funcion = CONTAR_LINEAS;
  	      break;
	
  	    case 'c':
  	      funcion = CONTAR_LETRAS;
  	      break;
	
  	    case 'w':
  	      funcion = CONTAR_PALABRAS;
  	      break;
	
  	  }
  	}
	
  	switch(funcion) {
  	  case CONTAR_LINEAS:
  	    contar_lineas(fp);
  	    break;
  	  case CONTAR_PALABRAS:
  	    contar_palabras(fp);
  	    break;
  	  case CONTAR_LETRAS:
  	    contar_letras(fp);
  	    break;
  	}
  } else {
	fp = fopen(argv[1], "r");
  	if (fp == NULL) {
  	   fputs("Error al abrir el archivo\n", stderr);
  	   return 1;
  	}
	contar_lineas(fp);
	contar_palabras(fp);
	contar_letras(fp);	
  }
  
  fclose(fp);
  return 0;

}

void contar_palabras(FILE* fp) {
  rewind(fp);
  int c;
  int estado = INICIAL;
  int palabras = 0;

  c = fgetc(fp);
  while (c != EOF) {
    switch (estado) {

      case INICIAL:
        palabras = 0;
        if (!isspace(c)) {
            palabras++;
            estado = PALABRA;
        } else {
          estado = ESPACIO;
        }
        break;

      case PALABRA:
        if (isspace(c)) {
          estado = ESPACIO;
        }
        break;

      case ESPACIO:
        if (!isspace(c)) {
          palabras++;
          estado = PALABRA;
        }

    }
    c = fgetc(fp);
  }

  printf ("La cantidad de palabras es %d\n", palabras);
}

void contar_letras(FILE* fp) {
  int letras = 0;
  rewind(fp);
  while (!feof(fp)) {
    char a = fgetc(fp);
    if(a != ' ' || a != '\n' || a != '.' || a != '\0') {
      letras++;
    }
  }
  letras--;
  printf("La cantidad de letras es: %d\n", letras);
}

void contar_lineas(FILE* fp) {
  int lineas = 0;
  rewind(fp);
  while(!feof(fp)) {
    char a = fgetc(fp);
    if(a == '\n') {
     lineas++;
    }
  }
  printf("La cantidad de lineas es: %d\n", lineas);
}

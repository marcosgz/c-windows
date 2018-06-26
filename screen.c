#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct screen {
	char** matriz;
	int rows;
	int columns;
};
typedef struct screen Screen;

struct screenPosition {
	int x;
	int y;
};
typedef struct screenPosition ScreenPosition;

void readScreen(char filename[], Screen* s);
void memAllocScreen(Screen* s);
void memFreeScreen(Screen* s);
void showScreen(Screen* s);
void promptScreen(Screen* s, ScreenPosition *p, char output[]);
void updateScreenStr(Screen* s, ScreenPosition *p, char output[]);
void updateScreenInt(Screen* s, ScreenPosition *p, int number);

void readScreen(char filename[], Screen* s) {
	int i = 0;
	FILE* f;
	f = fopen(filename, "r");
	if(f == 0) {
		printf("Erro na leitura da tela");
		exit(1);
	}

	fscanf(f, "%d %d", &(s->rows), &(s->columns));
	memAllocScreen(s);

	for(i = 0; i < s->rows; i++) {
		fscanf(f, " %[^\n]s", s->matriz[i]);
	}

	fclose(f);
}

void memAllocScreen(Screen* s) {
	int i = 0;
	s->matriz = malloc(sizeof(char*) * s->rows);

	for(i = 0; i < s->rows; i++) {
		s->matriz[i] = malloc(sizeof(char) * s->columns + 1);
	}
}

void memFreeScreen(Screen* s) {
	int i = 0;
	for(i = 0; i < s->rows; i++) {
		free(s->matriz[i]);
	}

	free(s->matriz);
}

void showScreen(Screen* s) {
	clear();
	int i = 0;
	for(i = 0; i < s->rows; i++) {
		printf("%s\n", s->matriz[i]);
	}
}

void promptScreen(Screen* s, ScreenPosition *p, char output[]) {
	// Mover o cursor no inicio indicando o campo a ser digitado
	int x = p->x;
	s->matriz[p->y][x] = INPUT_CHAR;
	showScreen(s);
	scanf(" %[^\n]s", output);
	p->x = x;
	updateScreenStr(s, p, output);
	// Exibe a matriz atualizada
	showScreen(s);
}

void updateScreenStr(Screen* s, ScreenPosition *p, char* output) {
	int i = 0, len = 0;
	len = stringLength(output);
	// Atualiza a matriz com o que o usuario digitou
	for(i = 0; i < len; i++) {
		s->matriz[p->y][p->x + i] = output[i];
	}
}

void updateScreenInt(Screen* s, ScreenPosition *p, int number) {
	char buffer[80] = "buffer";
	sprintf(buffer, "%d", number);
	updateScreenStr(s, p, buffer);
}

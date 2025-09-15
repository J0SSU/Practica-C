#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Definición de la estructura que simula la clase CifradoCesar
typedef struct {
    int desplazamiento; // K
    int totalLetras;    // T
    char alfabeto[100]; // arreglo para el alfabeto
} CifradoCesar;

// Constructor "simulado"
CifradoCesar* crearCifradoCesar(int desplazamiento, const char* alfabeto) {
    CifradoCesar* cesar = (CifradoCesar*)malloc(sizeof(CifradoCesar));
    cesar->desplazamiento = desplazamiento;
    strcpy(cesar->alfabeto, alfabeto);
    cesar->totalLetras = strlen(alfabeto);
    return cesar;
}

// Método para cifrar
void cifrar(CifradoCesar* cesar, const char* texto, char* resultado) {
    int i, j;
    int lenTexto = strlen(texto);
    int total = cesar->totalLetras;

    for (i = 0; i < lenTexto; i++) {
        char c = texto[i];
        char* posPtr = strchr(cesar->alfabeto, c); // busca el char en alfabeto
        if (posPtr != NULL) {
            int pos = posPtr - cesar->alfabeto;
            int nuevaPos = (pos + cesar->desplazamiento) % total;
            resultado[i] = cesar->alfabeto[nuevaPos];
        } else {
            resultado[i] = c; // deja igual caracteres que no están en el alfabeto
        }
    }
    resultado[lenTexto] = '\0'; // terminador
}

// Método para descifrar
void descifrar(CifradoCesar* cesar, const char* texto, char* resultado) {
    int i;
    int lenTexto = strlen(texto);
    int total = cesar->totalLetras;

    for (i = 0; i < lenTexto; i++) {
        char c = texto[i];
        char* posPtr = strchr(cesar->alfabeto, c);
        if (posPtr != NULL) {
            int pos = posPtr - cesar->alfabeto;
            int nuevaPos = (pos - cesar->desplazamiento + total) % total;
            resultado[i] = cesar->alfabeto[nuevaPos];
        } else {
            resultado[i] = c;
        }
    }
    resultado[lenTexto] = '\0';
}

// Programa principal
int main() {
    int K = 3;
    const char* alfabeto = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

    CifradoCesar* cesar = crearCifradoCesar(K, alfabeto);

    char texto[200];
    char cifrado[200];
    char descifrado[200];

    printf("Texto a cifrar: ");
    fgets(texto, sizeof(texto), stdin);
    texto[strcspn(texto, "\n")] = '\0'; // quitar salto de línea

    cifrar(cesar, texto, cifrado);
    descifrar(cesar, cifrado, descifrado);

    printf("Texto cifrado: %s\n", cifrado);
    printf("Texto descifrado: %s\n", descifrado);

    free(cesar); // liberar memoria
    return 0;
}

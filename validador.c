#include <stdio.h>
#include <string.h>
#include <stdbool.h>
//LEE EL README.md PARA MAS INFORMACION SOBRE EL PROYECTO

// Funcion 1 
bool esCaracterVocal(char caracter) {
    return caracter == 'a' || caracter == 'e' || caracter == 'i' || caracter == 'o' || caracter == 'u';
}

// Funcion 2
bool contieneConsonanteOclusiva(const char* textoClave) {
    const char consonantesOclusivas[] = "ptkbdg";
    for (int i = 0; textoClave[i] != '\0'; i++) {
        for (int j = 0; consonantesOclusivas[j] != '\0'; j++) {
            if (textoClave[i] == consonantesOclusivas[j]) {
                return true;
            }
        }
    }
    return false;
}

// Funcion 3
bool tieneVocalesYConsonantesIntercaladas(const char* textoClave) {
    for (int i = 1; textoClave[i] != '\0'; i++) {
        if (esCaracterVocal(textoClave[i]) == esCaracterVocal(textoClave[i - 1])) {
            return false;
        }
    }
    return true;
}

// Funcion 4
bool noTieneLetrasIgualesConsecutivasSalvoAAoII(const char* textoClave) {
    for (int i = 1; textoClave[i] != '\0'; i++) {
        if (textoClave[i] == textoClave[i - 1]) {
            if (!(textoClave[i] == 'a' || textoClave[i] == 'i')) {
                return false;
            }
        }
    }
    return true;
}

// Funcion 5
void limpiarFinDeLinea(char* texto) {
    size_t longitud = strlen(texto);
    while (longitud > 0 && (texto[longitud - 1] == '\n' || texto[longitud - 1] == '\r')) {
        texto[--longitud] = '\0';
    }
}

// Funcion 6
bool esClaveAceptable(const char* textoClave) {
    return contieneConsonanteOclusiva(textoClave) &&
           tieneVocalesYConsonantesIntercaladas(textoClave) &&
           noTieneLetrasIgualesConsecutivasSalvoAAoII(textoClave);
}

// Funcion prinncippal

int main() {
    FILE* archivoEntradaClaves = fopen("claves.txt", "r");
    FILE* archivoSalidaResultados = fopen("revisadas.txt", "w");

    if (!archivoEntradaClaves || !archivoSalidaResultados) {
        printf("Error al abrir los archivos.\n");
        return 1;
    }

    char textoClaveActual[25]; 

    while (fgets(textoClaveActual, sizeof(textoClaveActual), archivoEntradaClaves)) {
        limpiarFinDeLinea(textoClaveActual);

        if (strcmp(textoClaveActual, "end") == 0) {
            break;
        }

        if (esClaveAceptable(textoClaveActual)) {
            fprintf(archivoSalidaResultados, "<%s> Es aceptable.\n", textoClaveActual);
        } else {
            fprintf(archivoSalidaResultados, "<%s> No es aceptable.\n", textoClaveActual);
        }
    }

    fclose(archivoEntradaClaves);
    fclose(archivoSalidaResultados);
    printf("Verificacion de contras ! Exitosa.\n");
    
    return 0;
}

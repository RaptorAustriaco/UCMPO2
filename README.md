# 🔐 Proyecto: Validador de Contraseñas “Pronunciables y Seguras”

### 📘 Curso: Programación II  
### 🏫 Universidad Católica del Maule – 2025  
### 👨‍🏫 Profesor: Hugo Araya Carrasco

---

## 📖 Descripción

Este proyecto implementa un validador de contraseñas seguras y fáciles de pronunciar, de acuerdo con tres reglas específicas. Está escrito en lenguaje C, usando modularidad, validación de cadenas y manejo de archivos.

El programa:

- Lee contraseñas desde un archivo de entrada `claves.txt`.
- Evalúa cada contraseña según tres reglas.
- Escribe los resultados en `revisadas.txt`.

---

## 📁 Archivos incluidos

| Archivo          | Descripción                                                 |
|------------------|-------------------------------------------------------------|
| `validador.c`    | Código fuente en lenguaje C                                 |
| `claves.txt`     | Archivo de entrada con una contraseña por línea             |
| `revisadas.txt`  | Archivo de salida generado con el resultado de cada clave   |

---

## ✅ Reglas de validación

Una contraseña es aceptable si:

1. Contiene al menos una **consonante oclusiva** (`p`, `t`, `k`, `b`, `d`, `g`).
2. Tiene **vocales y consonantes intercaladas** (una tras otra).
3. **No tiene letras iguales consecutivas**, excepto `aa` o `ii`.

---

## 🧠 Variables clave

| Variable                     | Tipo         | Significado                                            |
|------------------------------|--------------|--------------------------------------------------------|
| `caracter`                   | `char`       | Letra individual evaluada                              |
| `textoClave`                 | `const char*`| Cadena completa de una contraseña                      |
| `textoClaveActual`           | `char[]`     | Línea leída desde el archivo                           |
| `consonantesOclusivas[]`     | `char[]`     | Letras que deben estar presentes                       |
| `archivoEntradaClaves`       | `FILE*`      | Archivo de entrada (`claves.txt`)                      |
| `archivoSalidaResultados`    | `FILE*`      | Archivo de salida (`revisadas.txt`)                    |
| `i`, `j`, `longitud`         | `int`, `size_t` | Contadores y manejo de longitud                      |

---

## 🔍 Estructura de funciones

### `bool esCaracterVocal(char caracter)`
Verifica si el carácter es una vocal (`a`, `e`, `i`, `o`, `u`).

### `bool contieneConsonanteOclusiva(const char* textoClave)`
Evalúa si la cadena contiene alguna de las letras oclusivas requeridas.

### `bool tieneVocalesYConsonantesIntercaladas(const char* textoClave)`
Comprueba que no existan dos vocales o dos consonantes consecutivas.

### `bool noTieneLetrasIgualesConsecutivasSalvoAAoII(const char* textoClave)`
Detecta letras duplicadas seguidas y solo permite `aa` o `ii`.

### `void limpiarFinDeLinea(char* texto)`
Limpia los saltos de línea (`\n`, `\r`) al final de cada línea leída.

### `bool esClaveAceptable(const char* textoClave)`
Combina las tres reglas anteriores para determinar si una clave es aceptable.

---

## 🧾 Explicación paso a paso del `main`

```c
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

    return 0;
}
```

---

## 🚀 Cómo compilar y ejecutar

```bash
gcc validador.c -o validador
./validador
```

---

## 🧪 Ejemplo de ejecución

### Entrada (`claves.txt`)
```
k
boda
wiinap
aap
hugo
end
```

### Salida (`revisadas.txt`)
```
<k> Es aceptable.
<boda> Es aceptable.
<wiinap> Es aceptable.
<aap> Es aceptable.
<hugo> Es aceptable.
```

---

## 📌 Licencia

Este proyecto es educativo y fue desarrollado con fines académicos.  
Universidad Católica del Maule – 2025.

# Proyecto: Validador de Contraseñas "Pronunciables y Seguras"

### Curso: Programación II


---

## 🔖 Descripción General

Este proyecto consiste en desarrollar un programa en lenguaje C que permita evaluar si una serie de contraseñas contenidas en un archivo cumplen con criterios de seguridad definidos. Las contraseñas deben ser fáciles de pronunciar y a la vez seguras.

El programa debe leer un archivo llamado `claves.txt`, validar cada contraseña y escribir los resultados en `revisadas.txt`.

---

## 🗂️ Archivos involucrados

| Archivo         | Descripción                                              |
| --------------- | -------------------------------------------------------- |
| `validador.c`   | Archivo con el código fuente en lenguaje C               |
| `claves.txt`    | Archivo de entrada con una contraseña por línea          |
| `revisadas.txt` | Archivo de salida con los resultados "Es aceptable" o no |

---

## 🔍 Requisitos del Proyecto

1. **Lectura de datos desde archivo `claves.txt`.**
2. **Validación de contraseñas según 3 reglas:**

   * Debe contener al menos una **consonante oclusiva**: `p`, `t`, `k`, `b`, `d`, `g`.
   * Debe tener **vocales y consonantes intercaladas**.
   * No debe tener letras iguales seguidas, excepto `aa` o `ii`.
3. **Escritura de resultados en `revisadas.txt`.**
4. **Uso de funciones para modularidad.**
5. **Variables con nombres explicativos.**
6. **Buena organización del código y comentarios.**

---

## 📊 Variables usadas

| Variable                  | Tipo             | Significado                                           |
| ------------------------- | ---------------- | ----------------------------------------------------- |
| `caracter`                | `char`           | Letra que se está evaluando en una función            |
| `textoClave`              | `const char*`    | Clave completa que se está evaluando                  |
| `consonantesOclusivas`    | `char[]`         | Arreglo que contiene las consonantes oclusivas        |
| `textoClaveActual`        | `char[]`         | Almacena temporalmente cada línea del archivo         |
| `archivoEntradaClaves`    | `FILE*`          | Apuntador al archivo `claves.txt` (modo lectura)      |
| `archivoSalidaResultados` | `FILE*`          | Apuntador al archivo `revisadas.txt` (modo escritura) |
| `i`, `j`, `longitud`      | `int` / `size_t` | Variables de control para bucles                      |

---

## 🧩 Explicación línea por línea de funciones

### Función 1: `esCaracterVocal`

```c
bool esCaracterVocal(char caracter) {
    return caracter == 'a' || caracter == 'e' || caracter == 'i' || caracter == 'o' || caracter == 'u';
}
```

* Verifica si una letra es una vocal. Retorna verdadero si lo es.

---

### Función 2: `contieneConsonanteOclusiva`

```c
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
```

* Recorre la clave y busca alguna consonante oclusiva.
* Si encuentra una, retorna `true`. Si no, retorna `false`.

---

### Función 3: `tieneVocalesYConsonantesIntercaladas`

```c
bool tieneVocalesYConsonantesIntercaladas(const char* textoClave) {
    for (int i = 1; textoClave[i] != '\0'; i++) {
        if (esCaracterVocal(textoClave[i]) == esCaracterVocal(textoClave[i - 1])) {
            return false;
        }
    }
    return true;
}
```

* Verifica que no haya dos letras del mismo tipo seguidas.
* Si encuentra dos vocales o dos consonantes seguidas, retorna `false`.

---

### Función 4: `noTieneLetrasIgualesConsecutivasSalvoAAoII`

```c
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
```

* Rechaza letras repetidas seguidas, excepto si son `a` o `i`.

---

### Función 5: `limpiarFinDeLinea`

```c
void limpiarFinDeLinea(char* texto) {
    size_t longitud = strlen(texto);
    while (longitud > 0 && (texto[longitud - 1] == '\n' || texto[longitud - 1] == '\r')) {
        texto[--longitud] = '\0';
    }
}
```

* Elimina los saltos de línea y retorno de carro (`\n` y `\r`) al final de cada línea.

---

### Función 6: `esClaveAceptable`

```c
bool esClaveAceptable(const char* textoClave) {
    return contieneConsonanteOclusiva(textoClave) &&
           tieneVocalesYConsonantesIntercaladas(textoClave) &&
           noTieneLetrasIgualesConsecutivasSalvoAAoII(textoClave);
}
```

* Evalúa la contraseña usando las tres reglas anteriores.
* Retorna `true` solo si todas las condiciones se cumplen.

---

### Función principal: `main()`

```c
int main() {
    FILE* archivoEntradaClaves = fopen("claves.txt", "r");
    FILE* archivoSalidaResultados = fopen("revisadas.txt", "w");
```

* Abre el archivo de entrada para lectura.
* Abre el archivo de salida para escritura.

```c
    if (!archivoEntradaClaves || !archivoSalidaResultados) {
        printf("Error al abrir los archivos.\n");
        return 1;
    }
```

* Verifica que ambos archivos se hayan abierto correctamente. Si no, muestra error y finaliza.

```c
    char textoClaveActual[25];
```

* Declara un arreglo para almacenar la línea actual del archivo.

```c
    while (fgets(textoClaveActual, sizeof(textoClaveActual), archivoEntradaClaves)) {
        limpiarFinDeLinea(textoClaveActual);
```

* Lee cada línea del archivo y elimina los caracteres de salto de línea.

```c
        if (strcmp(textoClaveActual, "end") == 0) {
            break;
        }
```

* Si la línea es "end", finaliza el ciclo de lectura.

```c
        if (esClaveAceptable(textoClaveActual)) {
            fprintf(archivoSalidaResultados, "<%s> Es aceptable.\n", textoClaveActual);
        } else {
            fprintf(archivoSalidaResultados, "<%s> No es aceptable.\n", textoClaveActual);
        }
    }
```

* Evalúa si la clave es aceptable o no, y escribe el resultado correspondiente en el archivo de salida.

```c
    fclose(archivoEntradaClaves);
    fclose(archivoSalidaResultados);
    return 0;
}
```

* Cierra ambos archivos y termina el programa correctamente.

---

## 📥 Ejemplo de entrada y salida

### Entrada (`claves.txt`):

```
k
boda
wiinap
aap
hugo
end
```

### Salida (`revisadas.txt`):

```
<k> Es aceptable.
<boda> Es aceptable.
<wiinap> Es aceptable.
<aap> Es aceptable.
<hugo> Es aceptable.
```

---



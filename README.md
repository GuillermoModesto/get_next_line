*Este proyecto ha sido creado como parte del currículo de 42 por guantino.*

# get_next_line

## 📘 Descripción

**get_next_line** es una función diseñada para leer un archivo **línea a línea**, devolviendo en cada llamada la siguiente línea completa, incluyendo el carácter de salto de línea `\n` si está presente.  

El objetivo del proyecto es comprender la gestión de memoria dinámica, el manejo de buffers, el control de lectura en archivos y la implementación de un algoritmo capaz de mantener un estado persistente entre llamadas consecutivas sin utilizar variables globales accesibles externamente.

Esta implementación soporta:

- Lectura línea a línea desde un *file descriptor*.
- Manejo de buffers dinámicos.
- Almacenamiento persistente de la parte no consumida entre llamadas.
- Funcionamiento seguro ante errores o lecturas parciales.

---

## 🛠️ Instrucciones

### ✔️ Compilación

El proyecto requiere incluir `get_next_line.c`, `get_next_line_utils.c` y el archivo de cabecera `get_next_line.h`.

Ejemplo de compilación manual:

```bash
cc -Wall -Wextra -Werror get_next_line.c get_next_line_utils.c -I . -o gnl
```

### ✔️ Ejecución

Ejemplo de uso en un programa:

```c
int fd = open("archivo.txt", O_RDONLY);
char *line;

while ((line = get_next_line(fd)) != NULL)
{
    printf("%s", line);
    free(line);
}
close(fd);
```

---

## 📚 Recursos

### Referencias clásicas

- Documentación estándar de C (ISO/IEC 9899)
- `man 2 read` – Comportamiento del sistema de lectura en Unix
- Artículos educativos sobre buffers y lectura de archivos:
  - https://en.cppreference.com/w/c/io
  - https://www.gnu.org/software/libc/manual/html_node/Low_002dLevel-I-O.html

### Uso de IA en el proyecto

Se ha utilizado inteligencia artificial **únicamente** para:

- Generación del contenido del archivo `README.md`.
- Correcciones de redacción y organización de secciones.
- Explicaciones teóricas sobre el algoritmo de lectura línea a línea para documentarlo.

**No se empleó IA para escribir la implementación del código ni para resolver la lógica del proyecto, cumpliendo las normas pedagógicas del currículo 42.**

---

## 🧠 Explicación y justificación del algoritmo

La función `get_next_line` implementa un algoritmo basado en **lectura controlada** y **almacenamiento persistente**, estructurado en cuatro fases principales:

---

### 🔹 1. Buffer estático persistente

El uso de:

```c
static char *buff;
```

permite almacenar **restos de lectura** entre llamadas sucesivas.  
Esto es necesario porque la lectura con `read()` puede:

- devolver menos bytes de los necesarios para completar una línea,
- cortar justo antes o después del `\n`.

Gracias al buffer estático, el programa puede continuar la línea en la siguiente llamada.

---

### 🔹 2. Lectura desde el descriptor hasta encontrar un salto de línea

La función `read_to_buff()` completa el buffer dinámicamente:

```c
while (r > 0 && !ft_strchr(buff, '\n'))
{
    r = read(fd, tmp, BUFFER_SIZE);
    ...
    buff = gnl_strjoin(buff, tmp);
}
```

Justificación:

- **Eficiencia:** evita leer más de lo necesario.
- **Corrección:** garantiza que se tenga toda la línea antes de extraerla.
- **Robustez:** maneja errores, EOF y concatenación de fragmentos.

---

### 🔹 3. Extracción de la línea completa

```c
line = extract_line(buff);
```

Esta operación:

- Busca el salto de línea.
- Copia exactamente la línea que debe devolverse.
- No altera aún el buffer general.

Justificación:

- Separa claramente *obtener la línea* de *gestionar la memoria*, lo que simplifica el diseño.

---

### 🔹 4. Guardar el resto del buffer

```c
buff = save_remainder(buff);
```

Esta función elimina del buffer la parte ya utilizada y **conserva solamente los datos sobrantes**, permitiendo que el proceso continúe correctamente.

Justificación:

- Mantiene una estructura de datos mínima.
- Evita reallocaciones innecesarias.
- Garantiza linealidad del tiempo de ejecución.

---

## 📌 Ventajas del algoritmo seleccionado

- **O(n)** para cada llamada, siendo n la longitud de la línea retornada.
- Evita sobrelectura del archivo.
- Gestiona correctamente archivos grandes.
- Memoria ajustada dinámicamente a lo necesario.
- Compatible con múltiples tamaños de `BUFFER_SIZE`.
- Separación clara de responsabilidades entre funciones → código modular y fácil de mantener.

---

## 📄 Ejemplo de salida

Para un archivo:

```
Hola
Mundo
42
```

Llamadas:

```
get_next_line(fd) → "Hola
"
get_next_line(fd) → "Mundo
"
get_next_line(fd) → "42"
get_next_line(fd) → NULL
```

---

## 🧩 Decisiones técnicas

- Uso de `static char *buff` para persistencia sin exponer variables globales.
- Concatenación eficiente mediante `gnl_strjoin`.
- No se usan estructuras complejas: solo punteros y memoria dinámica.
- Manejo explícito de errores en lectura y creación de buffers.
- Implementación de funciones auxiliares (`ft_strlen`, `ft_strchr`, `ft_substr`) para evitar uso de la librería estándar, cumpliendo la normativa del proyecto.

---


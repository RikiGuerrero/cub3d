# cub3d

![C Language](https://img.shields.io/badge/C-Programming-blue.svg) ![Makefile](https://img.shields.io/badge/Makefile-Build-orange.svg) ![Git](https://img.shields.io/badge/Git-Version%20Control-red.svg) ![Norminette](https://img.shields.io/badge/Norminette-Code%20Style-brightgreen.svg) ![MLX42](https://img.shields.io/badge/MLX42-Graphics%20Library-yellow.svg) ![Raycasting](https://img.shields.io/badge/Raycasting-3D%20Rendering-blueviolet.svg)

## 📌 Descripción

Cub3D es un proyecto desarrollado en C como parte del currículo de la escuela 42. Su objetivo es crear un juego de laberinto 3D inspirado en *Wolfenstein 3D* utilizando la técnica de *raycasting*. Este proyecto permite a los estudiantes explorar conceptos de programación gráfica y motores de renderizado.

### Características
- Implementación del algoritmo de *raycasting* para generar un entorno 3D.
- Simulación de colisiones y detección de objetos.
- Soporte para texturas y mapeo de paredes.
- Movimiento fluido del jugador dentro del laberinto.
- Uso de la biblioteca gráfica *MLX42*.
## 🛠 Lenguajes y Tecnologías

- **Lenguaje:** C
- **Biblioteca gráfica:** MLX42
- **Técnicas de renderizado:** Raycasting
- **Compilación:** Makefile

## 💡 Conceptos de Programación Aplicados

- Raycasting
- Detección de colisiones
- Transformaciones geométricas
- Mapeo de texturas

## 🚀 Instalación y Uso

1. Clonar el repositorio:
   ```bash
   git clone https://github.com/RikiGuerrero/cub3d.git
   cd cub3d
2. Compilar el proyecto:
   ```bash
   make
   ```
3. Ejecuta el juego:
   ```bash
   ./cub3D maps/subject.cub
   ```
4. Controles
   - **W / A / S / D** - Movimiento del jugador
   - **Flechas Izquierda/Derecha** - Rotación de la cámara
   - **ESC** - Salir del juego

## ✅ Normas y Estilo de Código

El código sigue las reglas de la **Norminette**, la herramienta de estilo de 42. Para verificar:
```bash
norminette
```

## 📜 Licencia

Este proyecto es parte del currículo de 42 y sigue las reglas de la escuela.

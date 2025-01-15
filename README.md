# Generador Interactivo de Analizadores Sintácticos LL(1) y SLR(1)

Este proyecto es una herramienta interactiva diseñada para ayudar a los estudiantes a comprender y construir analizadores sintácticos LL(1) y SLR(1). Permite aprender de manera práctica mediante la generación de gramáticas y la construcción interactiva de tablas de análisis.

## Características

1. **Analizador Sintáctico Automático**  
   Construcción del analizador sintáctico asociado a una gramática generada previamente. El usuario podrá elegir entre LL(1) y SLR(1).

2. **Selección del Tipo de Analizador**  
   El usuario decide si desea trabajar con un analizador LL(1) o SLR(1).

3. **Niveles de Dificultad**  
   Selección de diferentes niveles de dificultad para ajustar la complejidad de las gramáticas generadas.

4. **Generación de Gramáticas**  
   Gramáticas aleatorias generadas según el nivel de dificultad seleccionado.

5. **Construcción Interactiva de Tablas**  
   - **LL(1):** El estudiante introduce manualmente la tabla de análisis, que será validada por el sistema.  
   - **SLR(1):** Construcción manual de los estados del autómata LR con validación paso a paso.

6. **Elección Libre de Configuraciones**  
   Permite al usuario seleccionar libremente los estados y símbolos en cada paso, con retroalimentación inmediata en caso de errores.

7. **Retroalimentación Visual y Textual**  
   Mensajes claros para guiar al estudiante en cada paso, indicando errores y sugiriendo correcciones.

## Requisitos Técnicos

- **Lenguaje:** C++  
- **Framework:** Qt  
- **Mínimo de módulos requeridos:**  
  1. Módulo para analizador LL(1).  
  2. Módulo para analizador SLR(1).  
  3. Módulo para la generación de gramáticas aleatorias.

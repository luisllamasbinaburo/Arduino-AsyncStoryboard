# Librería Arduino Storyboard
La librería Storyboard implementa una serie de tareas temporizadas que ejecutan de forma secuancial una vez transcurrido un determinado tiempo en milisegundos. Resulta útil para dar un cierto comportamiento asíncrono a nuestros programas.

Más información https://www.luisllamas.es/libreria-arduino-storyboard/

## Instrucciones de uso

La librería Storyboard contiene una serie de acciones temporizadas que son ejecutadas de forma secuencial una detrás de otra.

En un proyecto real, por ejemplo, nuestro montaje recibiría una serie de comandos (como la posición y velocidad por las que tiene que pasar un actuador) y emplearíamos un Storyboard para ejecutar las acciones repetidas en el momento deseados.

Un objeto StoryBoard se instancia indicando en el constructor su capacidad, el número máximo de tareas que puede llegar a contener. La función Count indica la cantidad de tareas que están puestas en cola en el StoryBoard.

Cada tarea cuenta con un intervalo de tiempo en milisegundos y una función de callback asociada. Cuando la tarea expira se ejecuta la función de callback y se pasa a la siguiente tarea del StoryBoard.

Los intervalos de cada tarea son en serie. Por ejemplo, 3 tareas de 2000 milisegundos se ejecutarán a los 2, 4 y 6 segundos respectivamente (no a los 2 segundos simultáneamente)

Existen varios tipos de tareas que podemos añadir
- Delay, no ejecuta acción.
- Single, se ejecuta una única vez.
- Repetitive, se ejecuta N veces  
- Continuous, se repite de forma indefinida

- Alternat, se ejecuta N veces, alternando entre dos acciones
- AlternantContinous, se ejecuta de forma indefinida, alternando entre dos acciones.

Para actualizar el estado de las tareas, debemos llamar al método Update con frecuencia. El método Update comprueba el estado de todas las tareas y, en caso de que alguna haya expirado, ejecuta las acciones permanentes.

Las tareas se almacenan en un buffer circular. Si el buffer está lleno, la tarea no se añaden.


### Constructor
La clase Storyboard se instancia a través de su constructor.
```c++
StoryBoard(const size_t capacity);
```

### Uso de Storyboard
```c++
void AddDelay(int time);
void AddDelay(int time, Action callback);
void AddSingle(int time, Action action);
void AddSingle(int time, Action action, Action callback);

void AddRepetitive(int time, Action action, unsigned int repetitions);
void AddRepetitive(int time, Action action, unsigned int repetitions, Action callback);
void AddContinuous(int time, Action action);
void AddContinuous(int time, Action action, Action callback);

void AddAlternant(int time, Action action, Action alternateAction, unsigned int repetitions);
void AddAlternant(int time, Action action, Action alternateAction, unsigned int repetitions, Action callback);
void AddAlternantContinuous(int time, Action action, Action alternateAction);
void AddAlternantContinuous(int time, Action action, Action alternateAction, Action callback);

// Actualizar el estado de la tarea
void Update();

// Estado del buffer 
size_t Capacity() const;
size_t Count() const;
bool IsFull() const;
bool IsEmpty() const;
```


## Ejemplos
La librería Storyboard incluye los siguientes ejemplos para ilustrar su uso.

* Storyboard: Ejemplo que muestra el uso de algunas de las funciones de conversión.
```c++
#include "StoryBoard.h"

StoryBoard storyBoard(10);

void debug(String text)
{
	Serial.print(millis());
	Serial.print('\t');
	Serial.println(text);
}

void setup() 
{
	Serial.begin(9600);

	storyBoard.AddSingle(500, []() {debug("Debug1");});
	storyBoard.AddDelay(1500);
	storyBoard.AddRepetitive(500, 
		[]() {debug("Debug2");}, 3, 
		[]() {storyBoard.AddAlternant(500, []() {debug("Alternant1");}, []() {debug("Alternant2");}, 2);});
}


void loop()
{
	storyBoard.Update();
}
```


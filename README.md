# qprocessing

> qprocessing is a c++ fork of [Processing](https://github.com/processing/processing)

## Installation
### Prerequisites
- [make](https://www.gnu.org/software/make/)
### Dependencies
- [glfw](https://github.com/glfw/glfw)
- [glew](https://github.com/nigels-com/glew)
### Building
``` sh
make release /
make debug
```
## Setup

- Add the [includes](qprocessing/includes) to your include path
- Link with the generated library in build/lib and [GL](https://github.com/nigels-com/glew), [GLEW](https://github.com/nigels-com/glew) and [GLFW](https://github.com/nigels-com/glew)

## Usage
Example main:
``` cpp
#include <qprocessing.h> // should be in your include path
using namespace qprocessing; // more processing like usage (optional)

// you have to implement both of these
void setup();
void draw();

void setup(){
  // your setup code
  size(500, 500); // window size
}
void loop(){
  background(0);
  circle(0, 0, 1);
  // see qprocessing.h for all available functions
}
```

## Documentation
See [qprocessing.h](qprocessing/includes/qprocessing.h) for documentation

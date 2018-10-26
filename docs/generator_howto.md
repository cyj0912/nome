# How to create a new generator for NOME

## You need a main class for the generator
 - Let's call our toy generator MyGenerator
 - It inherits MeshNew, so that the generated mesh is just copied during instanciation.
#### MyGenerator.h
```cpp
#pragma once

#include "Data.h"
#include "MeshNew.h"

class MyGenerator : public MeshNew
{
public:
	explicit MyGenerator(Session* session /*, additional parameters*/)
	{
	    ParentSession = session;
	    GenerateMesh();
	}

private:
    void GenerateMesh();

	//Helpful pointers
	Session* ParentSession;
	Reader* Reader;
};
```
#### MyGenerator.cpp
```c++
#include "MyGenerator.h"
#include "Reader.h"

void MyGenerator::GenerateMesh()
{
    double *x = (double*)malloc(sizeof(double));
	double *y = (double*)malloc(sizeof(double));
	double *z = (double*)malloc(sizeof(double));
	*x = 0; *y = 0; *z = 0;
	Vert* newVert = createVert(x, y, z);
	newVert->setName("testVert0");
	verts.push_back(newVert);
	
	//Edges and faces can be created in an analogous manner.
}
```

## Inform the build system of your new files
In order for `MyGenerator.cpp` and `MyGenerator.h` to compile, you need to add them to the source list in `CMakeLists.txt`.

```cmake
set(SOURCES
        main.cpp
        ...
		MyGenerator.cpp)

set(HEADERS
        edge.h
        ...
		MyGenerator.h)

```

## Change the parser

In order for the parser to recognize your generator, you must define new tokens and a grammer that the parser recognizes. Once the parser encounters the newly defined grammer, it will run your code within the grammar definition to create an instance of your generator.

Suppose that we would like the user to create MyGenerator using the following syntax:
```
mygenerator <name> [fancy] endmygenerator
```
where fancy is an optional keyword.

First, we identify the new keywords that the lexer needs to recognize and convert into numerical tokens. In our case, those would be *mygenerator*, *endmygenerator*, and *fancy*. We go ahead and define them in both the lexer and parser.

#### compilerNome/lexer.l
```
mygenerator             return MY_GENERATOR;
endmygenerator          return END_MY_GENERATOR;
fancy                   return FANCY;
```

#### compilerNome/parser.y
```
%token MY_GENERATOR END_MY_GENERATOR FANCY;
```

Now we are ready to define the new grammer for the parser. Don't forget to also `#include` the header file for your generator at the beginning of `parser.y`.
#### compilerNome/parser.y
```
#include <MyGenerator.h>

...

command: 
  mesh | surface | point | face | object | bank |
  tunnel | funnel | polyline | instance | delete | group | circle |
  subdivision | offset | bspline | beziercurve | foreground | background |
  insidefaces | outsidefaces | offsetfaces | merging | mygenerator;

...

mygenerator: MY_GENERATOR uniqueName optional_fancy END_MY_GENERATOR
            {
                auto* gen = new MyGenerator(currSession);
			    gen->setName(nameUnique);
			    currSession->meshes.push_back(gen);
            };

optional_fancy:
                | FANCY;
```

The `optional_fancy` grammer is there just so that the parser can correctly parse the keyword; the vertical bar means that `optional_fancy` can either be empty or `FANCY`. This keyword doesn't do anything. Also, `mygenerator` needs to be included in the list following `command:`.

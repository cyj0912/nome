# Non-Orientable Manifold Editor (NOME)
Welcome to the non-orientable manifold editor (NOME) project. NOME is a computer aided geometric design tool developed at UC Berkeley from 2015. Inheiriting the major functionaliies from its ancestor SLIDE (https://people.eecs.berkeley.edu/~ug/slide/), NOME also provides a design envrionment that support mesh operations on single-sided 2 manifolds (wikipedia definition for manifold https://en.wikipedia.org/wiki/Manifold). It also supprt various fun and interactive UI operations such as vertex/face selection, face adding/deletion.

# User's Guide
1. Platforms, Download and Installation
NOME is developend and released on various platforms, including Microsoft Windows 7 or higher system, Mac OS, and Linus system.
2. Getting started
3. A Hello-Cube example
4. Want to explore more?
Appendix A: Commands of input .nome file
Appendix B: User Interface Details

## Microsoft Windows Libraries and Dependencies
In order to compile NOME, the following dependencies are needed:
  * Qt (https://www.qt.io/download/) (the open source version is free to download)
  * GLM (http://glm.g-truc.net/0.9.6/index.html). Download the zip version (currently called glm-0.9.8.3.zip). Unzip the file and navigate inside the glm folder. Place the nested glm folder at the root of the downloaded project. 
  * Flex and Bison are required if you wish to modify the parser. Linux/Mac user can just install them with their favorite package manager. For Windows users, the Msys2 project provides a nice package that installs both.

## Example CMake Setup
`
CMAKE_PREFIX_PATH=<Qt Path>;<Flex and Bison Path>
`

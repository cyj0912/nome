/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_STL_E_DEVGRA_NOME_COMPILERSTL_PARSERSTL_HPP_INCLUDED
# define YY_STL_E_DEVGRA_NOME_COMPILERSTL_PARSERSTL_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int stldebug;
#endif
/* "%code requires" blocks.  */
#line 1 "compilerStl/parserStl.y" /* yacc.c:1909  */

#include <newNOME/Session.h>

#line 48 "E:/DevGra/nome/compilerStl/parserStl.hpp" /* yacc.c:1909  */

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    OUTER = 258,
    SOLID = 259,
    FACET = 260,
    ENDFACET = 261,
    LOOP = 262,
    ENDLOOP = 263,
    VERTEX = 264,
    NORMAL = 265,
    ENDSOLID = 266,
    VARIABLE = 267,
    NUMBER = 268,
    BANK_EXPR = 269
  };
#endif
/* Tokens.  */
#define OUTER 258
#define SOLID 259
#define FACET 260
#define ENDFACET 261
#define LOOP 262
#define ENDLOOP 263
#define VERTEX 264
#define NORMAL 265
#define ENDSOLID 266
#define VARIABLE 267
#define NUMBER 268
#define BANK_EXPR 269

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 66 "compilerStl/parserStl.y" /* yacc.c:1909  */

    double number;
    char *string;
    struct {
        char *string; // char *strVal;
        double number;   // int posVal;
    } numPos;

#line 97 "E:/DevGra/nome/compilerStl/parserStl.hpp" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE stllval;
extern YYLTYPE stllloc;
int stlparse (Session* currSession);

#endif /* !YY_STL_E_DEVGRA_NOME_COMPILERSTL_PARSERSTL_HPP_INCLUDED  */

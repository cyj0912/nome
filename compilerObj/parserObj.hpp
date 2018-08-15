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

#ifndef YY_OBJ_E_DEVGRA_NOME_COMPILEROBJ_PARSEROBJ_HPP_INCLUDED
# define YY_OBJ_E_DEVGRA_NOME_COMPILEROBJ_PARSEROBJ_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int objdebug;
#endif
/* "%code requires" blocks.  */
#line 1 "compilerObj/parserObj.y" /* yacc.c:1909  */

#include <newNOME/Session.h>

#line 48 "E:/DevGra/nome/compilerObj/parserObj.hpp" /* yacc.c:1909  */

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    COMMENT = 258,
    NUMBER = 259,
    V = 260,
    VT = 261,
    VN = 262,
    VP = 263,
    F = 264,
    L = 265,
    O = 266,
    G = 267,
    S = 268,
    SLASH = 269,
    MTLLIB = 270,
    USEMTL = 271,
    VARIABLE = 272,
    BANK_EXPR = 273
  };
#endif
/* Tokens.  */
#define COMMENT 258
#define NUMBER 259
#define V 260
#define VT 261
#define VN 262
#define VP 263
#define F 264
#define L 265
#define O 266
#define G 267
#define S 268
#define SLASH 269
#define MTLLIB 270
#define USEMTL 271
#define VARIABLE 272
#define BANK_EXPR 273

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 85 "compilerObj/parserObj.y" /* yacc.c:1909  */

    double number;
    char *string;
    struct {
        char *string; // char *strVal;
        double number;   // int posVal;
    } numPos;

#line 105 "E:/DevGra/nome/compilerObj/parserObj.hpp" /* yacc.c:1909  */
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


extern YYSTYPE objlval;
extern YYLTYPE objlloc;
int objparse (Session* currSession);

#endif /* !YY_OBJ_E_DEVGRA_NOME_COMPILEROBJ_PARSEROBJ_HPP_INCLUDED  */

/* A Bison parser, made by GNU Bison 3.2.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018 Free Software Foundation, Inc.

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_BANK_D_DEV_NOME_COMPILERBANK_PARSERBANK_HPP_INCLUDED
# define YY_BANK_D_DEV_NOME_COMPILERBANK_PARSERBANK_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int bankdebug;
#endif
/* "%code requires" blocks.  */
#line 1 "compilerBank/parserBank.y" /* yacc.c:1906  */

#include <newNOME/Session.h>

#line 51 "D:/Dev/nome/compilerBank/parserBank.hpp" /* yacc.c:1906  */

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    COS = 258,
    SIN = 259,
    TAN = 260,
    SEC = 261,
    CSC = 262,
    COT = 263,
    E = 264,
    LN = 265,
    LOG = 266,
    SQRT = 267,
    LPAREN = 268,
    RPAREN = 269,
    EXP = 270,
    MULTIPLY = 271,
    DIVIDE = 272,
    ADD = 273,
    SUBTRACT = 274,
    NUM = 275,
    ARCCOS = 276,
    ARCCOT = 277,
    ARCCSC = 278,
    ARCSEC = 279,
    ARCSIN = 280,
    ARCTAN = 281,
    BANK_EXPR = 282
  };
#endif
/* Tokens.  */
#define COS 258
#define SIN 259
#define TAN 260
#define SEC 261
#define CSC 262
#define COT 263
#define E 264
#define LN 265
#define LOG 266
#define SQRT 267
#define LPAREN 268
#define RPAREN 269
#define EXP 270
#define MULTIPLY 271
#define DIVIDE 272
#define ADD 273
#define SUBTRACT 274
#define NUM 275
#define ARCCOS 276
#define ARCCOT 277
#define ARCCSC 278
#define ARCSEC 279
#define ARCSIN 280
#define ARCTAN 281
#define BANK_EXPR 282

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 49 "compilerBank/parserBank.y" /* yacc.c:1906  */

    double number;
    char *string;

#line 122 "D:/Dev/nome/compilerBank/parserBank.hpp" /* yacc.c:1906  */
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


extern YYSTYPE banklval;
extern YYLTYPE banklloc;
int bankparse (Session* currSession);

#endif /* !YY_BANK_D_DEV_NOME_COMPILERBANK_PARSERBANK_HPP_INCLUDED  */

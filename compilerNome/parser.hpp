/* A Bison parser, made by GNU Bison 3.0.5.  */

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

#ifndef YY_NOM_E_DEVGRA_NOME_COMPILERNOME_PARSER_HPP_INCLUDED
# define YY_NOM_E_DEVGRA_NOME_COMPILERNOME_PARSER_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int nomdebug;
#endif
/* "%code requires" blocks.  */
#line 1 "compilerNome/parser.y" /* yacc.c:1910  */

#include <newNOME/Session.h>


#line 49 "E:/DevGra/nome/compilerNome/parser.hpp" /* yacc.c:1910  */

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    COLOR = 258,
    VARIABLE = 259,
    NEWLINE = 260,
    SURFACE = 261,
    END_SURFACE = 262,
    MESH = 263,
    END_MESH = 264,
    FACE = 265,
    END_FACE = 266,
    BEG_POINT = 267,
    END_POINT = 268,
    OBJECT = 269,
    END_OBJECT = 270,
    BANK = 271,
    END_BANK = 272,
    TUNNEL = 273,
    END_TUNNEL = 274,
    FUNNEL = 275,
    END_FUNNEL = 276,
    POLYLINE = 277,
    END_POLYLINE = 278,
    INSTANCE = 279,
    END_INSTANCE = 280,
    CIRCLE = 281,
    END_CIRCLE = 282,
    BEG_DELETE = 283,
    END_DELETE = 284,
    GROUP = 285,
    END_GROUP = 286,
    TRANSLATE = 287,
    ROTATE = 288,
    MIRROR = 289,
    SET = 290,
    OPARENTHESES = 291,
    EPARENTHESES = 292,
    OBRACE = 293,
    EXPR = 294,
    DOLLAR = 295,
    EBRACE = 296,
    PERIOD = 297,
    TOKHEAT = 298,
    STATE = 299,
    TOKTARGET = 300,
    TOKTEMPERATURE = 301,
    SCALE = 302,
    SUBDIVISION = 303,
    END_SUBDIVISION = 304,
    SUBDIVISIONS = 305,
    TYPE = 306,
    OFFSET = 307,
    END_OFFSET = 308,
    MIN = 309,
    MAX = 310,
    STEP = 311,
    BSPLINE = 312,
    END_BSPLINE = 313,
    CLOSED = 314,
    SLICES = 315,
    BEZIERCURVE = 316,
    END_BEZIERCURVE = 317,
    COS = 318,
    SIN = 319,
    TAN = 320,
    EXPONENT = 321,
    MULTIPLY = 322,
    DIVIDE = 323,
    ADD = 324,
    SUBTRACT = 325,
    SLIDEREXPRESSION = 326,
    REVERSE = 327,
    FOREGROUND = 328,
    END_FOREGROUND = 329,
    BACKGROUND = 330,
    END_BACKGROUND = 331,
    INSIDEFACES = 332,
    END_INSIDEFACES = 333,
    OUTSIDEFACES = 334,
    END_OUTSIDEFACES = 335,
    OFFSETFACES = 336,
    END_OFFSETFACES = 337,
    MERGE = 338,
    END_MERGE = 339,
    EPSILON = 340,
    SWEEP = 341,
    END_SWEEP = 342,
    PATH = 343,
    ENDPATH = 344,
    CROSSSECTION = 345,
    END_CROSSSECTION = 346,
    BANK_EXPR = 347,
    NUMBER = 348
  };
#endif
/* Tokens.  */
#define COLOR 258
#define VARIABLE 259
#define NEWLINE 260
#define SURFACE 261
#define END_SURFACE 262
#define MESH 263
#define END_MESH 264
#define FACE 265
#define END_FACE 266
#define BEG_POINT 267
#define END_POINT 268
#define OBJECT 269
#define END_OBJECT 270
#define BANK 271
#define END_BANK 272
#define TUNNEL 273
#define END_TUNNEL 274
#define FUNNEL 275
#define END_FUNNEL 276
#define POLYLINE 277
#define END_POLYLINE 278
#define INSTANCE 279
#define END_INSTANCE 280
#define CIRCLE 281
#define END_CIRCLE 282
#define BEG_DELETE 283
#define END_DELETE 284
#define GROUP 285
#define END_GROUP 286
#define TRANSLATE 287
#define ROTATE 288
#define MIRROR 289
#define SET 290
#define OPARENTHESES 291
#define EPARENTHESES 292
#define OBRACE 293
#define EXPR 294
#define DOLLAR 295
#define EBRACE 296
#define PERIOD 297
#define TOKHEAT 298
#define STATE 299
#define TOKTARGET 300
#define TOKTEMPERATURE 301
#define SCALE 302
#define SUBDIVISION 303
#define END_SUBDIVISION 304
#define SUBDIVISIONS 305
#define TYPE 306
#define OFFSET 307
#define END_OFFSET 308
#define MIN 309
#define MAX 310
#define STEP 311
#define BSPLINE 312
#define END_BSPLINE 313
#define CLOSED 314
#define SLICES 315
#define BEZIERCURVE 316
#define END_BEZIERCURVE 317
#define COS 318
#define SIN 319
#define TAN 320
#define EXPONENT 321
#define MULTIPLY 322
#define DIVIDE 323
#define ADD 324
#define SUBTRACT 325
#define SLIDEREXPRESSION 326
#define REVERSE 327
#define FOREGROUND 328
#define END_FOREGROUND 329
#define BACKGROUND 330
#define END_BACKGROUND 331
#define INSIDEFACES 332
#define END_INSIDEFACES 333
#define OUTSIDEFACES 334
#define END_OUTSIDEFACES 335
#define OFFSETFACES 336
#define END_OFFSETFACES 337
#define MERGE 338
#define END_MERGE 339
#define EPSILON 340
#define SWEEP 341
#define END_SWEEP 342
#define PATH 343
#define ENDPATH 344
#define CROSSSECTION 345
#define END_CROSSSECTION 346
#define BANK_EXPR 347
#define NUMBER 348

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 87 "compilerNome/parser.y" /* yacc.c:1910  */

    double intNumber;
    double number;
    const char *string;
    bool boolean;
    struct {
        const char *string; // char *strVal;
        double number;   // int posVal;
    } numPos;

#line 258 "E:/DevGra/nome/compilerNome/parser.hpp" /* yacc.c:1910  */
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


extern YYSTYPE nomlval;
extern YYLTYPE nomlloc;
int nomparse (Session* currSession);

#endif /* !YY_NOM_E_DEVGRA_NOME_COMPILERNOME_PARSER_HPP_INCLUDED  */

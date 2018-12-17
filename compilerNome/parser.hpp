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

#ifndef YY_NOM_D_DEV_NOME_COMPILERNOME_PARSER_HPP_INCLUDED
# define YY_NOM_D_DEV_NOME_COMPILERNOME_PARSER_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int nomdebug;
#endif
/* "%code requires" blocks.  */
#line 1 "compilerNome/parser.y" /* yacc.c:1906  */

#include <newNOME/Session.h>


#line 52 "D:/Dev/nome/compilerNome/parser.hpp" /* yacc.c:1906  */

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
    TORUSKNOT = 283,
    END_TORUSKNOT = 284,
    BEG_DELETE = 285,
    END_DELETE = 286,
    GROUP = 287,
    END_GROUP = 288,
    TRANSLATE = 289,
    ROTATE = 290,
    MIRROR = 291,
    SET = 292,
    OPARENTHESES = 293,
    EPARENTHESES = 294,
    OBRACE = 295,
    EXPR = 296,
    DOLLAR = 297,
    EBRACE = 298,
    PERIOD = 299,
    TOKHEAT = 300,
    STATE = 301,
    TOKTARGET = 302,
    TOKTEMPERATURE = 303,
    SCALE = 304,
    SUBDIVISION = 305,
    END_SUBDIVISION = 306,
    SUBDIVISIONS = 307,
    TYPE = 308,
    OFFSET = 309,
    END_OFFSET = 310,
    MIN = 311,
    MAX = 312,
    STEP = 313,
    BSPLINE = 314,
    END_BSPLINE = 315,
    CLOSED = 316,
    MINIMIZETORSION = 317,
    AZIMUTH = 318,
    TWIST = 319,
    SLICES = 320,
    BEZIERCURVE = 321,
    END_BEZIERCURVE = 322,
    COS = 323,
    SIN = 324,
    TAN = 325,
    EXPONENT = 326,
    MULTIPLY = 327,
    DIVIDE = 328,
    ADD = 329,
    SUBTRACT = 330,
    SLIDEREXPRESSION = 331,
    REVERSE = 332,
    FOREGROUND = 333,
    END_FOREGROUND = 334,
    BACKGROUND = 335,
    END_BACKGROUND = 336,
    INSIDEFACES = 337,
    END_INSIDEFACES = 338,
    OUTSIDEFACES = 339,
    END_OUTSIDEFACES = 340,
    OFFSETFACES = 341,
    END_OFFSETFACES = 342,
    MERGE = 343,
    END_MERGE = 344,
    EPSILON = 345,
    SWEEP = 346,
    END_SWEEP = 347,
    PATH = 348,
    ENDPATH = 349,
    CROSSSECTION = 350,
    END_CROSSSECTION = 351,
    BANK_EXPR = 352,
    NUMBER = 353
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
#define TORUSKNOT 283
#define END_TORUSKNOT 284
#define BEG_DELETE 285
#define END_DELETE 286
#define GROUP 287
#define END_GROUP 288
#define TRANSLATE 289
#define ROTATE 290
#define MIRROR 291
#define SET 292
#define OPARENTHESES 293
#define EPARENTHESES 294
#define OBRACE 295
#define EXPR 296
#define DOLLAR 297
#define EBRACE 298
#define PERIOD 299
#define TOKHEAT 300
#define STATE 301
#define TOKTARGET 302
#define TOKTEMPERATURE 303
#define SCALE 304
#define SUBDIVISION 305
#define END_SUBDIVISION 306
#define SUBDIVISIONS 307
#define TYPE 308
#define OFFSET 309
#define END_OFFSET 310
#define MIN 311
#define MAX 312
#define STEP 313
#define BSPLINE 314
#define END_BSPLINE 315
#define CLOSED 316
#define MINIMIZETORSION 317
#define AZIMUTH 318
#define TWIST 319
#define SLICES 320
#define BEZIERCURVE 321
#define END_BEZIERCURVE 322
#define COS 323
#define SIN 324
#define TAN 325
#define EXPONENT 326
#define MULTIPLY 327
#define DIVIDE 328
#define ADD 329
#define SUBTRACT 330
#define SLIDEREXPRESSION 331
#define REVERSE 332
#define FOREGROUND 333
#define END_FOREGROUND 334
#define BACKGROUND 335
#define END_BACKGROUND 336
#define INSIDEFACES 337
#define END_INSIDEFACES 338
#define OUTSIDEFACES 339
#define END_OUTSIDEFACES 340
#define OFFSETFACES 341
#define END_OFFSETFACES 342
#define MERGE 343
#define END_MERGE 344
#define EPSILON 345
#define SWEEP 346
#define END_SWEEP 347
#define PATH 348
#define ENDPATH 349
#define CROSSSECTION 350
#define END_CROSSSECTION 351
#define BANK_EXPR 352
#define NUMBER 353

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 88 "compilerNome/parser.y" /* yacc.c:1906  */

    double intNumber;
    double number;
    const char *string;
    bool boolean;
    struct {
        const char *string; // char *strVal;
        double number;   // int posVal;
    } numPos;

#line 271 "D:/Dev/nome/compilerNome/parser.hpp" /* yacc.c:1906  */
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

#endif /* !YY_NOM_D_DEV_NOME_COMPILERNOME_PARSER_HPP_INCLUDED  */

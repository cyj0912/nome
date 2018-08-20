/* A Bison parser, made by GNU Bison 3.0.5.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.5"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1


/* Substitute the variable and function names.  */
#define yyparse         nomparse
#define yylex           nomlex
#define yyerror         nomerror
#define yydebug         nomdebug
#define yynerrs         nomnerrs

#define yylval          nomlval
#define yychar          nomchar
#define yylloc          nomlloc

/* Copy the first part of user declarations.  */
#line 6 "compilerNome/parser.y" /* yacc.c:339  */

#include <stdio.h>
#include <string.h>
#include <list>
#include <newNOME/Data.h>
#include <newNOME/MeshNew.h>
#include <newNOME/Session.h>
#include <newNOME/Reader.h>
#include <newNOME/TransformationNew.h>
#include <newNOME/PolylineNew.h>
#include <newNOME/CircleNew.h>
#include <newNOME/FunnelNew.h>
#include <newNOME/TunnelNew.h>
#include <newNOME/InstanceNew.h>
#include <newNOME/BankNew.h>
#include <newNOME/OffsetNew.h>
#include <newNOME/SubdivisionNew.h>
#include <newNOME/GroupNew.h>
#include <newNOME/BSplineNew.h>
#include <newNOME/BezierCurveNew.h>
#include <newNOME/Sweep.h>

extern int nomlineno;
extern char* nomtext;
extern int nomcolumn;

int nomlex(void);
void nomerror(Session* currSession, const char *s) {
  printf("%s on line %d - %s\n", s, nomlineno, nomtext);
}

int nomwrap() {
    return 1;
}

map<string,QColor> surfaces2;
map<string,Vert*> vertices2;
std::vector<string> tempVariables2;
std::vector<string> tempFaceDelete2;
string currentSetName2;
std::list<SetNew *> currentSetList2;
map<string,std::vector<double>> currentBank2;
std::vector<string> currentInstanceList2;
std::list<InstanceNew *> currentGroup2;
std::list<FaceNew *> currentMeshFaces2;
std::list<PolylineNew *> currentMeshPolyline;
std::list<Vert *> currentMeshVertices2;
std::list<EdgeNew *> currentMeshEdges2;
std::list<TransformationNew *> currentTransformations2;
std::string surfaceFromArg;
std::string nameUnique;
std::string nameUniqueFaceMesh;
std::string nameUniqueInstanceGroup;
SweepInitializer currentSweepInitializer;


#line 132 "E:/DevGra/nome/compilerNome/parser.cpp" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* In a future release of Bison, this section will be replaced
   by #include "parser.hpp".  */
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
#line 1 "compilerNome/parser.y" /* yacc.c:355  */

#include <newNOME/Session.h>


#line 167 "E:/DevGra/nome/compilerNome/parser.cpp" /* yacc.c:355  */

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
#line 87 "compilerNome/parser.y" /* yacc.c:355  */

    double intNumber;
    double number;
    const char *string;
    bool boolean;
    struct {
        const char *string; // char *strVal;
        double number;   // int posVal;
    } numPos;

#line 376 "E:/DevGra/nome/compilerNome/parser.cpp" /* yacc.c:355  */
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

/* Copy the second part of user declarations.  */

#line 407 "E:/DevGra/nome/compilerNome/parser.cpp" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   373

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  94
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  56
/* YYNRULES -- Number of rules.  */
#define YYNRULES  96
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  250

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   348

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   110,   110,   111,   116,   116,   116,   116,   116,   116,
     117,   117,   117,   117,   117,   117,   117,   118,   118,   118,
     118,   118,   118,   119,   119,   119,   119,   119,   122,   124,
     133,   143,   155,   177,   187,   189,   195,   202,   203,   207,
     208,   208,   208,   208,   208,   208,   212,   219,   248,   272,
     296,   311,   312,   312,   315,   316,   320,   381,   382,   386,
     391,   392,   396,   416,   445,   472,   488,   501,   524,   525,
     529,   574,   627,   638,   650,   674,   708,   743,   749,   791,
     798,   847,   913,   951,   967,   968,   971,   984,  1000,  1019,
    1038,  1057,  1076,  1095,  1152,  1188,  1214
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "COLOR", "VARIABLE", "NEWLINE",
  "SURFACE", "END_SURFACE", "MESH", "END_MESH", "FACE", "END_FACE",
  "BEG_POINT", "END_POINT", "OBJECT", "END_OBJECT", "BANK", "END_BANK",
  "TUNNEL", "END_TUNNEL", "FUNNEL", "END_FUNNEL", "POLYLINE",
  "END_POLYLINE", "INSTANCE", "END_INSTANCE", "CIRCLE", "END_CIRCLE",
  "BEG_DELETE", "END_DELETE", "GROUP", "END_GROUP", "TRANSLATE", "ROTATE",
  "MIRROR", "SET", "OPARENTHESES", "EPARENTHESES", "OBRACE", "EXPR",
  "DOLLAR", "EBRACE", "PERIOD", "TOKHEAT", "STATE", "TOKTARGET",
  "TOKTEMPERATURE", "SCALE", "SUBDIVISION", "END_SUBDIVISION",
  "SUBDIVISIONS", "TYPE", "OFFSET", "END_OFFSET", "MIN", "MAX", "STEP",
  "BSPLINE", "END_BSPLINE", "CLOSED", "SLICES", "BEZIERCURVE",
  "END_BEZIERCURVE", "COS", "SIN", "TAN", "EXPONENT", "MULTIPLY", "DIVIDE",
  "ADD", "SUBTRACT", "SLIDEREXPRESSION", "REVERSE", "FOREGROUND",
  "END_FOREGROUND", "BACKGROUND", "END_BACKGROUND", "INSIDEFACES",
  "END_INSIDEFACES", "OUTSIDEFACES", "END_OUTSIDEFACES", "OFFSETFACES",
  "END_OFFSETFACES", "MERGE", "END_MERGE", "EPSILON", "SWEEP", "END_SWEEP",
  "PATH", "ENDPATH", "CROSSSECTION", "END_CROSSSECTION", "BANK_EXPR",
  "NUMBER", "$accept", "commands", "command", "numberValue", "uniqueName",
  "uniqueNameFaceMesh", "uniqueNameInstanceGroup", "numPosTok",
  "variables", "surfaceArgs", "closedArgs", "transformArgs", "reverseArgs",
  "rotateArgs", "translateArgs", "scaleArgs", "mirrorArgs", "faceArgs",
  "instanceArgs", "instanceGroup", "faceDeleteArgs",
  "instanceOffseSubdivide", "instanceOffseSubdivideArgs", "subdivision",
  "offset", "mesh", "group", "delete", "set", "setArgs", "polylineMesh",
  "faceMesh", "bank", "merging", "circle", "tunnel", "funnel",
  "parenthesisName", "face", "faceDelete", "beziercurve", "bspline",
  "polyline", "sweep", "sweep_param_pack", "sweep_path",
  "sweep_crosssection", "foreground", "background", "insidefaces",
  "outsidefaces", "offsetfaces", "instance", "object", "surface", "point", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348
};
# endif

#define YYPACT_NINF -84

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-84)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -84,   174,   -84,     6,     6,     6,     6,     6,     9,     6,
       6,     6,     6,     6,   -84,     6,    32,    40,     6,     6,
     -84,   -84,   -84,   -84,   -84,   -73,     6,   -84,   -84,   -84,
     -84,   -84,   -84,   -84,   -84,   -84,   -84,   -84,   -84,   -84,
     -84,   -84,   -84,   -84,   -84,   -84,   -84,   -84,   -84,   -84,
     -84,   -84,   -84,    18,   -84,    16,    21,    16,   -84,    22,
      24,    16,    49,    28,    17,   -84,   -84,   -84,    16,    16,
     195,   187,    73,    42,     8,   -60,   -19,    34,    41,   -84,
     -84,   -60,    57,    26,   -60,   -60,   -84,   -84,   -60,    69,
     -84,   -84,    25,   -16,    -4,    29,    23,    74,    45,    55,
      56,    58,   -84,   -84,   -84,   -84,   -84,   -84,   -84,   -84,
     -84,   -84,   -84,   -84,   -84,   -84,    -7,    91,   -83,   -84,
     -60,   -84,    92,     6,   -84,   -84,     2,   205,   -60,   -84,
     -84,    93,   -84,   -60,   -60,   238,   248,   -60,    87,    95,
     -84,   -84,    97,   100,   -84,   104,   -84,    51,   -60,   -84,
     -60,   -60,   -60,   -60,   -84,    30,   -84,   108,   -84,   -60,
     -84,    16,    16,   -84,   -84,   -84,   -60,    31,   -60,   -60,
     -84,   -84,    86,   -84,   -84,   121,   -84,    79,    76,   -60,
     -84,   -60,   -60,   -60,   -60,   -84,    43,   -60,   -84,   -84,
      96,   -84,   -60,   -60,   -60,   112,   -84,   -60,   -60,   -84,
     242,   -60,   -60,   -60,   -60,   -84,   103,   285,   292,   128,
     -60,   106,   109,   -84,   296,    98,    94,   301,   -84,   111,
     113,   -60,   115,   146,   -84,   -84,   -84,   -60,   135,   136,
     -84,   -84,   -60,   -84,   -84,   120,   123,   -84,   -84,   -84,
     -84,   -84,   102,   -60,   -84,   -60,   125,   110,   -84,   -84
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    57,     0,     0,     0,     0,     0,
      39,    39,    39,    39,    39,     0,     0,     3,    17,    18,
       4,    15,    14,     9,    26,    16,    10,    11,     7,    20,
      19,    12,    27,    21,    22,    23,    24,    25,    13,     8,
       5,     6,    30,     0,    51,     0,     0,     0,    68,     0,
       0,     0,     0,     0,     0,    54,    60,    60,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    34,
      39,     0,     0,     0,     0,     0,    39,    39,     0,     0,
      66,    58,     0,     0,     0,    37,     0,     0,     0,     0,
       0,     0,    46,    88,    45,    41,    40,    42,    43,    44,
      89,    90,    91,    92,    29,    28,     0,     0,     0,    84,
       0,    64,     0,     0,    53,    52,     0,     0,     0,    94,
      72,     0,    69,     0,     0,     0,     0,     0,     0,     0,
      65,    55,     0,     0,    61,     0,    38,     0,     0,    36,
       0,     0,     0,     0,    73,     0,    83,     0,    85,     0,
      31,     0,     0,    35,    77,    78,     0,     0,     0,     0,
      82,    93,     0,    79,    32,     0,    59,     0,     0,     0,
      39,     0,     0,     0,     0,    86,     0,     0,    39,    39,
       0,    33,     0,     0,     0,     0,    39,     0,     0,    39,
       0,     0,     0,     0,     0,    87,     0,     0,     0,     0,
       0,     0,     0,    74,     0,     0,     0,     0,    80,     0,
       0,     0,     0,     0,    71,    70,    96,     0,     0,     0,
      56,    62,     0,    81,    48,     0,     0,    49,    95,    67,
      75,    76,     0,     0,    50,     0,     0,     0,    47,    63
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -84,   -84,   -84,   -66,    19,   -84,   -84,   -84,   -84,   -84,
     -84,   -21,   -84,   -84,   -84,   -84,   -84,   -84,   -84,   -84,
     -84,   -84,   105,   -84,   -84,   -84,   -84,   -84,   -84,   -84,
     -84,   -84,   -84,   -84,   -84,   -84,   -84,   -52,   -84,   -84,
     -84,   -84,   -84,   -84,   -84,   -84,   -84,   -84,   -84,   -84,
     -84,   -84,   -84,   -84,   -84,   -84
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    27,   116,    53,   161,   175,   192,   126,   104,
     147,    70,   105,   106,   107,   108,   109,    78,    92,   141,
      64,   144,    93,    28,    29,    30,    31,    32,   132,    83,
     124,   125,    33,    34,    35,    36,    37,    80,    38,    91,
      39,    40,    41,    42,   118,   119,   158,    43,    44,    45,
      46,    47,    48,    49,    50,    51
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      71,    72,    73,    74,   156,    82,   163,   157,   142,    86,
      52,   114,    75,    58,    97,   128,    95,    96,   133,   134,
     142,    77,   137,    54,    55,    56,    57,    89,    59,    60,
      61,    62,    63,   115,    65,   143,    66,    68,    69,   164,
      98,    99,   100,   130,    67,    76,    90,   145,    97,   139,
     121,   122,    79,    87,   159,   101,   140,    81,    84,   127,
      85,   131,   166,   123,    88,   135,   136,   168,   169,   117,
     120,   172,   129,   138,    98,    99,   100,   154,   149,    97,
     102,   150,   180,   148,   181,   182,   183,   184,   146,   101,
     113,   151,   152,   187,   153,   155,   160,   167,   173,   174,
     190,   176,   193,   194,   177,    98,    99,   100,   178,   188,
     189,   179,   186,   199,   102,   201,   202,   203,   204,   185,
     101,   206,   112,   195,   191,   196,   210,   211,   212,   197,
     198,   215,   216,   209,   205,   219,   220,   221,   222,   213,
     223,   226,   162,   228,   227,   102,   229,   231,   234,   232,
     235,   111,   237,   238,   240,   236,   243,   241,   245,   200,
     244,   239,   248,   249,     0,     0,   242,   207,   208,     0,
       0,     0,    94,     0,     2,   214,     0,   246,   217,   247,
       3,     0,     4,     0,     5,     0,     6,     0,     7,     0,
       8,     0,     9,    97,    10,     0,    11,     0,    12,     0,
      13,    97,    14,     0,    15,     0,     0,     0,     0,     0,
       0,    97,     0,     0,     0,     0,   165,     0,     0,    98,
      99,   100,    16,     0,     0,     0,    17,    98,    99,   100,
       0,    18,     0,     0,   101,    19,     0,    98,    99,   100,
       0,     0,   101,     0,    97,     0,     0,    20,    97,    21,
       0,    22,   101,    23,    97,    24,     0,    25,     0,   102,
      26,   170,     0,   110,     0,     0,     0,   102,     0,   103,
      98,    99,   100,   171,    98,    99,   100,   102,     0,     0,
      98,    99,   100,     0,     0,   101,     0,     0,     0,   101,
       0,    97,     0,     0,     0,   101,   224,     0,    97,     0,
       0,     0,    97,     0,   218,     0,     0,    97,     0,     0,
     102,     0,     0,     0,   102,   225,     0,    98,    99,   100,
     102,   230,     0,     0,    98,    99,   100,     0,    98,    99,
     100,     0,   101,    98,    99,   100,     0,     0,     0,   101,
       0,     0,     0,   101,     0,     0,     0,     0,   101,     0,
       0,     0,     0,     0,     0,     0,     0,   102,     0,   233,
       0,     0,     0,     0,   102,     0,     0,     0,   102,     0,
       0,     0,     0,   102
};

static const yytype_int16 yycheck[] =
{
      21,    22,    23,    24,    87,    57,     4,    90,    24,    61,
       4,    71,    85,     4,     6,    81,    68,    69,    84,    85,
      24,     3,    88,     4,     5,     6,     7,    10,     9,    10,
      11,    12,    13,    93,    15,    51,     4,    18,    19,    37,
      32,    33,    34,    17,     4,    26,    29,    51,     6,    24,
       9,    10,    36,     4,   120,    47,    31,    36,    36,    80,
      36,    35,   128,    22,    36,    86,    87,   133,   134,    88,
      36,   137,    15,     4,    32,    33,    34,    84,     4,     6,
      72,    36,   148,    60,   150,   151,   152,   153,    59,    47,
      82,    36,    36,   159,    36,     4,     4,     4,    11,     4,
     166,     4,   168,   169,     4,    32,    33,    34,     4,   161,
     162,    60,     4,   179,    72,   181,   182,   183,   184,    89,
      47,   187,    80,    37,    93,     4,   192,   193,   194,    50,
      54,   197,   198,    37,    91,   201,   202,   203,   204,    27,
      37,    13,   123,    37,   210,    72,    37,    49,    37,    55,
      37,    78,    37,     7,    19,   221,    36,    21,    56,   180,
      37,   227,    37,    53,    -1,    -1,   232,   188,   189,    -1,
      -1,    -1,    67,    -1,     0,   196,    -1,   243,   199,   245,
       6,    -1,     8,    -1,    10,    -1,    12,    -1,    14,    -1,
      16,    -1,    18,     6,    20,    -1,    22,    -1,    24,    -1,
      26,     6,    28,    -1,    30,    -1,    -1,    -1,    -1,    -1,
      -1,     6,    -1,    -1,    -1,    -1,    11,    -1,    -1,    32,
      33,    34,    48,    -1,    -1,    -1,    52,    32,    33,    34,
      -1,    57,    -1,    -1,    47,    61,    -1,    32,    33,    34,
      -1,    -1,    47,    -1,     6,    -1,    -1,    73,     6,    75,
      -1,    77,    47,    79,     6,    81,    -1,    83,    -1,    72,
      86,    23,    -1,    76,    -1,    -1,    -1,    72,    -1,    74,
      32,    33,    34,    25,    32,    33,    34,    72,    -1,    -1,
      32,    33,    34,    -1,    -1,    47,    -1,    -1,    -1,    47,
      -1,     6,    -1,    -1,    -1,    47,    11,    -1,     6,    -1,
      -1,    -1,     6,    -1,    62,    -1,    -1,     6,    -1,    -1,
      72,    -1,    -1,    -1,    72,    23,    -1,    32,    33,    34,
      72,    25,    -1,    -1,    32,    33,    34,    -1,    32,    33,
      34,    -1,    47,    32,    33,    34,    -1,    -1,    -1,    47,
      -1,    -1,    -1,    47,    -1,    -1,    -1,    -1,    47,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    72,    -1,    58,
      -1,    -1,    -1,    -1,    72,    -1,    -1,    -1,    72,    -1,
      -1,    -1,    -1,    72
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    95,     0,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,    30,    48,    52,    57,    61,
      73,    75,    77,    79,    81,    83,    86,    96,   117,   118,
     119,   120,   121,   126,   127,   128,   129,   130,   132,   134,
     135,   136,   137,   141,   142,   143,   144,   145,   146,   147,
     148,   149,     4,    98,    98,    98,    98,    98,     4,    98,
      98,    98,    98,    98,   114,    98,     4,     4,    98,    98,
     105,   105,   105,   105,   105,    85,    98,     3,   111,    36,
     131,    36,   131,   123,    36,    36,   131,     4,    36,    10,
      29,   133,   112,   116,   116,   131,   131,     6,    32,    33,
      34,    47,    72,    74,   103,   106,   107,   108,   109,   110,
      76,    78,    80,    82,    71,    93,    97,    88,   138,   139,
      36,     9,    10,    22,   124,   125,   102,   105,    97,    15,
      17,    35,   122,    97,    97,   105,   105,    97,     4,    24,
      31,   113,    24,    51,   115,    51,    59,   104,    60,     4,
      36,    36,    36,    36,    84,     4,    87,    90,   140,    97,
       4,    99,    98,     4,    37,    11,    97,     4,    97,    97,
      23,    25,    97,    11,     4,   100,     4,     4,     4,    60,
      97,    97,    97,    97,    97,    89,     4,    97,   131,   131,
      97,    93,   101,    97,    97,    37,     4,    50,    54,    97,
     105,    97,    97,    97,    97,    91,    97,   105,   105,    37,
      97,    97,    97,    27,   105,    97,    97,   105,    62,    97,
      97,    97,    97,    37,    11,    23,    13,    97,    37,    37,
      25,    49,    55,    58,    37,    37,    97,    37,     7,    97,
      19,    21,    97,    36,    37,    56,    97,    97,    37,    53
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    94,    95,    95,    96,    96,    96,    96,    96,    96,
      96,    96,    96,    96,    96,    96,    96,    96,    96,    96,
      96,    96,    96,    96,    96,    96,    96,    96,    97,    97,
      98,    99,   100,   101,   102,   102,   103,   104,   104,   105,
     105,   105,   105,   105,   105,   105,   106,   107,   108,   109,
     110,   111,   111,   111,   112,   112,   113,   114,   114,   115,
     116,   116,   117,   118,   119,   120,   121,   122,   123,   123,
     124,   125,   126,   127,   128,   129,   130,   131,   132,   133,
     134,   135,   136,   137,   138,   138,   139,   140,   141,   142,
     143,   144,   145,   146,   147,   148,   149
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     2,     2,     0,     1,     0,
       2,     2,     2,     2,     2,     2,     1,     9,     6,     6,
       7,     0,     2,     2,     0,     2,     5,     0,     2,     2,
       0,     2,     8,    12,     4,     4,     3,     6,     0,     2,
       5,     5,     4,     4,     7,     9,     9,     3,     5,     3,
       7,     8,     5,     4,     1,     2,     3,     3,     3,     3,
       3,     3,     3,     5,     4,     9,     8
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (currSession, YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static unsigned
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  unsigned res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location, currSession); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, Session* currSession)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  YYUSE (yylocationp);
  YYUSE (currSession);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, Session* currSession)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp, currSession);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule, Session* currSession)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       , currSession);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule, currSession); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, Session* currSession)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  YYUSE (currSession);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (Session* currSession)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.
       'yyls': related to locations.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yyls1, yysize * sizeof (*yylsp),
                    &yystacksize);

        yyls = yyls1;
        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 28:
#line 122 "compilerNome/parser.y" /* yacc.c:1648  */
    {
        (yyval.string) = strdup((yyvsp[0].string));
    }
#line 1801 "E:/DevGra/nome/compilerNome/parser.cpp" /* yacc.c:1648  */
    break;

  case 29:
#line 125 "compilerNome/parser.y" /* yacc.c:1648  */
    {
        std::string exprStr = strdup((yyvsp[0].string));
        exprStr.erase(0, 6);
        exprStr.erase(exprStr.size() - 1);
        (yyval.string) = strdup(exprStr.c_str());
    }
#line 1812 "E:/DevGra/nome/compilerNome/parser.cpp" /* yacc.c:1648  */
    break;

  case 30:
#line 134 "compilerNome/parser.y" /* yacc.c:1648  */
    {
        Reader* currReader = createReader(currSession);
        if (!currReader->isUnique(strdup((yyvsp[0].string)))){
          nomerror(currSession, "Duplicate construct name.");
          YYABORT;
        }
        nameUnique = strdup((yyvsp[0].string));
    }
#line 1825 "E:/DevGra/nome/compilerNome/parser.cpp" /* yacc.c:1648  */
    break;

  case 31:
#line 144 "compilerNome/parser.y" /* yacc.c:1648  */
    {
        for (FaceNew* fa : currentMeshFaces2){
            string currentF = strdup((yyvsp[0].string));
          if(!currentF.compare(fa->name)){
            nomerror(currSession, "Duplicate construct name.");
            YYABORT;
          }
        }
        nameUniqueFaceMesh = strdup((yyvsp[0].string));
    }
#line 1840 "E:/DevGra/nome/compilerNome/parser.cpp" /* yacc.c:1648  */
    break;

  case 32:
#line 156 "compilerNome/parser.y" /* yacc.c:1648  */
    {
        for (InstanceNew* fa : currentGroup2){
            string currentF = strdup((yyvsp[0].string));
          if(!currentF.compare(fa->name)){
            nomerror(currSession, "Duplicate construct name.");
            YYABORT;
          }
        }
        nameUniqueInstanceGroup= strdup((yyvsp[0].string));
    }
#line 1855 "E:/DevGra/nome/compilerNome/parser.cpp" /* yacc.c:1648  */
    break;

  case 33:
#line 178 "compilerNome/parser.y" /* yacc.c:1648  */
    {
        (yyval.numPos).string = strdup((yyvsp[0].string));
        (yyval.numPos).number = nomcolumn;
    }
#line 1864 "E:/DevGra/nome/compilerNome/parser.cpp" /* yacc.c:1648  */
    break;

  case 35:
#line 189 "compilerNome/parser.y" /* yacc.c:1648  */
    {
        tempVariables2.push_back((yyvsp[0].string));
    }
#line 1872 "E:/DevGra/nome/compilerNome/parser.cpp" /* yacc.c:1648  */
    break;

  case 36:
#line 195 "compilerNome/parser.y" /* yacc.c:1648  */
    {
        if (surfaceFromArg.length() == 0){
          surfaceFromArg = strdup((yyvsp[0].string));
        }
    }
#line 1882 "E:/DevGra/nome/compilerNome/parser.cpp" /* yacc.c:1648  */
    break;

  case 37:
#line 202 "compilerNome/parser.y" /* yacc.c:1648  */
    {(yyval.boolean) = false;}
#line 1888 "E:/DevGra/nome/compilerNome/parser.cpp" /* yacc.c:1648  */
    break;

  case 38:
#line 203 "compilerNome/parser.y" /* yacc.c:1648  */
    {
        (yyval.boolean) = true;
    }
#line 1896 "E:/DevGra/nome/compilerNome/parser.cpp" /* yacc.c:1648  */
    break;

  case 46:
#line 213 "compilerNome/parser.y" /* yacc.c:1648  */
    {
      Reverse* currReverse = createReverse();
      currentTransformations2.push_back(currReverse);
    }
#line 1905 "E:/DevGra/nome/compilerNome/parser.cpp" /* yacc.c:1648  */
    break;

  case 47:
#line 220 "compilerNome/parser.y" /* yacc.c:1648  */
    {
        double *x = (double*) malloc(sizeof(double));
        double *y = (double*) malloc(sizeof(double));
        double *z = (double*) malloc(sizeof(double));
        double *angle = (double*) malloc(sizeof(double));

        double *currentValSet = (double*) malloc(sizeof(double));
        parseGetBankVal((yyvsp[-6].string), currSession, currentValSet, nomlineno);
        *x = *currentValSet;
        parseGetBankVal((yyvsp[-5].string), currSession, currentValSet, nomlineno);
        *y = *currentValSet;
        parseGetBankVal((yyvsp[-4].string), currSession, currentValSet, nomlineno);
        *z = *currentValSet;
        parseGetBankVal((yyvsp[-1].string), currSession, currentValSet, nomlineno);
        *angle = *currentValSet;

        Rotate* currRotate = createRotate(x, y, z, angle);
        currRotate->xStr = strdup((yyvsp[-6].string));
        currRotate->yStr = strdup((yyvsp[-5].string));
        currRotate->zStr = strdup((yyvsp[-4].string));
        currRotate->angleStr = strdup((yyvsp[-1].string));

        currentTransformations2.push_back(currRotate);

    }
#line 1935 "E:/DevGra/nome/compilerNome/parser.cpp" /* yacc.c:1648  */
    break;

  case 48:
#line 249 "compilerNome/parser.y" /* yacc.c:1648  */
    {
        double *x = (double*) malloc(sizeof(double));
        double *y = (double*) malloc(sizeof(double));
        double *z = (double*) malloc(sizeof(double));

        double *currentValSet = (double*) malloc(sizeof(double));
        parseGetBankVal((yyvsp[-3].string), currSession, currentValSet, nomlineno);
        *x = *currentValSet;
        parseGetBankVal((yyvsp[-2].string), currSession, currentValSet, nomlineno);
        *y = *currentValSet;
        parseGetBankVal((yyvsp[-1].string), currSession, currentValSet, nomlineno);
        *z = *currentValSet;

        Translate* currTranslate = createTranslate(x, y, z);
        currTranslate->xStr = strdup((yyvsp[-3].string));
        currTranslate->yStr = strdup((yyvsp[-2].string));
        currTranslate->zStr = strdup((yyvsp[-1].string));

        currentTransformations2.push_back(currTranslate);
    }
#line 1960 "E:/DevGra/nome/compilerNome/parser.cpp" /* yacc.c:1648  */
    break;

  case 49:
#line 273 "compilerNome/parser.y" /* yacc.c:1648  */
    {
        double *x = (double*) malloc(sizeof(double));
        double *y = (double*) malloc(sizeof(double));
        double *z = (double*) malloc(sizeof(double));

        double *currentValSet = (double*) malloc(sizeof(double));
        parseGetBankVal((yyvsp[-3].string), currSession, currentValSet, nomlineno);
        *x = *currentValSet;
        parseGetBankVal((yyvsp[-2].string), currSession, currentValSet, nomlineno);
        *y = *currentValSet;
        parseGetBankVal((yyvsp[-1].string), currSession, currentValSet, nomlineno);
        *z = *currentValSet;

        Scale* currScale = createScale(x, y, z);
        currScale->xStr = strdup((yyvsp[-3].string));
        currScale->yStr = strdup((yyvsp[-2].string));
        currScale->zStr = strdup((yyvsp[-1].string));

        currentTransformations2.push_back(currScale);
    }
#line 1985 "E:/DevGra/nome/compilerNome/parser.cpp" /* yacc.c:1648  */
    break;

  case 50:
#line 297 "compilerNome/parser.y" /* yacc.c:1648  */
    {
        double *currentValSet = (double*) malloc(sizeof(double));
        parseGetBankVal((yyvsp[-4].string), currSession, currentValSet, nomlineno);
        double x = *currentValSet;
        parseGetBankVal((yyvsp[-3].string), currSession, currentValSet, nomlineno);
        double y = *currentValSet;
        parseGetBankVal((yyvsp[-2].string), currSession, currentValSet, nomlineno);
        double z = *currentValSet;
        parseGetBankVal((yyvsp[-1].string), currSession, currentValSet, nomlineno);
        double w = *currentValSet;

    }
#line 2002 "E:/DevGra/nome/compilerNome/parser.cpp" /* yacc.c:1648  */
    break;

  case 56:
#line 321 "compilerNome/parser.y" /* yacc.c:1648  */
    {
        Reader* currReader = createReader(currSession);

        string instanceName = strdup((yyvsp[-3].string));
        string lookFor = strdup((yyvsp[-2].string));

        MeshNew * currentMesh = currReader->getMesh((yyvsp[-2].string));

        InstanceNew* newInstance = NULL;
        bool onlyCreateNewVertices = false;
        if (currentMesh != NULL) {
            //if (currentTransformations2.size() > 0){
              onlyCreateNewVertices = true;
            //}
            newInstance = createInstance(currentMesh, currSession->verts, currReader, true, false, onlyCreateNewVertices, currSession, false);
            newInstance->currSession = currSession;
        }
        else{
            GroupNew * currentGroup2 = currReader->getGroup((yyvsp[-2].string));
            if (currentGroup2 != NULL) {
                newInstance = createInstance(currentGroup2, currSession->verts, currReader, currSession);
                newInstance->currSession = currSession;
            }
            else{
                nomerror(currSession, "Incorrect vertex, face, or mesh name");
                YYABORT;
            }
        }

        newInstance->setName(nameUniqueInstanceGroup);
        newInstance->transformations = currentTransformations2;
        currentTransformations2.clear();

        for (TransformationNew * t : newInstance->transformations){
            newInstance->applyTransformation(t);
        }

        /*for (InstanceNew * i : newInstance->listInstances){
          for (TransformationNew * t : i->transformations){
              i->applyTransformation(t);
          }
        }*/

        string surfaceName = surfaceFromArg;
        // Check if a surface has been applied.
        if (surfaceName.length() != 0){
            Surface * currentSurface = currReader->surf(surfaceFromArg);
            if (currentSurface != NULL) {
                setSurface(newInstance, currentSurface);
            }
            else{
                nomerror(currSession, "Incorrect surface name");
                YYABORT;
            }
        }
        currentGroup2.push_back(newInstance);
        surfaceFromArg = "";
    }
#line 2065 "E:/DevGra/nome/compilerNome/parser.cpp" /* yacc.c:1648  */
    break;

  case 59:
#line 387 "compilerNome/parser.y" /* yacc.c:1648  */
    {
        string instanceName = strdup((yyvsp[0].string));
    }
#line 2073 "E:/DevGra/nome/compilerNome/parser.cpp" /* yacc.c:1648  */
    break;

  case 62:
#line 397 "compilerNome/parser.y" /* yacc.c:1648  */
    {
        double *subdivision = (double*) malloc(sizeof(double));

        double *currentValSet = (double*) malloc(sizeof(double));
        parseGetBankVal((yyvsp[-1].string), currSession, currentValSet, nomlineno);
        *subdivision = *currentValSet;

        std::string subdivType(strdup((yyvsp[-3].string)));
        if (subdivType.compare("SLF_CATMULL_CLARK") == 0){
          currSession->subdivisionType = 0;
        } else if (subdivType.compare("WEIGHTED_FACEPOINT_SLF_CATMULL_CLARK") == 0){
          currSession->subdivisionType = 1;
        }

        SubdivisionNew* currSubdivision = createSubdivision(strdup((yyvsp[-5].string)), strdup((yyvsp[-3].string)), subdivision);
        currSession->subdivisions.push_back(currSubdivision);
    }
#line 2095 "E:/DevGra/nome/compilerNome/parser.cpp" /* yacc.c:1648  */
    break;

  case 63:
#line 417 "compilerNome/parser.y" /* yacc.c:1648  */
    {
        double *min = (double*) malloc(sizeof(double));
        double *max = (double*) malloc(sizeof(double));
        double *step = (double*) malloc(sizeof(double));

        double *currentValSet = (double*) malloc(sizeof(double));
        parseGetBankVal((yyvsp[-5].string), currSession, currentValSet, nomlineno);
        *min = *currentValSet;
        parseGetBankVal((yyvsp[-3].string), currSession, currentValSet, nomlineno);
        *max = *currentValSet;
        parseGetBankVal((yyvsp[-1].string), currSession, currentValSet, nomlineno);
        *step = *currentValSet;

        std::string offsetType(strdup((yyvsp[-7].string)));
        if (offsetType.compare("REGULAR") == 0){
          currSession->offsetType = 0;
        } else if (offsetType.compare("WEIGHTED") == 0){
          currSession->offsetType = 1;
        }

        OffsetNew* currOffset = createOffset(strdup((yyvsp[-10].string)), min, max, step);

        currSession->offsets.push_back(currOffset);
    }
#line 2124 "E:/DevGra/nome/compilerNome/parser.cpp" /* yacc.c:1648  */
    break;

  case 64:
#line 446 "compilerNome/parser.y" /* yacc.c:1648  */
    {

        MeshNew* currMesh = createMesh();

        for (std::list<FaceNew*>::iterator it=currentMeshFaces2.begin(); it != currentMeshFaces2.end(); ++it){
            currMesh->faces.push_back(*it);
        }

        for (std::list<Vert*>::iterator it=currentMeshVertices2.begin(); it != currentMeshVertices2.end(); ++it){
            currMesh->verts.push_back(*it);
        }

        for (std::list<EdgeNew*>::iterator it=currentMeshEdges2.begin(); it != currentMeshEdges2.end(); ++it){
            currMesh->edges.push_back(*it);
        }

        currMesh->setName(nameUnique);
        currSession->meshes.push_back(currMesh);

        currentMeshFaces2.clear();
        currentMeshEdges2.clear();
        currentMeshVertices2.clear();
        }
#line 2152 "E:/DevGra/nome/compilerNome/parser.cpp" /* yacc.c:1648  */
    break;

  case 65:
#line 473 "compilerNome/parser.y" /* yacc.c:1648  */
    {
        GroupNew* currGroup = createGroup(currentGroup2);
        currGroup->setName(nameUnique);
        currSession->groups.push_back(currGroup);
        currentGroup2.clear();
        }
#line 2163 "E:/DevGra/nome/compilerNome/parser.cpp" /* yacc.c:1648  */
    break;

  case 66:
#line 489 "compilerNome/parser.y" /* yacc.c:1648  */
    {
        Reader* currReader = createReader(currSession);

        for (std::string currFace : tempFaceDelete2){
            currReader->deleteFace(currReader->getFace(currFace));
        }

        tempFaceDelete2.clear();
        }
#line 2177 "E:/DevGra/nome/compilerNome/parser.cpp" /* yacc.c:1648  */
    break;

  case 67:
#line 502 "compilerNome/parser.y" /* yacc.c:1648  */
    {
        string currentSetName = (yyvsp[-4].string);
        double currentSetValue = (double)atof((yyvsp[-3].numPos).string);
        double *currentValSet = (double*) malloc(sizeof(double));
        parseGetBankVal((yyvsp[-2].string), currSession, currentValSet, nomlineno);
        double currentSetStart = *currentValSet;
        parseGetBankVal((yyvsp[-1].string), currSession, currentValSet, nomlineno);
        double currentSetEnd = *currentValSet;
        parseGetBankVal((yyvsp[0].string), currSession, currentValSet, nomlineno);
        double currentSetStepSize = *currentValSet;
        string currentSetValueString = (yyvsp[-3].numPos).string;


        int begPos = (yyvsp[-3].numPos).number-currentSetValueString.length();
        int lengthValChar = currentSetValueString.length();

        SetNew * currentSet = createSet(currentSetName, currentSetValue, currentSetStart, currentSetEnd, currentSetStepSize, begPos, lengthValChar);

        currentSetList2.push_back(currentSet);
        }
#line 2202 "E:/DevGra/nome/compilerNome/parser.cpp" /* yacc.c:1648  */
    break;

  case 70:
#line 530 "compilerNome/parser.y" /* yacc.c:1648  */
    {
    Reader* currReader = createReader(currSession);

    // Create list of vertices of face.
    std::list<Vert*> verticesPolyline;
    for (std::vector<string>::iterator it = tempVariables2.begin() ; it != tempVariables2.end(); ++it){
        Vert * currentVertex = currReader->getVert(*it);
        if (currentVertex != NULL) {
            verticesPolyline.push_back(currentVertex);
            currentMeshVertices2.push_back(currentVertex);
        }
        else{
            nomerror(currSession, "Incorrect vertex name");
            YYABORT;
        }
    }

    PolylineNew* currPolyline = createPolylineNew(verticesPolyline);
    for (EdgeNew* e : currPolyline->edges){
      currentMeshEdges2.push_back(e);
    }

    currPolyline->setName(nameUnique);

    string surfaceName = surfaceFromArg;
    // Check if a surface has been applied.
    if (surfaceName.length() != 0){
        Surface * currentSurface = currReader->surf(surfaceFromArg);
        if (currentSurface != NULL) {
            currPolyline->setSurface(currentSurface);
        }
        else{
            nomerror(currSession, "Incorrect surface name");
            YYABORT;
        }
    }
    currentMeshPolyline.push_back(currPolyline);

    tempVariables2.clear();
    surfaceFromArg = "";
}
#line 2248 "E:/DevGra/nome/compilerNome/parser.cpp" /* yacc.c:1648  */
    break;

  case 71:
#line 575 "compilerNome/parser.y" /* yacc.c:1648  */
    {
        Reader* currReader = createReader(currSession);

        std::list<Vert*> verticesFace;
        //std::cout << "FACE MESH" << std::endl;
        for (std::vector<string>::iterator it = tempVariables2.begin() ; it != tempVariables2.end(); ++it){
            Vert * currentVertex = currReader->getVert(*it);
            if (currentVertex != NULL) {
                verticesFace.push_back(currentVertex);
                bool found = false;
                for (Vert* currentMeshVertex: currentMeshVertices2){
                    if (currentMeshVertex->index == currentVertex->index){
                        found = true;
                    }
                }
                if (found == false){
                    currentMeshVertices2.push_back(currentVertex);
                }

            }
            else{
                std::string errorMessage = "Incorrect vertex name " + *it;
                const char * errorMessageC = errorMessage.c_str();
                nomerror(currSession, errorMessageC);
                YYABORT;
            }
        }

        FaceNew * newFace = createFace(verticesFace, &currentMeshEdges2, currReader, false);
        setName(newFace, nameUniqueFaceMesh);

        string surfaceName = surfaceFromArg;
        // Check if a surface has been applied.
        if (surfaceName.length() != 0){
            Surface * currentSurface = currReader->surf(surfaceFromArg);
            if (currentSurface != NULL) {
                setSurface(newFace, currentSurface);
            }
            else{
                nomerror(currSession, "Incorrect surface name");
                YYABORT;
            }
        }

        currentMeshFaces2.push_back(newFace);

        tempVariables2.clear();
        surfaceFromArg = "";
    }
#line 2302 "E:/DevGra/nome/compilerNome/parser.cpp" /* yacc.c:1648  */
    break;

  case 72:
#line 628 "compilerNome/parser.y" /* yacc.c:1648  */
    {
        BankNew * currentBank2 = createBank();
        currentBank2->name = strdup((yyvsp[-2].string));
        currentBank2->sets = currentSetList2;
        currSession->banks.push_back(currentBank2);
        currentSetList2.clear();
        }
#line 2314 "E:/DevGra/nome/compilerNome/parser.cpp" /* yacc.c:1648  */
    break;

  case 73:
#line 639 "compilerNome/parser.y" /* yacc.c:1648  */
    {
        double *epsilonVal = (double*) malloc(sizeof(double));

        double *currentValSet = (double*) malloc(sizeof(double));
        parseGetBankVal((yyvsp[-1].string), currSession, currentValSet, nomlineno);
        *epsilonVal = *currentValSet;
        currSession->epsilon = *epsilonVal;
        currSession->epsilonStr = strdup((yyvsp[-1].string));
    }
#line 2328 "E:/DevGra/nome/compilerNome/parser.cpp" /* yacc.c:1648  */
    break;

  case 74:
#line 651 "compilerNome/parser.y" /* yacc.c:1648  */
    {
        string name = (yyvsp[-5].string);
        double *num = (double*) malloc(sizeof(double));
        double *rad = (double*) malloc(sizeof(double));

        double *currentValSet = (double*) malloc(sizeof(double));
        parseGetBankVal((yyvsp[-3].string), currSession, currentValSet, nomlineno);
        *num = *currentValSet;

        parseGetBankVal((yyvsp[-2].string), currSession, currentValSet, nomlineno);
        *rad = *currentValSet;

        CircleNew* currCircle = createCircle(num, rad);
        currCircle->setName(nameUnique);
        currCircle->numStr = strdup((yyvsp[-3].string));
        currCircle->radStr = strdup((yyvsp[-2].string));
        currCircle->currSession = currSession;
        currCircle->createVertEdgeCircle();

        currSession->circles.push_back(currCircle);
    }
#line 2354 "E:/DevGra/nome/compilerNome/parser.cpp" /* yacc.c:1648  */
    break;

  case 75:
#line 676 "compilerNome/parser.y" /* yacc.c:1648  */
    {
        Reader* currReader = createReader(currSession);

        string name = (yyvsp[-7].string);
        double *n = (double*) malloc(sizeof(double));
        double *ro = (double*) malloc(sizeof(double));
        double *ratio = (double*) malloc(sizeof(double));
        double *h = (double*) malloc(sizeof(double));

        double *currentValSet = (double*) malloc(sizeof(double));
        parseGetBankVal((yyvsp[-5].string), currSession, currentValSet, nomlineno);
        *n = *currentValSet;
        parseGetBankVal((yyvsp[-4].string), currSession, currentValSet, nomlineno);
        *ro = *currentValSet;
        parseGetBankVal((yyvsp[-3].string), currSession, currentValSet, nomlineno);
        *ratio = *currentValSet;
        parseGetBankVal((yyvsp[-2].string), currSession, currentValSet, nomlineno);
        *h = *currentValSet;

        TunnelNew* currTunnel = createTunnel(n, ro, ratio, h, currReader);
        currTunnel->setName(nameUnique);
        currTunnel->nStr = strdup((yyvsp[-5].string));
        currTunnel->roStr = strdup((yyvsp[-4].string));
        currTunnel->ratioStr = strdup((yyvsp[-3].string));
        currTunnel->hStr = strdup((yyvsp[-2].string));
        currTunnel->currSession = currSession;

        currSession->tunnels.push_back(currTunnel);
        }
#line 2388 "E:/DevGra/nome/compilerNome/parser.cpp" /* yacc.c:1648  */
    break;

  case 76:
#line 710 "compilerNome/parser.y" /* yacc.c:1648  */
    {
        Reader* currReader = createReader(currSession);

        string name = (yyvsp[-7].string);
        double *n = (double*) malloc(sizeof(double));
        double *ro = (double*) malloc(sizeof(double));
        double *ratio = (double*) malloc(sizeof(double));
        double *h = (double*) malloc(sizeof(double));

        double *currentValSet = (double*) malloc(sizeof(double));
        parseGetBankVal((yyvsp[-5].string), currSession, currentValSet, nomlineno);
        *n = *currentValSet;
        parseGetBankVal((yyvsp[-4].string), currSession, currentValSet, nomlineno);
        *ro = *currentValSet;
        parseGetBankVal((yyvsp[-3].string), currSession, currentValSet, nomlineno);
        *ratio = *currentValSet;
        parseGetBankVal((yyvsp[-2].string), currSession, currentValSet, nomlineno);
        *h = *currentValSet;

        FunnelNew* currFunnel = createFunnel(n, ro, ratio, h, currReader);
        currFunnel->setName(nameUnique);

        currFunnel->nStr = strdup((yyvsp[-5].string));
        currFunnel->roStr = strdup((yyvsp[-4].string));
        currFunnel->ratioStr = strdup((yyvsp[-3].string));
        currFunnel->hStr = strdup((yyvsp[-2].string));
        currFunnel->currSession = currSession;

        currSession->funnels.push_back(currFunnel);
        }
#line 2423 "E:/DevGra/nome/compilerNome/parser.cpp" /* yacc.c:1648  */
    break;

  case 77:
#line 744 "compilerNome/parser.y" /* yacc.c:1648  */
    {
        }
#line 2430 "E:/DevGra/nome/compilerNome/parser.cpp" /* yacc.c:1648  */
    break;

  case 78:
#line 750 "compilerNome/parser.y" /* yacc.c:1648  */
    {
        Reader* currReader = createReader(currSession);

        std::list<Vert*> verticesFace;
        for (std::vector<string>::iterator it = tempVariables2.begin() ; it != tempVariables2.end(); ++it){
            Vert * currentVertex = currReader->getVert(*it);
            if (currentVertex != NULL) {
                verticesFace.push_back(currentVertex);
            }
            else{
                nomerror(currSession, "Incorrect vertex name");
                YYABORT;
            }
        }

        FaceNew * newFace = createFace(verticesFace, &(currSession->edges), currReader, false);

        setName(newFace, nameUnique);


        string surfaceName = surfaceFromArg;
        // Check if a surface has been applied.
        if (surfaceName.length() != 0){
            Surface * currentSurface = currReader->surf(surfaceFromArg);
            if (currentSurface != NULL) {
                setSurface(newFace, currentSurface);
            }
            else{
                nomerror(currSession, "Incorrect surface name");
                YYABORT;
            }
        }

        currSession->faces.push_back(newFace);

        tempVariables2.clear();
        surfaceFromArg = "";
        }
#line 2473 "E:/DevGra/nome/compilerNome/parser.cpp" /* yacc.c:1648  */
    break;

  case 79:
#line 792 "compilerNome/parser.y" /* yacc.c:1648  */
    {
        tempFaceDelete2.push_back((yyvsp[-1].string));
        }
#line 2481 "E:/DevGra/nome/compilerNome/parser.cpp" /* yacc.c:1648  */
    break;

  case 80:
#line 798 "compilerNome/parser.y" /* yacc.c:1648  */
    {
    double *slices = (double*) malloc(sizeof(double));
    Reader* currReader = createReader(currSession);


    BezierCurveNew* currBezierCurve = createBezierCurveNew();
    currBezierCurve->setName(nameUnique);
    double *currentValSet = (double*) malloc(sizeof(double));
    //parseGetBankVal($<string>5, currSession, currentValSet);
    //*slices = *currentValSet;
    *slices = 0;
    currBezierCurve->segments = slices;
    currBezierCurve->segmentsStr = strdup((yyvsp[-2].string));
    currBezierCurve->currSession = currSession;

    // Create list of vertices of face.
    for (std::vector<string>::iterator it = tempVariables2.begin() ; it != tempVariables2.end(); ++it){
        Vert * currentVertex = currReader->getVert(*it);
        if (currentVertex != NULL) {
            currBezierCurve->proxy.push_back(currentVertex);
        }
        else{
            nomerror(currSession, "Incorrect vertex name");
            YYABORT;
        }
    }

    currBezierCurve->updateBezierCurve();

    string surfaceName = surfaceFromArg;
    // Check if a surface has been applied.
    if (surfaceName.length() != 0){
        Surface * currentSurface = currReader->surf(surfaceFromArg);
        if (currentSurface != NULL) {
            currBezierCurve->setSurface(currentSurface);
        }
        else{
            nomerror(currSession, "Incorrect surface name");
            YYABORT;
        }
    }

    currSession->bezierCurves.push_back(currBezierCurve);
    tempVariables2.clear();
    surfaceFromArg = "";
}
#line 2532 "E:/DevGra/nome/compilerNome/parser.cpp" /* yacc.c:1648  */
    break;

  case 81:
#line 847 "compilerNome/parser.y" /* yacc.c:1648  */
    {
    if ((yyvsp[-7].intNumber) != (yyvsp[0].intNumber)) {
        nomerror(currSession, "bspline and endbspline do not have the same number.");
        YYABORT;
    }

    Reader* currReader = createReader(currSession);

    BSplineNew* currBSpline = createBSplineNew();
    currBSpline->setName(nameUnique);
    currBSpline->set_order((yyvsp[-7].intNumber));
    double *currentValSet = (double*) malloc(sizeof(double));
    parseGetBankVal((yyvsp[-2].string), currSession, currentValSet, nomlineno);
    currBSpline->segments = -1;
    currBSpline->currSession = currSession;

    currBSpline->segmentsStr = strdup((yyvsp[-2].string));


    // Create list of vertices of face.
    for (std::vector<string>::iterator it = tempVariables2.begin() ; it != tempVariables2.end(); ++it){
        Vert * currentVertex = currReader->getVert(*it);
        if (currentVertex != NULL) {
            currBSpline->proxy.push_back(currentVertex);
        }
        else{
            nomerror(currSession, "Incorrect vertex name");
            YYABORT;
        }
    }

    currBSpline->isLoop = (yyvsp[-4].boolean);

    if (currBSpline->order > currBSpline->proxy.size()){
      std::string errorStr = "bspline order (";
      errorStr += currBSpline->order;
      errorStr += ") must be <= #controlpoints (";
      errorStr += currBSpline->proxy.size();
      errorStr += ").";
      nomerror(currSession, errorStr.c_str());
      YYABORT;
    }

    currBSpline->updateBSpline();

    string surfaceName = surfaceFromArg;
    // Check if a surface has been applied.
    if (surfaceName.length() != 0){
        Surface * currentSurface = currReader->surf(surfaceFromArg);
        if (currentSurface != NULL) {
            currBSpline->setSurface(currentSurface);
        }
        else{
            nomerror(currSession, "Incorrect surface name");
            YYABORT;
        }
    }


    currSession->bsplines.push_back(currBSpline);

    tempVariables2.clear();
    surfaceFromArg = "";
  }
#line 2601 "E:/DevGra/nome/compilerNome/parser.cpp" /* yacc.c:1648  */
    break;

  case 82:
#line 914 "compilerNome/parser.y" /* yacc.c:1648  */
    {
        Reader* currReader = createReader(currSession);

        // Create list of vertices of face.
        std::list<Vert*> verticesPolyline;
        for (std::vector<string>::iterator it = tempVariables2.begin() ; it != tempVariables2.end(); ++it){
            Vert * currentVertex = currReader->getVert(*it);
            if (currentVertex != NULL) {
                verticesPolyline.push_back(currentVertex);
            }
            else{
                nomerror(currSession, "Incorrect vertex name");
                YYABORT;
            }
        }

        PolylineNew* currPolyline = createPolylineNew(verticesPolyline);
        currPolyline->setName(nameUnique);

        string surfaceName = surfaceFromArg;
        // Check if a surface has been applied.
        if (surfaceName.length() != 0){
            Surface * currentSurface = currReader->surf(surfaceFromArg);
            if (currentSurface != NULL) {
                currPolyline->setSurface(currentSurface);
            }
            else{
                nomerror(currSession, "Incorrect surface name");
                YYABORT;
            }
        }
        currSession->polylines.push_back(currPolyline);
        tempVariables2.clear();
        surfaceFromArg = "";
        }
#line 2641 "E:/DevGra/nome/compilerNome/parser.cpp" /* yacc.c:1648  */
    break;

  case 83:
#line 952 "compilerNome/parser.y" /* yacc.c:1648  */
    {
	       try
		   {
		       Sweep* sweep = new Sweep(currSession, currentSweepInitializer);
			   sweep->setName(nameUnique);
			   currSession->meshes.push_back(sweep);
			   currentSweepInitializer.Clear();
		   }
		   catch (const std::invalid_argument& e)
		   {
               nomerror(currSession, e.what());
               YYABORT;
		   }
	   }
#line 2660 "E:/DevGra/nome/compilerNome/parser.cpp" /* yacc.c:1648  */
    break;

  case 86:
#line 972 "compilerNome/parser.y" /* yacc.c:1648  */
    {
				Reader* currReader = createReader(currSession);
				MeshNew* path = currReader->getMesh((yyvsp[-1].string));
				if (!path || !dynamic_cast<ISweepPath*>(path))
				{
					//The target path is not a valid path
					nomerror(currSession, "Sweep path not found or invalid.");
					YYABORT;
				}
				currentSweepInitializer.PathInit.Path = dynamic_cast<ISweepPath*>(path);
			}
#line 2676 "E:/DevGra/nome/compilerNome/parser.cpp" /* yacc.c:1648  */
    break;

  case 87:
#line 985 "compilerNome/parser.y" /* yacc.c:1648  */
    {
						Reader* currReader = createReader(currSession);
						MeshNew* path = currReader->getMesh((yyvsp[-1].string));
						if (!path || !dynamic_cast<ISweepPath*>(path))
						{
							//The target path is not a valid path
							nomerror(currSession, "Sweep cross section not found or invalid.");
							YYABORT;
						}
						SweepCrosssectionInitializer init;
						init.CrossSection = dynamic_cast<ISweepPath*>(path);
						currentSweepInitializer.CrossSectionInits.push_back(init);
					}
#line 2694 "E:/DevGra/nome/compilerNome/parser.cpp" /* yacc.c:1648  */
    break;

  case 88:
#line 1001 "compilerNome/parser.y" /* yacc.c:1648  */
    {
      Reader* currReader = createReader(currSession);
      string surfaceName = surfaceFromArg;
      // Check if a surface has been applied.
      if (surfaceName.length() != 0){
          Surface * currentSurface = currReader->surf(surfaceFromArg);
          if (currentSurface != NULL) {
              currSession-> foreColor = currentSurface;
          }
          else{
              nomerror(currSession, "Incorrect surface name");
              YYABORT;
          }
      }
      surfaceFromArg = "";
    }
#line 2715 "E:/DevGra/nome/compilerNome/parser.cpp" /* yacc.c:1648  */
    break;

  case 89:
#line 1020 "compilerNome/parser.y" /* yacc.c:1648  */
    {
      Reader* currReader = createReader(currSession);
      string surfaceName = surfaceFromArg;
      // Check if a surface has been applied.
      if (surfaceName.length() != 0){
          Surface * currentSurface = currReader->surf(surfaceFromArg);
          if (currentSurface != NULL) {
              currSession-> backColor = currentSurface;
          }
          else{
              nomerror(currSession, "Incorrect surface name");
              YYABORT;
          }
      }
      surfaceFromArg = "";
    }
#line 2736 "E:/DevGra/nome/compilerNome/parser.cpp" /* yacc.c:1648  */
    break;

  case 90:
#line 1039 "compilerNome/parser.y" /* yacc.c:1648  */
    {
      Reader* currReader = createReader(currSession);
      string surfaceName = surfaceFromArg;
      // Check if a surface has been applied.
      if (surfaceName.length() != 0){
          Surface * currentSurface = currReader->surf(surfaceFromArg);
          if (currentSurface != NULL) {
              currSession-> insideColor = currentSurface;
          }
          else{
              nomerror(currSession, "Incorrect surface name");
              YYABORT;
          }
      }
      surfaceFromArg = "";
    }
#line 2757 "E:/DevGra/nome/compilerNome/parser.cpp" /* yacc.c:1648  */
    break;

  case 91:
#line 1058 "compilerNome/parser.y" /* yacc.c:1648  */
    {
      Reader* currReader = createReader(currSession);
      string surfaceName = surfaceFromArg;
      // Check if a surface has been applied.
      if (surfaceName.length() != 0){
          Surface * currentSurface = currReader->surf(surfaceFromArg);
          if (currentSurface != NULL) {
              currSession-> outsideColor = currentSurface;
          }
          else{
              nomerror(currSession, "Incorrect surface name");
              YYABORT;
          }
      }
      surfaceFromArg = "";
    }
#line 2778 "E:/DevGra/nome/compilerNome/parser.cpp" /* yacc.c:1648  */
    break;

  case 92:
#line 1077 "compilerNome/parser.y" /* yacc.c:1648  */
    {
      Reader* currReader = createReader(currSession);
      string surfaceName = surfaceFromArg;
      // Check if a surface has been applied.
      if (surfaceName.length() != 0){
          Surface * currentSurface = currReader->surf(surfaceFromArg);
          if (currentSurface != NULL) {
              currSession-> offsetColor = currentSurface;
          }
          else{
              nomerror(currSession, "Incorrect surface name");
              YYABORT;
          }
      }
      surfaceFromArg = "";
    }
#line 2799 "E:/DevGra/nome/compilerNome/parser.cpp" /* yacc.c:1648  */
    break;

  case 93:
#line 1096 "compilerNome/parser.y" /* yacc.c:1648  */
    {
        Reader* currReader = createReader(currSession);

        string instanceName = nameUnique;
        string lookFor = strdup((yyvsp[-2].string));

        MeshNew * currentMesh = currReader->getMesh((yyvsp[-2].string));

        InstanceNew* newInstance = NULL;
        bool onlyCreateNewVertices = false;
        if (currentMesh != NULL) {
            //if (currentTransformations2.size() > 0){
              onlyCreateNewVertices = true;
            //}
            newInstance = createInstance(currentMesh, currSession->verts, currReader, true, false, onlyCreateNewVertices, currSession, true);
            newInstance->currSession = currSession;
        }
        else{
            GroupNew * currentGroup2 = currReader->getGroup((yyvsp[-2].string));
            if (currentGroup2 != NULL) {
                newInstance = createInstance(currentGroup2, currSession->verts, currReader, currSession);
                newInstance->currSession = currSession;
            }
            else{
                nomerror(currSession, "Incorrect vertex, face, or mesh name");
                YYABORT;
            }
        }

        newInstance->setName(strdup((yyvsp[-3].string)));
        newInstance->transformations = currentTransformations2;
        currentTransformations2.clear();

        for (TransformationNew * t : newInstance->transformations){
            newInstance->applyTransformation(t);
        }

        string surfaceName = surfaceFromArg;
        // Check if a surface has been applied.
        if (surfaceName.length() != 0){
            Surface * currentSurface = currReader->surf(surfaceFromArg);
            if (currentSurface != NULL) {
                setSurface(newInstance, currentSurface);
            }
            else{
                nomerror(currSession, "Incorrect surface name");
                YYABORT;
            }
        }

        currSession->instances.push_back(newInstance);
        surfaceFromArg = "";
        }
#line 2857 "E:/DevGra/nome/compilerNome/parser.cpp" /* yacc.c:1648  */
    break;

  case 94:
#line 1153 "compilerNome/parser.y" /* yacc.c:1648  */
    {
          Reader* currReader = createReader(currSession);

          std::list<FaceNew*> facesObject;
          for (std::vector<string>::iterator it = tempVariables2.begin() ; it != tempVariables2.end(); ++it){
              FaceNew * currentFace = currReader->getFace(*it);
              if (currentFace != NULL) {
                  facesObject.push_back(currentFace);
              }
              else{
                  nomerror(currSession, "Incorrect face name");
                  YYABORT;
              }
          }

          MeshNew* currMesh = createMesh();

          for (std::list<FaceNew*>::iterator it=facesObject.begin(); it != facesObject.end(); ++it){
              currMesh->faces.push_back(*it);
              for (Vert* currVert : (*it)->verts){
                  currMesh->verts.push_back(currVert);
              }
              for (EdgeNew* currEdge : (*it)->edges){
                  currMesh->edges.push_back(currEdge);
              }
          }

          currMesh->setName(nameUnique);
          currSession->meshes.push_back(currMesh);

          tempVariables2.clear();
        }
#line 2894 "E:/DevGra/nome/compilerNome/parser.cpp" /* yacc.c:1648  */
    break;

  case 95:
#line 1189 "compilerNome/parser.y" /* yacc.c:1648  */
    {
        double *r = (double*) malloc(sizeof(double));
        double *g = (double*) malloc(sizeof(double));
        double *b = (double*) malloc(sizeof(double));

        double *currentValSet = (double*) malloc(sizeof(double));
        parseGetBankVal((yyvsp[-4].string), currSession, currentValSet, nomlineno);
        *r = *currentValSet;
        parseGetBankVal((yyvsp[-3].string), currSession, currentValSet, nomlineno);
        *g = *currentValSet;
        parseGetBankVal((yyvsp[-2].string), currSession, currentValSet, nomlineno);
        *b = *currentValSet;

        Surface* currSurface = createSurface(r, g, b, nameUnique);

        currSurface->rStr = strdup((yyvsp[-4].string));
        currSurface->gStr = strdup((yyvsp[-3].string));
        currSurface->bStr = strdup((yyvsp[-2].string));
        currSurface->currSession = currSession;

        currSession->surfaces.push_back(currSurface);
        }
#line 2921 "E:/DevGra/nome/compilerNome/parser.cpp" /* yacc.c:1648  */
    break;

  case 96:
#line 1215 "compilerNome/parser.y" /* yacc.c:1648  */
    {
        double *x = (double*) malloc(sizeof(double));
        double *y = (double*) malloc(sizeof(double));
        double *z = (double*) malloc(sizeof(double));

        double *currentValSet = (double*) malloc(sizeof(double));
        parseGetBankVal((yyvsp[-4].string), currSession, currentValSet, nomlineno);
        *x =*currentValSet;
        parseGetBankVal((yyvsp[-3].string), currSession, currentValSet, nomlineno);
        *y =*currentValSet;
        parseGetBankVal((yyvsp[-2].string), currSession, currentValSet, nomlineno);
        *z =*currentValSet;

        Vert * newVertex = createVert (x, y, z);
        newVertex->setName(nameUnique);

        newVertex->currSession = currSession;
        newVertex->xStr = strdup((yyvsp[-4].string));
        newVertex->yStr = strdup((yyvsp[-3].string));
        newVertex->zStr = strdup((yyvsp[-2].string));

        currSession->verts.push_back(newVertex);
        }
#line 2949 "E:/DevGra/nome/compilerNome/parser.cpp" /* yacc.c:1648  */
    break;


#line 2953 "E:/DevGra/nome/compilerNome/parser.cpp" /* yacc.c:1648  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (currSession, YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (currSession, yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }

  yyerror_range[1] = yylloc;

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, &yylloc, currSession);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, yylsp, currSession);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (currSession, YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc, currSession);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp, yylsp, currSession);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}

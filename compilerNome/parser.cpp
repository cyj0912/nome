/* A Bison parser, made by GNU Bison 3.2.1.  */

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.2.1"

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

/* First part of user prologue.  */
#line 6 "compilerNome/parser.y" /* yacc.c:338  */

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
#include <newNOME/TorusKnotNew.h>

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


#line 136 "/Volumes/macData/BerkeleyCG/nome/compilerNome/parser.cpp" /* yacc.c:338  */
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
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
#ifndef YY_NOM_VOLUMES_MACDATA_BERKELEYCG_NOME_COMPILERNOME_PARSER_HPP_INCLUDED
# define YY_NOM_VOLUMES_MACDATA_BERKELEYCG_NOME_COMPILERNOME_PARSER_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int nomdebug;
#endif
/* "%code requires" blocks.  */
#line 1 "compilerNome/parser.y" /* yacc.c:353  */

#include <newNOME/Session.h>


#line 174 "/Volumes/macData/BerkeleyCG/nome/compilerNome/parser.cpp" /* yacc.c:353  */

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
#line 88 "compilerNome/parser.y" /* yacc.c:353  */

    double intNumber;
    double number;
    const char *string;
    bool boolean;
    struct {
        const char *string; // char *strVal;
        double number;   // int posVal;
    } numPos;

#line 393 "/Volumes/macData/BerkeleyCG/nome/compilerNome/parser.cpp" /* yacc.c:353  */
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

#endif /* !YY_NOM_VOLUMES_MACDATA_BERKELEYCG_NOME_COMPILERNOME_PARSER_HPP_INCLUDED  */



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
typedef unsigned short yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short yytype_int16;
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
#  define YYSIZE_T unsigned
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

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
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
#define YYLAST   365

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  99
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  61
/* YYNRULES -- Number of rules.  */
#define YYNRULES  107
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  271

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   353

#define YYTRANSLATE(YYX)                                                \
  ((unsigned) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

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
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   111,   111,   112,   117,   117,   117,   117,   117,   117,
     118,   118,   118,   118,   118,   118,   118,   118,   119,   119,
     119,   119,   119,   119,   120,   120,   120,   120,   120,   123,
     125,   134,   144,   156,   178,   188,   190,   196,   203,   204,
     208,   209,   209,   209,   209,   209,   209,   213,   220,   249,
     273,   297,   312,   313,   313,   316,   317,   321,   382,   383,
     387,   392,   393,   397,   417,   446,   473,   489,   502,   525,
     526,   530,   575,   628,   639,   651,   675,   707,   741,   776,
     782,   824,   831,   880,   946,   984,  1000,  1000,  1001,  1002,
    1003,  1004,  1005,  1008,  1021,  1036,  1041,  1046,  1050,  1055,
    1074,  1093,  1112,  1131,  1150,  1207,  1243,  1269
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
  "TORUSKNOT", "END_TORUSKNOT", "BEG_DELETE", "END_DELETE", "GROUP",
  "END_GROUP", "TRANSLATE", "ROTATE", "MIRROR", "SET", "OPARENTHESES",
  "EPARENTHESES", "OBRACE", "EXPR", "DOLLAR", "EBRACE", "PERIOD",
  "TOKHEAT", "STATE", "TOKTARGET", "TOKTEMPERATURE", "SCALE",
  "SUBDIVISION", "END_SUBDIVISION", "SUBDIVISIONS", "TYPE", "OFFSET",
  "END_OFFSET", "MIN", "MAX", "STEP", "BSPLINE", "END_BSPLINE", "CLOSED",
  "MINIMIZETORSION", "AZIMUTH", "TWIST", "SLICES", "BEZIERCURVE",
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
  "faceMesh", "bank", "merging", "circle", "torusknot", "tunnel", "funnel",
  "parenthesisName", "face", "faceDelete", "beziercurve", "bspline",
  "polyline", "sweep", "sweep_param_pack", "sweep_path",
  "sweep_crosssection", "sweep_closed", "sweep_mintorsion",
  "sweep_azimuth", "sweep_twist", "foreground", "background",
  "insidefaces", "outsidefaces", "offsetfaces", "instance", "object",
  "surface", "point", YY_NULLPTR
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
     345,   346,   347,   348,   349,   350,   351,   352,   353
};
# endif

#define YYPACT_NINF -78

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-78)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -78,   188,   -78,     0,     0,     0,     0,     0,     1,     0,
       0,     0,     0,     0,     0,   -78,     0,     8,    40,     0,
       0,   -78,   -78,   -78,   -78,   -78,   -74,     0,   -78,   -78,
     -78,   -78,   -78,   -78,   -78,   -78,   -78,   -78,   -78,   -78,
     -78,   -78,   -78,   -78,   -78,   -78,   -78,   -78,   -78,   -78,
     -78,   -78,   -78,   -78,   -78,    43,   -78,     9,    32,     9,
     -78,    33,    34,     9,    69,    44,    49,    38,   -78,   -78,
     -78,     9,     9,   201,   142,    75,    15,     3,   -63,   -78,
      51,   104,   -78,   -78,   -63,    76,    -9,   -63,   -63,   -78,
     -78,   -63,   -63,    89,   -78,   -78,    42,     7,    12,    35,
      30,    93,    60,    61,    64,    67,   -78,   -78,   -78,   -78,
     -78,   -78,   -78,   -78,   -78,   -78,   -78,   -78,   -78,   -78,
      17,    -7,   -63,   -78,   103,     0,   -78,   -78,     2,   222,
     -63,   -78,   -78,   108,   -78,   -63,   -63,   226,   257,   -63,
     -63,   105,   117,   -78,   -78,   118,   119,   -78,   123,   -78,
      63,   -63,   -78,   -63,   -63,   -63,   -63,   -78,   -78,   -78,
     -63,   -63,   -78,   125,   129,   -78,   -78,   -78,   -78,   -78,
     -78,   -63,   -78,     9,     9,   -78,   -78,   -78,   -63,    37,
     -63,   -63,   -78,   -78,   100,   -63,   -78,   -78,   143,   -78,
      94,    95,   -63,   -78,   -63,   -63,   -63,   -63,   -78,   -78,
      55,    57,   -63,   -78,   -78,   116,   -78,   -63,   -63,   -63,
     130,   -63,   -78,   -63,   -63,   -78,   249,   -63,   -63,   -63,
     -63,   -78,   -78,   120,   253,   284,   147,   -63,   122,   124,
     -78,   -63,   261,   113,    99,   288,   -78,   126,   127,   -63,
     128,   162,   -78,   -78,   -78,   -63,   151,   152,   133,   -78,
     -78,   -63,   -78,   -78,   137,   140,   -78,   -78,   -78,   -78,
     -78,   154,   134,   -63,   -78,   -78,   -63,   141,   132,   -78,
     -78
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    58,     0,     0,     0,     0,
       0,    40,    40,    40,    40,    40,     0,     0,     3,    18,
      19,     4,    15,    14,     9,    27,    16,    17,    10,    11,
       7,    21,    20,    12,    28,    22,    23,    24,    25,    26,
      13,     8,     5,     6,    31,     0,    52,     0,     0,     0,
      69,     0,     0,     0,     0,     0,     0,     0,    55,    61,
      61,     0,     0,     0,     0,     0,     0,     0,     0,    86,
       0,     0,    35,    40,     0,     0,     0,     0,     0,    40,
      40,     0,     0,     0,    67,    59,     0,     0,     0,    38,
       0,     0,     0,     0,     0,     0,    47,    99,    46,    42,
      41,    43,    44,    45,   100,   101,   102,   103,    30,    29,
       0,     0,     0,    65,     0,     0,    54,    53,     0,     0,
       0,   105,    73,     0,    70,     0,     0,     0,     0,     0,
       0,     0,     0,    66,    56,     0,     0,    62,     0,    39,
       0,     0,    37,     0,     0,     0,     0,    74,    95,    96,
       0,     0,    85,     0,     0,    87,    88,    89,    90,    91,
      92,     0,    32,     0,     0,    36,    79,    80,     0,     0,
       0,     0,    84,   104,     0,     0,    81,    33,     0,    60,
       0,     0,     0,    40,     0,     0,     0,     0,    97,    98,
       0,     0,     0,    40,    40,     0,    34,     0,     0,     0,
       0,     0,    40,     0,     0,    40,     0,     0,     0,     0,
       0,    93,    94,     0,     0,     0,     0,     0,     0,     0,
      75,     0,     0,     0,     0,     0,    82,     0,     0,     0,
       0,     0,    72,    71,   107,     0,     0,     0,     0,    57,
      63,     0,    83,    49,     0,     0,    50,   106,    68,    77,
      78,     0,     0,     0,    51,    76,     0,     0,     0,    48,
      64
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -78,   -78,   -78,   -77,    13,   -78,   -78,   -78,   -78,   -78,
     -78,   -22,   -78,   -78,   -78,   -78,   -78,   -78,   -78,   -78,
     -78,   -78,   114,   -78,   -78,   -78,   -78,   -78,   -78,   -78,
     -78,   -78,   -78,   -78,   -78,   -78,   -78,   -78,   -29,   -78,
     -78,   -78,   -78,   -78,   -78,   -78,   -78,   -78,   -78,   -78,
     -78,   -78,   -78,   -78,   -78,   -78,   -78,   -78,   -78,   -78,
     -78
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    28,   120,    55,   173,   188,   207,   128,   108,
     150,    73,   109,   110,   111,   112,   113,    81,    96,   144,
      67,   147,    97,    29,    30,    31,    32,    33,   134,    86,
     126,   127,    34,    35,    36,    37,    38,    39,    83,    40,
      95,    41,    42,    43,    44,   121,   165,   166,   167,   168,
     169,   170,    45,    46,    47,    48,    49,    50,    51,    52,
      53
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint16 yytable[] =
{
      74,    75,    76,    77,    54,    60,   175,   130,   132,   101,
     135,   136,    69,   118,   139,   140,    78,    56,    57,    58,
      59,   101,    61,    62,    63,    64,    65,    66,   133,    68,
      85,   145,    71,    72,    89,   119,   145,   102,   103,   104,
      79,   176,    99,   100,    70,   171,    80,    82,    93,   102,
     103,   104,   105,   178,   158,   159,   160,   161,   180,   181,
     146,   129,   184,   185,   105,   148,   142,   137,   138,    94,
      84,    87,    88,    90,   193,   143,   194,   195,   196,   197,
     106,   101,    91,   198,   199,   162,   163,    92,   164,   122,
     117,   131,   106,   141,   202,   151,   149,   152,   153,   154,
     116,   205,   155,   208,   209,   156,   157,   172,   211,   102,
     103,   104,   179,   123,   124,   215,   186,   217,   218,   219,
     220,   187,   189,   190,   105,   223,   125,   191,   192,   200,
     227,   228,   229,   201,   231,   206,   233,   234,   174,   210,
     237,   238,   239,   240,   203,   204,   213,   212,   101,   221,
     245,   214,   106,   222,   248,   226,   251,   230,   115,   241,
     244,   246,   255,   247,   250,   253,   254,   256,   258,   257,
     259,   216,   261,   260,   262,   263,   102,   103,   104,   264,
     269,   224,   225,   265,    98,     0,   267,   270,     2,   268,
     232,   105,   266,   235,     3,     0,     4,     0,     5,     0,
       6,     0,     7,     0,     8,     0,     9,   101,    10,     0,
      11,     0,    12,     0,    13,     0,    14,     0,    15,   106,
      16,     0,     0,   114,     0,     0,     0,     0,   101,     0,
       0,     0,   101,   177,     0,   102,   103,   104,    17,     0,
       0,     0,    18,     0,     0,     0,     0,    19,     0,   182,
     105,     0,     0,     0,    20,   101,   102,   103,   104,   101,
     102,   103,   104,   101,   242,     0,    21,   101,    22,     0,
      23,   105,    24,     0,    25,   105,    26,     0,   106,    27,
     107,     0,   183,   102,   103,   104,   249,   102,   103,   104,
     101,   102,   103,   104,   101,   102,   103,   104,   105,   106,
       0,     0,   105,   106,     0,     0,   105,   243,     0,     0,
     105,     0,     0,     0,     0,     0,   236,     0,   102,   103,
     104,     0,   102,   103,   104,     0,   106,     0,     0,     0,
     106,     0,     0,   105,   106,     0,     0,   105,   106,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   252,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   106,     0,     0,     0,   106
};

static const yytype_int16 yycheck[] =
{
      22,    23,    24,    25,     4,     4,     4,    84,    17,     6,
      87,    88,     4,    76,    91,    92,    90,     4,     5,     6,
       7,     6,     9,    10,    11,    12,    13,    14,    37,    16,
      59,    24,    19,    20,    63,    98,    24,    34,    35,    36,
      27,    39,    71,    72,     4,   122,     3,    38,    10,    34,
      35,    36,    49,   130,    61,    62,    63,    64,   135,   136,
      53,    83,   139,   140,    49,    53,    24,    89,    90,    31,
      38,    38,    38,     4,   151,    33,   153,   154,   155,   156,
      77,     6,    38,   160,   161,    92,    93,    38,    95,    38,
      87,    15,    77,     4,   171,    65,    61,     4,    38,    38,
      85,   178,    38,   180,   181,    38,    89,     4,   185,    34,
      35,    36,     4,     9,    10,   192,    11,   194,   195,   196,
     197,     4,     4,     4,    49,   202,    22,     4,    65,     4,
     207,   208,   209,     4,   211,    98,   213,   214,   125,    39,
     217,   218,   219,   220,   173,   174,    52,     4,     6,    94,
     227,    56,    77,    96,   231,    39,    57,    27,    83,    39,
      13,    39,   239,    39,    51,    39,    39,    39,   245,     7,
      19,   193,    39,    21,   251,    38,    34,    35,    36,    39,
      39,   203,   204,    29,    70,    -1,   263,    55,     0,   266,
     212,    49,    58,   215,     6,    -1,     8,    -1,    10,    -1,
      12,    -1,    14,    -1,    16,    -1,    18,     6,    20,    -1,
      22,    -1,    24,    -1,    26,    -1,    28,    -1,    30,    77,
      32,    -1,    -1,    81,    -1,    -1,    -1,    -1,     6,    -1,
      -1,    -1,     6,    11,    -1,    34,    35,    36,    50,    -1,
      -1,    -1,    54,    -1,    -1,    -1,    -1,    59,    -1,    23,
      49,    -1,    -1,    -1,    66,     6,    34,    35,    36,     6,
      34,    35,    36,     6,    11,    -1,    78,     6,    80,    -1,
      82,    49,    84,    -1,    86,    49,    88,    -1,    77,    91,
      79,    -1,    25,    34,    35,    36,    25,    34,    35,    36,
       6,    34,    35,    36,     6,    34,    35,    36,    49,    77,
      -1,    -1,    49,    77,    -1,    -1,    49,    23,    -1,    -1,
      49,    -1,    -1,    -1,    -1,    -1,    67,    -1,    34,    35,
      36,    -1,    34,    35,    36,    -1,    77,    -1,    -1,    -1,
      77,    -1,    -1,    49,    77,    -1,    -1,    49,    77,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    60,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    77,    -1,    -1,    -1,    77
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,   100,     0,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,    30,    32,    50,    54,    59,
      66,    78,    80,    82,    84,    86,    88,    91,   101,   122,
     123,   124,   125,   126,   131,   132,   133,   134,   135,   136,
     138,   140,   141,   142,   143,   151,   152,   153,   154,   155,
     156,   157,   158,   159,     4,   103,   103,   103,   103,   103,
       4,   103,   103,   103,   103,   103,   103,   119,   103,     4,
       4,   103,   103,   110,   110,   110,   110,   110,    90,   103,
       3,   116,    38,   137,    38,   137,   128,    38,    38,   137,
       4,    38,    38,    10,    31,   139,   117,   121,   121,   137,
     137,     6,    34,    35,    36,    49,    77,    79,   108,   111,
     112,   113,   114,   115,    81,    83,    85,    87,    76,    98,
     102,   144,    38,     9,    10,    22,   129,   130,   107,   110,
     102,    15,    17,    37,   127,   102,   102,   110,   110,   102,
     102,     4,    24,    33,   118,    24,    53,   120,    53,    61,
     109,    65,     4,    38,    38,    38,    38,    89,    61,    62,
      63,    64,    92,    93,    95,   145,   146,   147,   148,   149,
     150,   102,     4,   104,   103,     4,    39,    11,   102,     4,
     102,   102,    23,    25,   102,   102,    11,     4,   105,     4,
       4,     4,    65,   102,   102,   102,   102,   102,   102,   102,
       4,     4,   102,   137,   137,   102,    98,   106,   102,   102,
      39,   102,     4,    52,    56,   102,   110,   102,   102,   102,
     102,    94,    96,   102,   110,   110,    39,   102,   102,   102,
      27,   102,   110,   102,   102,   110,    67,   102,   102,   102,
     102,    39,    11,    23,    13,   102,    39,    39,   102,    25,
      51,    57,    60,    39,    39,   102,    39,     7,   102,    19,
      21,    39,   102,    38,    39,    29,    58,   102,   102,    39,
      55
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    99,   100,   100,   101,   101,   101,   101,   101,   101,
     101,   101,   101,   101,   101,   101,   101,   101,   101,   101,
     101,   101,   101,   101,   101,   101,   101,   101,   101,   102,
     102,   103,   104,   105,   106,   107,   107,   108,   109,   109,
     110,   110,   110,   110,   110,   110,   110,   111,   112,   113,
     114,   115,   116,   116,   116,   117,   117,   118,   119,   119,
     120,   121,   121,   122,   123,   124,   125,   126,   127,   128,
     128,   129,   130,   131,   132,   133,   134,   135,   136,   137,
     138,   139,   140,   141,   142,   143,   144,   144,   144,   144,
     144,   144,   144,   145,   146,   147,   148,   149,   150,   151,
     152,   153,   154,   155,   156,   157,   158,   159
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     2,     2,     0,     1,
       0,     2,     2,     2,     2,     2,     2,     1,     9,     6,
       6,     7,     0,     2,     2,     0,     2,     5,     0,     2,
       2,     0,     2,     8,    12,     4,     4,     3,     6,     0,
       2,     5,     5,     4,     4,     7,    10,     9,     9,     3,
       5,     3,     7,     8,     5,     4,     0,     2,     2,     2,
       2,     2,     2,     3,     3,     1,     1,     2,     2,     3,
       3,     3,     3,     3,     5,     4,     9,     8
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
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
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


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, Session* currSession)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  YYUSE (yylocationp);
  YYUSE (currSession);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, Session* currSession)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyo, *yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yytype, yyvaluep, yylocationp, currSession);
  YYFPRINTF (yyo, ")");
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
  unsigned long yylno = yyrline[yyrule];
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

  return (YYSIZE_T) (yystpcpy (yyres, yystr) - yyres);
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
  *yyssp = (yytype_int16) yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = (YYSIZE_T) (yyssp - yyss + 1);

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
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
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
                  (unsigned long) yystacksize));

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
        case 29:
#line 123 "compilerNome/parser.y" /* yacc.c:1660  */
    {
        (yyval.string) = strdup((yyvsp[0].string));
    }
#line 1822 "/Volumes/macData/BerkeleyCG/nome/compilerNome/parser.cpp" /* yacc.c:1660  */
    break;

  case 30:
#line 126 "compilerNome/parser.y" /* yacc.c:1660  */
    {
        std::string exprStr = strdup((yyvsp[0].string));
        exprStr.erase(0, 6);
        exprStr.erase(exprStr.size() - 1);
        (yyval.string) = strdup(exprStr.c_str());
    }
#line 1833 "/Volumes/macData/BerkeleyCG/nome/compilerNome/parser.cpp" /* yacc.c:1660  */
    break;

  case 31:
#line 135 "compilerNome/parser.y" /* yacc.c:1660  */
    {
        Reader* currReader = createReader(currSession);
        if (!currReader->isUnique(strdup((yyvsp[0].string)))){
          nomerror(currSession, "Duplicate construct name.");
          YYABORT;
        }
        nameUnique = strdup((yyvsp[0].string));
    }
#line 1846 "/Volumes/macData/BerkeleyCG/nome/compilerNome/parser.cpp" /* yacc.c:1660  */
    break;

  case 32:
#line 145 "compilerNome/parser.y" /* yacc.c:1660  */
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
#line 1861 "/Volumes/macData/BerkeleyCG/nome/compilerNome/parser.cpp" /* yacc.c:1660  */
    break;

  case 33:
#line 157 "compilerNome/parser.y" /* yacc.c:1660  */
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
#line 1876 "/Volumes/macData/BerkeleyCG/nome/compilerNome/parser.cpp" /* yacc.c:1660  */
    break;

  case 34:
#line 179 "compilerNome/parser.y" /* yacc.c:1660  */
    {
        (yyval.numPos).string = strdup((yyvsp[0].string));
        (yyval.numPos).number = nomcolumn;
    }
#line 1885 "/Volumes/macData/BerkeleyCG/nome/compilerNome/parser.cpp" /* yacc.c:1660  */
    break;

  case 36:
#line 190 "compilerNome/parser.y" /* yacc.c:1660  */
    {
        tempVariables2.push_back((yyvsp[0].string));
    }
#line 1893 "/Volumes/macData/BerkeleyCG/nome/compilerNome/parser.cpp" /* yacc.c:1660  */
    break;

  case 37:
#line 196 "compilerNome/parser.y" /* yacc.c:1660  */
    {
        if (surfaceFromArg.length() == 0){
          surfaceFromArg = strdup((yyvsp[0].string));
        }
    }
#line 1903 "/Volumes/macData/BerkeleyCG/nome/compilerNome/parser.cpp" /* yacc.c:1660  */
    break;

  case 38:
#line 203 "compilerNome/parser.y" /* yacc.c:1660  */
    {(yyval.boolean) = false;}
#line 1909 "/Volumes/macData/BerkeleyCG/nome/compilerNome/parser.cpp" /* yacc.c:1660  */
    break;

  case 39:
#line 204 "compilerNome/parser.y" /* yacc.c:1660  */
    {
        (yyval.boolean) = true;
    }
#line 1917 "/Volumes/macData/BerkeleyCG/nome/compilerNome/parser.cpp" /* yacc.c:1660  */
    break;

  case 47:
#line 214 "compilerNome/parser.y" /* yacc.c:1660  */
    {
      Reverse* currReverse = createReverse();
      currentTransformations2.push_back(currReverse);
    }
#line 1926 "/Volumes/macData/BerkeleyCG/nome/compilerNome/parser.cpp" /* yacc.c:1660  */
    break;

  case 48:
#line 221 "compilerNome/parser.y" /* yacc.c:1660  */
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
#line 1956 "/Volumes/macData/BerkeleyCG/nome/compilerNome/parser.cpp" /* yacc.c:1660  */
    break;

  case 49:
#line 250 "compilerNome/parser.y" /* yacc.c:1660  */
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
#line 1981 "/Volumes/macData/BerkeleyCG/nome/compilerNome/parser.cpp" /* yacc.c:1660  */
    break;

  case 50:
#line 274 "compilerNome/parser.y" /* yacc.c:1660  */
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
#line 2006 "/Volumes/macData/BerkeleyCG/nome/compilerNome/parser.cpp" /* yacc.c:1660  */
    break;

  case 51:
#line 298 "compilerNome/parser.y" /* yacc.c:1660  */
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
#line 2023 "/Volumes/macData/BerkeleyCG/nome/compilerNome/parser.cpp" /* yacc.c:1660  */
    break;

  case 57:
#line 322 "compilerNome/parser.y" /* yacc.c:1660  */
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
#line 2086 "/Volumes/macData/BerkeleyCG/nome/compilerNome/parser.cpp" /* yacc.c:1660  */
    break;

  case 60:
#line 388 "compilerNome/parser.y" /* yacc.c:1660  */
    {
        string instanceName = strdup((yyvsp[0].string));
    }
#line 2094 "/Volumes/macData/BerkeleyCG/nome/compilerNome/parser.cpp" /* yacc.c:1660  */
    break;

  case 63:
#line 398 "compilerNome/parser.y" /* yacc.c:1660  */
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
#line 2116 "/Volumes/macData/BerkeleyCG/nome/compilerNome/parser.cpp" /* yacc.c:1660  */
    break;

  case 64:
#line 418 "compilerNome/parser.y" /* yacc.c:1660  */
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
#line 2145 "/Volumes/macData/BerkeleyCG/nome/compilerNome/parser.cpp" /* yacc.c:1660  */
    break;

  case 65:
#line 447 "compilerNome/parser.y" /* yacc.c:1660  */
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
#line 2173 "/Volumes/macData/BerkeleyCG/nome/compilerNome/parser.cpp" /* yacc.c:1660  */
    break;

  case 66:
#line 474 "compilerNome/parser.y" /* yacc.c:1660  */
    {
        GroupNew* currGroup = createGroup(currentGroup2);
        currGroup->setName(nameUnique);
        currSession->groups.push_back(currGroup);
        currentGroup2.clear();
        }
#line 2184 "/Volumes/macData/BerkeleyCG/nome/compilerNome/parser.cpp" /* yacc.c:1660  */
    break;

  case 67:
#line 490 "compilerNome/parser.y" /* yacc.c:1660  */
    {
        Reader* currReader = createReader(currSession);

        for (std::string currFace : tempFaceDelete2){
            currReader->deleteFace(currReader->getFace(currFace));
        }

        tempFaceDelete2.clear();
        }
#line 2198 "/Volumes/macData/BerkeleyCG/nome/compilerNome/parser.cpp" /* yacc.c:1660  */
    break;

  case 68:
#line 503 "compilerNome/parser.y" /* yacc.c:1660  */
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
#line 2223 "/Volumes/macData/BerkeleyCG/nome/compilerNome/parser.cpp" /* yacc.c:1660  */
    break;

  case 71:
#line 531 "compilerNome/parser.y" /* yacc.c:1660  */
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
#line 2269 "/Volumes/macData/BerkeleyCG/nome/compilerNome/parser.cpp" /* yacc.c:1660  */
    break;

  case 72:
#line 576 "compilerNome/parser.y" /* yacc.c:1660  */
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
#line 2323 "/Volumes/macData/BerkeleyCG/nome/compilerNome/parser.cpp" /* yacc.c:1660  */
    break;

  case 73:
#line 629 "compilerNome/parser.y" /* yacc.c:1660  */
    {
        BankNew * currentBank2 = createBank();
        currentBank2->name = strdup((yyvsp[-2].string));
        currentBank2->sets = currentSetList2;
        currSession->banks.push_back(currentBank2);
        currentSetList2.clear();
        }
#line 2335 "/Volumes/macData/BerkeleyCG/nome/compilerNome/parser.cpp" /* yacc.c:1660  */
    break;

  case 74:
#line 640 "compilerNome/parser.y" /* yacc.c:1660  */
    {
        double *epsilonVal = (double*) malloc(sizeof(double));

        double *currentValSet = (double*) malloc(sizeof(double));
        parseGetBankVal((yyvsp[-1].string), currSession, currentValSet, nomlineno);
        *epsilonVal = *currentValSet;
        currSession->epsilon = *epsilonVal;
        currSession->epsilonStr = strdup((yyvsp[-1].string));
    }
#line 2349 "/Volumes/macData/BerkeleyCG/nome/compilerNome/parser.cpp" /* yacc.c:1660  */
    break;

  case 75:
#line 652 "compilerNome/parser.y" /* yacc.c:1660  */
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
#line 2375 "/Volumes/macData/BerkeleyCG/nome/compilerNome/parser.cpp" /* yacc.c:1660  */
    break;

  case 76:
#line 676 "compilerNome/parser.y" /* yacc.c:1660  */
    {
		string name = (yyvsp[-8].string);
        double *pass = (double*) malloc(sizeof(double));
        double *turn = (double*) malloc(sizeof(double));
		double *rmaj = (double*) malloc(sizeof(double));
        double *rmin = (double*) malloc(sizeof(double));
		double *num = (double*) malloc(sizeof(double));

        double *currentValSet = (double*) malloc(sizeof(double));
        parseGetBankVal((yyvsp[-6].string), currSession, currentValSet, nomlineno);
        *pass = *currentValSet;

        parseGetBankVal((yyvsp[-5].string), currSession, currentValSet, nomlineno);
        *turn = *currentValSet;

		parseGetBankVal((yyvsp[-4].string), currSession, currentValSet, nomlineno);
        *rmaj = *currentValSet;

        parseGetBankVal((yyvsp[-3].string), currSession, currentValSet, nomlineno);
        *rmin = *currentValSet;

        parseGetBankVal((yyvsp[-2].string), currSession, currentValSet, nomlineno);
        *num = *currentValSet;

        TorusKnotNew* currTorusKnot = createTorusKnot(pass, turn, rmaj, rmin, num);
		currTorusKnot->setName(nameUnique);

        currSession->meshes.push_back(currTorusKnot);
	}
#line 2409 "/Volumes/macData/BerkeleyCG/nome/compilerNome/parser.cpp" /* yacc.c:1660  */
    break;

  case 77:
#line 709 "compilerNome/parser.y" /* yacc.c:1660  */
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
#line 2443 "/Volumes/macData/BerkeleyCG/nome/compilerNome/parser.cpp" /* yacc.c:1660  */
    break;

  case 78:
#line 743 "compilerNome/parser.y" /* yacc.c:1660  */
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
#line 2478 "/Volumes/macData/BerkeleyCG/nome/compilerNome/parser.cpp" /* yacc.c:1660  */
    break;

  case 79:
#line 777 "compilerNome/parser.y" /* yacc.c:1660  */
    {
        }
#line 2485 "/Volumes/macData/BerkeleyCG/nome/compilerNome/parser.cpp" /* yacc.c:1660  */
    break;

  case 80:
#line 783 "compilerNome/parser.y" /* yacc.c:1660  */
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
#line 2528 "/Volumes/macData/BerkeleyCG/nome/compilerNome/parser.cpp" /* yacc.c:1660  */
    break;

  case 81:
#line 825 "compilerNome/parser.y" /* yacc.c:1660  */
    {
        tempFaceDelete2.push_back((yyvsp[-1].string));
        }
#line 2536 "/Volumes/macData/BerkeleyCG/nome/compilerNome/parser.cpp" /* yacc.c:1660  */
    break;

  case 82:
#line 831 "compilerNome/parser.y" /* yacc.c:1660  */
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
#line 2587 "/Volumes/macData/BerkeleyCG/nome/compilerNome/parser.cpp" /* yacc.c:1660  */
    break;

  case 83:
#line 880 "compilerNome/parser.y" /* yacc.c:1660  */
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
#line 2656 "/Volumes/macData/BerkeleyCG/nome/compilerNome/parser.cpp" /* yacc.c:1660  */
    break;

  case 84:
#line 947 "compilerNome/parser.y" /* yacc.c:1660  */
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
#line 2696 "/Volumes/macData/BerkeleyCG/nome/compilerNome/parser.cpp" /* yacc.c:1660  */
    break;

  case 85:
#line 985 "compilerNome/parser.y" /* yacc.c:1660  */
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
#line 2715 "/Volumes/macData/BerkeleyCG/nome/compilerNome/parser.cpp" /* yacc.c:1660  */
    break;

  case 93:
#line 1009 "compilerNome/parser.y" /* yacc.c:1660  */
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
#line 2731 "/Volumes/macData/BerkeleyCG/nome/compilerNome/parser.cpp" /* yacc.c:1660  */
    break;

  case 94:
#line 1022 "compilerNome/parser.y" /* yacc.c:1660  */
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
#line 2749 "/Volumes/macData/BerkeleyCG/nome/compilerNome/parser.cpp" /* yacc.c:1660  */
    break;

  case 95:
#line 1037 "compilerNome/parser.y" /* yacc.c:1660  */
    {
    currentSweepInitializer.Closed = true;
}
#line 2757 "/Volumes/macData/BerkeleyCG/nome/compilerNome/parser.cpp" /* yacc.c:1660  */
    break;

  case 96:
#line 1042 "compilerNome/parser.y" /* yacc.c:1660  */
    {
                    currentSweepInitializer.MinTorsion = true;
                }
#line 2765 "/Volumes/macData/BerkeleyCG/nome/compilerNome/parser.cpp" /* yacc.c:1660  */
    break;

  case 97:
#line 1046 "compilerNome/parser.y" /* yacc.c:1660  */
    {
    currentSweepInitializer.AzimuthExpr = (yyvsp[0].string);
}
#line 2773 "/Volumes/macData/BerkeleyCG/nome/compilerNome/parser.cpp" /* yacc.c:1660  */
    break;

  case 98:
#line 1050 "compilerNome/parser.y" /* yacc.c:1660  */
    {
    currentSweepInitializer.TwistExpr = (yyvsp[0].string);
}
#line 2781 "/Volumes/macData/BerkeleyCG/nome/compilerNome/parser.cpp" /* yacc.c:1660  */
    break;

  case 99:
#line 1056 "compilerNome/parser.y" /* yacc.c:1660  */
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
#line 2802 "/Volumes/macData/BerkeleyCG/nome/compilerNome/parser.cpp" /* yacc.c:1660  */
    break;

  case 100:
#line 1075 "compilerNome/parser.y" /* yacc.c:1660  */
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
#line 2823 "/Volumes/macData/BerkeleyCG/nome/compilerNome/parser.cpp" /* yacc.c:1660  */
    break;

  case 101:
#line 1094 "compilerNome/parser.y" /* yacc.c:1660  */
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
#line 2844 "/Volumes/macData/BerkeleyCG/nome/compilerNome/parser.cpp" /* yacc.c:1660  */
    break;

  case 102:
#line 1113 "compilerNome/parser.y" /* yacc.c:1660  */
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
#line 2865 "/Volumes/macData/BerkeleyCG/nome/compilerNome/parser.cpp" /* yacc.c:1660  */
    break;

  case 103:
#line 1132 "compilerNome/parser.y" /* yacc.c:1660  */
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
#line 2886 "/Volumes/macData/BerkeleyCG/nome/compilerNome/parser.cpp" /* yacc.c:1660  */
    break;

  case 104:
#line 1151 "compilerNome/parser.y" /* yacc.c:1660  */
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
#line 2944 "/Volumes/macData/BerkeleyCG/nome/compilerNome/parser.cpp" /* yacc.c:1660  */
    break;

  case 105:
#line 1208 "compilerNome/parser.y" /* yacc.c:1660  */
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
#line 2981 "/Volumes/macData/BerkeleyCG/nome/compilerNome/parser.cpp" /* yacc.c:1660  */
    break;

  case 106:
#line 1244 "compilerNome/parser.y" /* yacc.c:1660  */
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
#line 3008 "/Volumes/macData/BerkeleyCG/nome/compilerNome/parser.cpp" /* yacc.c:1660  */
    break;

  case 107:
#line 1270 "compilerNome/parser.y" /* yacc.c:1660  */
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
#line 3036 "/Volumes/macData/BerkeleyCG/nome/compilerNome/parser.cpp" /* yacc.c:1660  */
    break;


#line 3040 "/Volumes/macData/BerkeleyCG/nome/compilerNome/parser.cpp" /* yacc.c:1660  */
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
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

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

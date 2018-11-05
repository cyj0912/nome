
%{
#include <stdio.h>
#include <string.h>
#include <string>
#include "parser.hpp"
#include "newNOME/Session.h"

int nomcolumn = 0;
int numBegComments = 0;
#define YY_USER_ACTION nomlloc.first_line = nomlloc.last_line = nomlineno; \
    nomlloc.first_column = nomcolumn; nomlloc.last_column = nomcolumn + nomleng - 1; \
    nomcolumn += nomleng;

static int isatty(int) {return 0;}
%}

%option prefix="nom"
%option noyywrap

%option nounistd
%option yylineno
%x MULTI_COMMENT
%x LINE_COMMENT


%%
<INITIAL>{
"(*"              numBegComments++; BEGIN(MULTI_COMMENT);
}
<MULTI_COMMENT>{
"*)"      numBegComments--; if (numBegComments == 0){ BEGIN(INITIAL); };
[^*\n]+   // eat comment in chunks
"(*"      numBegComments++;
"*"       // eat the lone star
\n        ;
}
"\#"            { BEGIN(LINE_COMMENT); }
<LINE_COMMENT>\n   { BEGIN(INITIAL); }
<LINE_COMMENT>.    { }
[+-]?([0-9]*[.])?[0-9]+  nomlval.string=nomtext; return NUMBER;
\$[a-zA-Z][a-zA-Z0-9]*.[a-zA-Z][a-zA-Z0-9]*  nomlval.string=strdup(nomtext); return BANK_EXPR;
expr                     return EXPR;
bspline[0-9]+            nomlval.intNumber = std::stoi(std::string(nomtext).substr (7)); return BSPLINE;
endbspline[0-9]+         nomlval.intNumber = std::stoi(std::string(nomtext).substr (10)); return END_BSPLINE;
closed                   return CLOSED;
minimizetorsion          return MINIMIZETORSION;
azimuth                  return AZIMUTH;
twist                    return TWIST;
slices                   return SLICES;
beziercurve              return BEZIERCURVE;
endbeziercurve           return END_BEZIERCURVE;
offset                   return OFFSET;
endoffset                return END_OFFSET;
min                      return MIN;
max                      return MAX;
step                     return STEP;
surface                  return SURFACE;
endsurface               return END_SURFACE;
point                    return BEG_POINT;
color                    return COLOR;
endpoint                 return END_POINT;
bank                     return BANK;
endbank                  return END_BANK;
set                      return SET;
face                     return FACE;
endface                  return END_FACE;
object                   return OBJECT;
endobject                return END_OBJECT;
mesh                    return MESH;
endmesh                 return END_MESH;
tunnel                  return TUNNEL;
endtunnel               return END_TUNNEL;
funnel                  return FUNNEL;
endfunnel               return END_FUNNEL;
polyline                return POLYLINE;
circle                  return CIRCLE;
endcircle               return END_CIRCLE;
scale                   return SCALE;
endpolyline             return END_POLYLINE;
instance                return INSTANCE;
endinstance             return END_INSTANCE;
translate               return TRANSLATE;
rotate                  return ROTATE;
reverse                 return REVERSE;
foreground              return FOREGROUND;
endforeground           return END_FOREGROUND;
background              return BACKGROUND;
endbackground           return END_BACKGROUND;
insidefaces             return INSIDEFACES;
endinsidefaces          return END_INSIDEFACES;
outsidefaces            return OUTSIDEFACES;
endoutsidefaces         return END_OUTSIDEFACES;
offsetfaces             return OFFSETFACES;
endoffsetfaces          return END_OFFSETFACES;
mirror                  return MIRROR;
delete                  return BEG_DELETE;
enddelete               return END_DELETE;
group                   return GROUP;
endgroup                return END_GROUP;
subdivision             return SUBDIVISION;
endsubdivision          return END_SUBDIVISION;
subdivisions            return SUBDIVISIONS;
type                    return TYPE;
\{                      return OBRACE;
\}                      return EBRACE;
merge                   return MERGE;
endmerge                return END_MERGE;
epsilon                 return EPSILON;
sweep                   return SWEEP;
endsweep                return END_SWEEP;
path                    return PATH;
endpath                 return ENDPATH;
crosssection            return CROSSSECTION;
endcrosssection         return END_CROSSSECTION;
\{expr\ ([^\}]*)\}      nomlval.string=strdup(nomtext); return SLIDEREXPRESSION;
[a-zA-Z\.][a-zA-Z0-9_\.]* nomlval.string=strdup(nomtext); return VARIABLE;
\(                      return OPARENTHESES;
\)                      return EPARENTHESES;
<<EOF>>                 if (numBegComments != 0){std::cout << "Error: Missing *) of multiline comment." << std::endl;} return 0;
[ \t\n]+                /* ignore whitespace */;
%%

int scanFromSessionFileContent(Session* s)
{
	const char* buf = s->fileContent.data();
	size_t sz = s->fileContent.size();
	YY_BUFFER_STATE bufferState = nom_scan_bytes(buf, sz);

	nomlineno = 1;
    nomcolumn = 0;

	int ret = nomparse(s);
	nom_delete_buffer(bufferState);
	return ret;
}

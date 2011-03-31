#include "t24.h"

#include <assert.h>
#include <regexp.h>

int t24_menu_mode = 0;
int t24_jed_mode = 0;

enum AnsiColor {
  clBlack  = 0,
  clRed    = 1,
  clGreen  = 2,
  clYellow = 3,
  clBlue   = 4,
  clPurple = 5,
  clCyan   = 6,
  clWhite  = 7
};

struct token_t {
  char* re;              /* regexp */
  int group;
  int index;             
  unsigned long color;   /* color and attributes */
  char* values;          /* a list pre-defined values or NULL */
};

struct token_t tokens[] = {
  /* Comments '*' */
  { "^(([\t ]*|)\\*.*$)", 1, 0, clYellow, NULL },
  
  /* Comments */
  { "^(((;)[\t ]*\\*([^=]|$)|!|//|REM).*)", 1, -1, clYellow, NULL },

  /* Double quoted string */
  { "^(\"[^\"]*\")", 1, -1, clYellow | ATTR_BOLD, NULL },

  /* Single quoted string */
  { "^('[^']*')", 1, -1, clYellow | ATTR_BOLD, NULL },

  /* Slash quoted string */
  { "^(\\\\[^\\\\\]*\\\\)", 1, -1, clYellow | ATTR_BOLD, NULL },

  /* Label */
  { "^([a-zA-Z0-9_\\.]+\\:)", 1, 0, clBlue | ATTR_BOLD, NULL },

  /* System variable */
  { "^(@\\([a-zA-Z0-9_\\.\\$]+\\))", 1, -1, clCyan, NULL },

  /* Cursor positioning */
  { "^((@)\\([ \t]*[a-zA-Z0-9_\\.\\$]+[ \t]*,[ \t]*[a-zA-Z0-9_\\.\\$]+[ \t]*\\))", 
    2, -1, clCyan, NULL },

  /* System variable @NAME */
  { "^(@[a-zA-Z_\\.]+)", 1, -1, clCyan, NULL },

  /* Common block */
  { "^(/([^\\/]+)/)", 
    2, 1, clRed | ATTR_BOLD, NULL },

  /* Subroutine operators */
  { "^(GOSUB|CALL|RETURN|STOP)", 1, -1, clCyan | ATTR_BOLD, NULL },
  
  /* Operators and functions */
  { "^([a-zA-Z_\\$][a-zA-Z0-9_\\.\\$]*)", 1, -1, clRed | ATTR_BOLD, 
    "|"
    "$INSERT|"
    "ABORT|"
    "ABSS|"
    "ABS|"
    "ADDS|"
    "ALPHA|"
    "AND|"
    "ANDS|"
    "ASCII|"
    "ASSIGNED|"
    "BEGIN|"
    "BITAND|"
    "BITCHANGE|"
    "BITCHECK|"
    "BITLOAD|"
    "BITNOT|"
    "BITOR|"
    "BITRESET|"
    "BITSET|"
    "BITTEST|"
    "BITXOR|"
    "BREAK|"
    "BYTELEN|"
    "CAPTURING|"
    "CALLC|"
    "CALLJ|"
    "CALLONEXIT|"
    "CALLdotNET|"
    "CALL|"
    "CASE|"
    "CATALOG|"
    "CATS|"
    "CHAIN|"
    "CHANGETIMESTAMP|"
    "CHANGE|"
    "CHARS|"
    "CHAR|"
    "CHDIR|"
    "CHECKSUM|"
    "CLEARCOMMON|"
    "CLEARDATA|"
    "CLEARFILE|"
    "CLEARINPUT|"
    "CLEARSELECT|"
    "CLEAR|"
    "CLOSESEQ|"
    "CLOSE|"
    "COL1|"
    "COL2|"
    "COLLECTDATA|"
    "COMMON|"
    "COMPARE|"
    "CONTINUE|"
    "CONVERT|"
    "CONVERT|"
    "COS|"
    "COUNTS|"
    "COUNT|"
    "CREATE|"
    "CRT|"
    "CacheBucketList|"
    "CacheClearAll|"
    "CacheClearStats|"
    "CacheClear|"
    "CacheDelete|"
    "CacheExists|"
    "CacheGetOption|"
    "CacheGet|"
    "CacheKeyList|"
    "CachePut|"
    "CacheSetOption|"
    "CacheStats|"
    "DATA|"
    "DATE|"
    "DCOUNT|"
    "DEBUG|"
    "DECATALOG|"
    "DECRYPT|"
    "DEFCE|"
    "DEFC|"
    "DEFFUN|"
    "DELETE-CATALOG|"
    "DELETELIST|"
    "DELETESEQ|"
    "DELETEU|"
    "DELETE|"
    "DEL|"
    "DIMENSION|"
    "DIM|"
    "DIR|"
    "DIVS|"
    "DIV|"
    "DOWNCASE|"
    "DO|"
    "DQUOTE"
    "DROUND|"
    "DTX|"
    "DYNTOXML|"
    "EBCDIC|"
    "ECHO|"
    "ELSE|"
    "ENCRYPT|"
    "END|"
    "ENTER|"
    "EQS|"
    "EQUATE|"
    "EQU|"
    "EQ|"
    "ERROR|"
    "EREPLACE|"
    "EXECUTE|"
    "EXIT|"
    "EXP|"
    "EXTRACT|"
    "FADD|"
    "FDIV|"
    "FIELDS|"
    "FIELD|"
    "FILEINFO|"
    "FILELOCK|"
    "FILEUNLOCK|"
    "FINDSTR|"
    "FIND|"
    "FLUSH|"
    "FMTS|"
    "FMT|"
    "FOLD|"
    "FOR|"
    "FOOTING|"
    "FORMLIST|"
    "FROM|"
    "FSUB|"
    "FUNCTION|"
    "GES|"
    "GETCWD|"
    "GETENV|"
    "GETLIST|"
    "GETUSERGROUP|"
    "GETX|"
    "GET|"
    "GE|"
    "GOSUB|"
    "GOTO|"
    "GROUP|"
    "GT|"
    "HEADINGE|"
    "HEADINGN|"
    "HEADING|"
    "HUSH|"
    "ICONVS|"
    "ICONV|"
    "IFS|"
    "IF|"
    "INCLUDE|"
    "INDEX|"
    "INMAT|"
    "INPUTCLEAR|"
    "INPUTNULL|"
    "INPUT|"
    "INSERT|"
    "INS|"
    "INT|"
    "IN|"
    "IOCTL|"
    "ISALNUM|"
    "ISALPHA|"
    "ISCNTRL|"
    "ISDIGIT|"
    "ISLOWER|"
    "ISPRINT|"
    "ISSPACE|"
    "ISUPPER|"
    "ITYPE|"
    "JBASECOREDUMP|"
    "JBASETHREADCreate|"
    "JBASETHREADStatus|"
    "JQLCOMPILE|"
    "JQLEXECUTE|"
    "JQLFETCH|"
    "JQLGETPROPERTY|"
    "JQLPUTPROPERTY|"
    "KEYIN|"
    "LATIN1|"
    "LEFT|"
    "LENDP|"
    "LENS|"
    "LEN|"
    "LES|"
    "LE|"
    "LIKE|"
    "LN|"
    "LOCALDATE|"
    "LOCALTIME|"
    "LOCATE|"
    "LOCK|"
    "LOOP|"
    "LOWER|"
    "LT|"
    "MAKETIMESTAMP|"
    "MATBUILD|"
    "MATCHES|"
    "MATCHFIELD|"
    "MATPARSE|"
    "MATREADU|"
    "MATREAD|"
    "MATWRITEU|"
    "MATWRITE|"
    "MAT|"
    "MAXIMUM|"
    "MINIMUM|"
    "MODS|"
    "MOD|"
    "MSLEEP|"
    "MULS|"
    "NEGS|"
    "NES|"
    "NEXT|"
    "NE|"
    "NOBUF|"
    "NOTS|"
    "NOT|"
    "NULL|"
    "NUMS|"
    "NUM|"
    "OBJEXCALLBACK|"
    "OCONVS|"
    "OCONV|"
    "ON|"
    "ONGOTO|"
    "OPENDEV|"
    "OPENINDEX|"
    "OPENPATH|"
    "OPENSEQ|"
    "OPENSER|"
    "OPEN|"
    "OR|"
    "ORS|"
    "OSBREAD|"
    "OSBWRITE|"
    "OSCLOSE|"
    "OSDELETE|"
    "OSOPEN|"
    "OSREAD|"
    "OSWRITE|"
    "OUT|"
    "PAGE|"
    "PAUSE|"
    "PCPERFORM|"
    "PERFORM|"
    "PRECISION|"
    "PRINTERR|"
    "PRINTER|"
    "PRINT|"
    "PROCREAD|"
    "PROCWRITE|"
    "PROGRAM|"
    "PROMPT|"
    "PUTENV|"
    "PWR|"
    "QUOTE|"
    "RAISE|"
    "READBLK|"
    "READLIST|"
    "READL|"
    "READNEXT|"
    "READPREV|"
    "READSELECT|"
    "READSEQ|"
    "READT|"
    "READU|"
    "READVL|"
    "READVU|"
    "READV|"
    "READXML|"
    "READ|"
    "RECORDLOCKED|"
    "REGEXP|"
    "RELEASE|"
    "REMOVE|"
    "REPEAT|"
    "REPLACE|"
    "RETURN|"
    "REWIND|"
    "RIGHT|"
    "RND|"
    "RQM|"
    "RTNDATA|"
    "SADD|"
    "SDIV|"
    "SEEK|"
    "SELECT|"
    "SENDX|"
    "SEND|"
    "SENTENCE|"
    "SEQS|"
    "SEQ|"
    "SETTING|"
    "SIN|"
    "SLEEP|"
    "SMUL|"
    "SORT|"
    "SOUNDEX|"
    "SPACES|"
    "SPACE|"
    "SPLICE|"
    "SPOOLER|"
    "SQRT|"
    "SQUOTE|"
    "SSELECTN|"
    "SSELECTV|"
    "SSELECT|"
    "SSUB|"
    "STATUS|"
    "STEP|"
    "STOP|"
    "STRS|"
    "STR|"
    "SUBROUTINE|"
    "SUBSTRINGS|"
    "SUBS|"
    "SUM|"
    "SWAP|"
    "TAN|"
    "THEN|"
    "TIMEDATE|"
    "TIMEDIFF|"
    "TIMEOUT|"
    "TIMESTAMP|"
    "TIME|"
    "TO|"
    "TRANSABORT|"
    "TRANSEND|"
    "TRANSQUERY|"
    "TRANSTART|"
    "TRANS|"
    "TRANS|"
    "TRIMBS|"
    "TRIMB|"
    "TRIMFS|"
    "TRIMF|"
    "TRIM|"
    "UDTEXECUTE|"
    "UNASSIGNED|"
    "UNIQUEKEY|"
    "UNLOCK|"
    "UNTIL|"
    "UPCASE|"
    "UPCASE|"
    "UTF8|"
    "WAKE|"
    "WEOFSEQ|"
    "WEOF|"
    "WITH|"
    "WHILE|"
    "WRITEBLK|"
    "WRITELIST|"
    "WRITESEQF|"
    "WRITESEQ|"
    "WRITEU|"
    "WRITEVU|"
    "WRITEV|"
    "WRITEXML|"
    "WRITE|"
    "XLATE|"
    "XMLTODYN|"
    "XMLTOXML|"
    "XTD|"
  },

  /* Numeric constant */
  { "^([0-9]+(\\.[0-9]+|))",
    1, -1, clGreen | ATTR_BOLD, NULL },

  /* -, +, *, /, = */
  { "^(-|\\+|\\*|/|=|<>|:=)",
    1, -1, clGreen, NULL },

  /* Skip current token */
  { "^([a-zA-Z_\\$\\%][a-zA-Z0-9_\\.\\$\\%]*)", 1, -1, -1, NULL }
};

static const int nb_tokens = sizeof(tokens) / sizeof(*tokens);

static regexp* re_tokens[nb_tokens] = {0};

#include <stdarg.h>

void t24_log(const char* fmt, ...)
{
  char buf[10240];
  va_list args;  
  va_start(args, fmt);
  vsprintf(buf, fmt, args);
  va_end(args);

  FILE *f = fopen("t24.log", "a+");
  if (!f) return;
  fprintf(f, "%s\n", buf);
  fclose(f);
}

static int t24_basic_color(int n, const char* line, char** end, termchar *newline, int index)
{
  int i;
  const int group = tokens[n].group;
  int offset = re_tokens[n]->startp[group] - line;
  const int size = re_tokens[n]->endp[group] - re_tokens[n]->startp[group];
  assert(size != 0);

#if 0
  {
    char word[size + 1];
    memcpy(word, re_tokens[n]->startp[group], size);
    word[size] = 0;
    fprintf(stderr, "token: [%s], index = %d, %d\n", word, index, tokens[n].index);
  }
#endif
  
  *end = NULL;
  if (tokens[n].index != -1 && index != tokens[n].index)
    return 0;

  *end = re_tokens[n]->endp[0];

  if (tokens[n].values) {
    char word[size + 3];
    word[0] = '|';
    memcpy(word + 1, re_tokens[n]->startp[group], size);
    word[1 + size ] = '|';
    word[1 + size + 1 ] = 0;
    if (!strstr(tokens[n].values, word))
      return 0;
  }

  if (tokens[n].color != -1) {
    for (i = offset; i < offset + size; ++i) {
      newline[i].attr = (newline[i].attr & ~ATTR_FGMASK) | tokens[n].color;
    }
  }
  memset(re_tokens[n]->startp[group], 0xff, size);
  return 1;
}

int t24_is_jed_hex_line(termchar *newline, int cols, int prefix_sz)
{
  int j;
  int hex_count = 0, space_count = 0;
  for (j = prefix_sz; j < cols; ++j) {
    int c = newline[j].chr & 0xff;
    if (isxdigit(c))
      hex_count += 1;
    else
      break;
  }
  if (hex_count & 1) return 0;
  for (; j < cols; ++j) {
    int c = newline[j].chr & 0xff;
    if (c == ' ')
      space_count += 1;
    else
      break;
  }
  return (prefix_sz + hex_count + space_count) == cols;
}

void t24_basic_highlight(termchar *newline, int cols, int jed_prefix_length) 
{
  int i;

  if (jed_prefix_length < 5) return;

  if (t24_is_jed_hex_line(newline, cols, jed_prefix_length))  
    return;
    
  static char line[1024 * 8];
  for (i = 0; i < cols; ++i)
    line[i] = newline[i].chr & 0xFF;
  line[cols] = 0;    

  if (re_tokens[0] == 0) {
    for (i = 0; i < nb_tokens; ++i)
      assert(re_tokens[i] = regcomp(tokens[i].re));
  }

  char* p = line + jed_prefix_length;
  int index = 0;
  while (*p) {
    int found = 0;
    for (i = 0; !found && i < nb_tokens; ++i) {
      if (regexec(re_tokens[i], p)) {
        char* end = NULL;
        found = t24_basic_color(i, p, &end, newline + (p - line), index);
        index += 1;
        if (end) p = end;
      }
    }
    if (!found)
      p += 1;
  }
}

int t24_is_jed_line(termchar *newline, int cols)
{
  int digit_count = 0, plus_count = 0;
  int j;
  if (cols < 4) return 0;
  for (j = 0; j < cols; ++j) {
    int c = newline[j].chr & 0xff;
    if (isdigit(c) && plus_count == 0) 
      digit_count += 1;
    else if (c == '+' && digit_count == 0) 
      plus_count += 1;
    else 
      break;
  }
  j = digit_count | plus_count;
  if (j && j < cols && (newline[j].chr & 0xff) == ' ')
    j += 1;
  return j;
}

int t24_is_t24_line(termchar *newline, int cols) 
{
  int minus_count = 0;
  int j;
  for (j = 1; j < cols; ++j) {
    int c = newline[j].chr & 0xff;
    if (c == '-') 
      minus_count += 1;
    else 
      break;
  }
  return minus_count > 50 && (newline[0].chr & 0xff) == ' ';
}

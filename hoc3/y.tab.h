#define racionalnum 257
#define NUMBER 258
#define VAR 259
#define BLTIN 260
#define INDEF 261
#define UNARYMINUS 262
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
typedef union {
	double val;
	char * bltin;
	Symbol *sym;
	RacionalAP racional_;
} YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
extern YYSTYPE yylval;

/*
************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Winter, 2023
* Author: TO_DO
* Professors: Paulo Sousa
************************************************************

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@@@@                                                               @@@@
@@          /       ==============================        /          @@
@         ////           @@       @@ #@                  ////         @
@         ////*          @@ @%  @ @@    @@  @ #@#       /////         @
@     ((( ////))))   @@  @% @%  @ @@ #@ @@  @ #@@#   ///////( ///     @
@     ((((,/ )))))    @@@@   @@@  @@ ##  @@@   #@#   ///// ,/////     @
@     (((((/)))((    ------------------------------    ((((./////*    @
@    //*./ /  .///   ---  PROGRAMMING LANGUAGE  ---  ////   / ( (//   @
@    ///// / /////   ==============================  * ////* / ////   @
@     ///// ///// ((                               (( ///// /////     @
@    ((((   / , (((((                             (((((  //   /(((    @
@    (((((((/ . (((((                          (((((* / (((((((       @
@      (((((( //((((/((((                    *((((/((((/( (((((/      @
@       .//,   * /   (((((                   (((((  ///    .//.       @
@     ,////////./(  (((((* ////         (///(((((( ,/(,////////       @
@         //////// ,// ((( /////,     ////// ((( //  /////// *        @
@            (((((((((,// * /////     /////   (//(((((((((            @
@            ((((((((((((/////         //.///  (((((((((((.           @
@                   (///////// //(   (//.//////////                   @
@                  (/////////             //////////                  @
@                                                                     @
@@          A L G O N Q U I N   C O L L E G E  -  2 0 2 3 W          @@
@@@@                                                               @@@@
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

*/

/*
************************************************************
* File name: scanner.h
* Compiler: MS Visual Studio 2022
* Course: CST 8152 � Compilers, Lab Section: [011, 012, 013]
* Assignment: A22, A32.
* Date: Sep 01 2022
* Purpose: This file is the main header for Scanner (.h)
* Function list: (...).
*************************************************************/


#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef SCANNER_H_
#define SCANNER_H_

#ifndef NULL
#include <_null.h> /* NULL pointer constant is defined there */
#endif

/*#pragma warning(1:4001) */	/*to enforce C89 type comments  - to make //comments an warning */

/*#pragma warning(error:4001)*/	/* to enforce C89 comments - to make // comments an error */

/* Constants */
#define VID_LEN 20  /* variable identifier length */
#define ERR_LEN 40  /* error message length */
#define NUM_LEN 5   /* maximum number of digits for IL */

#define RTE_CODE 1  /* Value for run-time error */

/* TO_DO: Define Token codes - Create your token classes */
enum TOKENS {
	ERR_T,		/*  0: Error token */
	MNID_T,		/*  1: Method name identifier token (start: &) */
	STR_T,		/*  2: String literal token */
	LPR_T,		/*  3: Left parenthesis token */
	RPR_T,		/*  4: Right parenthesis token */
	LBR_T,		/*  5: Left brace token */
	RBR_T,		/*  6: Right brace token */
	KW_T,		/*  7: Keyword token */
	EOS_T,		/*  8: End of statement (semicolon) */
	RTE_T,		/*  9: Run-time error token */
	INL_T,		/* 10: Integer Literal token */
	SEOF_T,		/* 11: Source end-of-file token */
	FLO_T,		/* 12: Foating literal token */
	OTH_T,		/* 13: Other Character token */
	UND_T,		/* 14: Underscore token */
	FVID_T,		/* 15: Float variable identifier token */
	SVID_T,		/* 16: String variable identifier token */
	IVID_T,		/* 17: Integer variable identifier token */
	AVID_T,		/* 18: Arithmetic variable identifier token*/
	OP_T,		/* 19: Logical operator token*/
	POI_T		/* 20: Point token for floating literal*/
};

/* TO_DO: Operators token attributes */
typedef enum ArithmeticOperators { OP_ADD, OP_SUB, OP_MUL, OP_DIV } AriOperator;
typedef enum RelationalOperators { OP_EQ, OP_NE, OP_GT, OP_LT } RelOperator;
typedef enum LogicalOperators { OP_AND, OP_OR, OP_NOT } LogOperator;
typedef enum SourceEndOfFile { SEOF_0, SEOF_255 } EofOperator;

/* TO_DO: Data structures for declaring the token and its attributes */
typedef union TokenAttribute {
	hailey_intg codeType;      /* integer attributes accessor */
	AriOperator arithmeticOperator;		/* arithmetic operator attribute code */
	RelOperator relationalOperator;		/* relational operator attribute code */
	LogOperator logicalOperator;		/* logical operator attribute code */
	EofOperator seofType;				/* source-end-of-file attribute code */
	hailey_intg intValue;						/* integer literal attribute (value) */
	hailey_intg keywordIndex;					/* keyword index in the keyword table */
	hailey_intg contentString;				/* string literal offset from the beginning of the string literal buffer (stringLiteralTable->content) */
	hailey_real floatValue;					/* floating-point literal attribute (value) */
	hailey_char idLexeme[VID_LEN + 1];		/* variable identifier token attribute */
	hailey_char errLexeme[ERR_LEN + 1];		/* error token attribite */
} TokenAttribute;

/* TO_DO: Should be used if no symbol table is implemented */
typedef struct idAttibutes {
	hailey_byte flags;			/* Flags information */
	union {
		hailey_intg intValue;				/* Integer value */
		hailey_real floatValue;			/* Float value */
		hailey_char* stringContent;		/* String value */
	} values;
} IdAttibutes;

/* Token declaration */
typedef struct Token {
	hailey_intg code;				/* token code */
	TokenAttribute attribute;	/* token attribute */
	IdAttibutes   idAttribute;	/* not used in this scanner implementation - for further use */
} Token;

///////////////////////////////////////////////////////////////////////////////////////////////////////

/* EOF definitions */
#define CHARSEOF0 '\0'
#define CHARSEOF255 0xFF

/*  Special case tokens processed separately one by one in the token-driven part of the scanner
 *  '=' , ' ' , '(' , ')' , '{' , '}' , == , <> , '>' , '<' , ';',
 *  white space, #comment\n , ',' , ';' , '-' , '+' , '*' , '/', # ,
 *  .&., .|. , .!. , SEOF.
 */

 /* TO_DO: Define lexeme FIXED classes */
 /* These constants will be used on nextClass */
#define CHRCOL2 '_'
#define CHRCOL3 '&'
#define CHRCOL4 '\''
#define CHRCOL5 '0'
#define CHRCOL6 '.'


/* These constants will be used on VID / MID function */
#define MNIDPREFIX '&'

/* TO_DO: Error states and illegal state */
#define FS		100		/* Illegal state */
#define ESNR	6		/* Error state with no retract */
#define ESWR	7		/* Error state with retract */

 /* TO_DO: State transition table definition */
#define TABLE_COLUMNS 8

/* TO_DO: Transition table - type of states defined in separate table */
static hailey_intg transitionTable[][TABLE_COLUMNS] = {
	/*[A-z], [0-9],    _,    &,    ',	.,	SEOF, other
	   L(0),  D(1), U(2), M(3), Q(4), F(5),	E(6),  O(7) */
	{     1,  ESNR, ESNR, ESNR,    4, ESWR,	ESWR, ESNR}, // S0: NOAS
	{     1,     1,    1,    2, ESWR, ESWR,	ESWR,    3}, // S1: NOAS
	{    FS,    FS,   FS,   FS,   FS,	FS,	  FS,   FS}, // S2: FSNR (MVID)
	{    FS,    FS,   FS,   FS,   FS,	FS,	  FS,   FS}, // S3: FSWR (KEY)
	{     4,     4,    4,    4,    5,	FS,	ESWR,    4}, // S4: NOAS
	{    FS,    FS,   FS,   FS,   FS,	FS,	  FS,   FS}, // S5: FSNR (SL)
	{    FS,    FS,   FS,   FS,   FS, ESNR,	  FS,   FS}, // S6: FSNR (IL)
	{    FS,	FS,	  FS,	FS,	  FS, ESNR,	  FS,   FS}, // S7: FSNR (FL)
	{    FS,    FS,   FS,   FS,   FS,	FS,   FS,   FS}, // S7: ESNR (ES)
	{    FS,    FS,   FS,   FS,   FS,	FS,	  FS,   FS}  // S8: ESWR (ER)
};

/* Define accepting states types */
#define NOFS	0		/* not accepting state */
#define FSNR	1		/* accepting state with no retract */
#define FSWR	2		/* accepting state with retract */

/* TO_DO: Define list of acceptable states */
static hailey_intg stateType[] = {
	NOFS, /* 00 */
	NOFS, /* 01 */
	FSNR, /* 02 (MID) - Methods */
	FSWR, /* 03 (KEY) */
	NOFS, /* 04 */
	FSNR, /* 05 (SL) */
	FSNR, /* 05 (IL) */
	FSNR, /* 05 (FL) */
	FSNR, /* 06 (Err1 - no retract) */
	FSWR  /* 07 (Err2 - retract) */
};

/*
-------------------------------------------------
TO_DO: Adjust your functions'definitions
-------------------------------------------------
*/

/* Static (local) function  prototypes */
hailey_intg startScanner(ReaderPointer psc_buf);
Token tokenizer(hailey_void);
static hailey_intg nextClass(hailey_char c);				/* character class function */
static hailey_intg nextState(hailey_intg, hailey_char);		/* state machine function */
hailey_void printToken(Token t);

/*
-------------------------------------------------
Automata definitions
-------------------------------------------------
*/

/* TO_DO: Pointer to function (of one char * argument) returning Token */
typedef Token(*PTR_ACCFUN)(hailey_char* lexeme);

/* Declare accepting states functions */
Token funcSL(hailey_char lexeme[]);
Token funcID(hailey_char lexeme[]);
Token funcKEY(hailey_char lexeme[]);
Token funcErr(hailey_char lexeme[]);
Token funcIL(hailey_char lexeme[]);
Token funcFL(hailey_char lexeme[]);

/*
 * Accepting function (action) callback table (array) definition
 * If you do not want to use the typedef, the equvalent declaration is:
 */

 /* TO_DO: Define final state table */
static PTR_ACCFUN finalStateTable[] = {
	NULL,      /* -     [00] */
	NULL,      /* -     [01] */
	funcID,    /* MNID  [02] - Methods */
	funcKEY,   /* KEY   [03] - Keywords */
	NULL,      /* -     [04] */
	funcSL,    /* SL    [05] - String Literal */
	funcIL,    /* IL    [06] - Integer Literal */
	funcFL,    /* FL    [07] - Float Literal */
	funcErr,    /* ERR1 [08] - No retract */
	funcErr    /* ERR2  [09] - Retract */
};


/*
-------------------------------------------------
Language keywords
-------------------------------------------------
*/

/* TO_DO: Define the number of Keywords from the language */
#define KWT_SIZE 10

/* TO_DO: Define the list of keywords */
static hailey_char* keywordTable[KWT_SIZE] = {
	"data",
	"code",
	"int",
	"real",
	"string",
	"if",
	"then",
	"else",
	"while",
	"do"
};

/* About indentation (useful for positional languages (ex: Python, Cobol) */

/*
 * Scanner attributes to be used (ex: including: intendation data
 */

#define INDENT '\t'  /* Tabulation */

 /* TO_DO: Should be used if no symbol table is implemented */
typedef struct languageAttributes {
	hailey_char indentationCharType;
	hailey_intg indentationCurrentPos;
	/* TO_DO: Include any extra attribute to be used in your scanner (OPTIONAL and FREE) */
} LanguageAttributes;

/* Number of errors */
hailey_intg numScannerErrors;

#endif
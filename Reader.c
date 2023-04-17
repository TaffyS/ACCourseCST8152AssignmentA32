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
* File name: Reader.h
* Compiler: MS Visual Studio 2022
* Course: CST 8152 – Compilers, Lab Section: [011, 012, 013]
* Assignment: A12.
* Date: Jan 01 2023
* Professor: Paulo Sousa
* Purpose: This file is the main code for Reader (.c)
************************************************************
*/

/*
 *.............................................................................
 * MAIN ADVICE:
 * Please check the "TODO" labels to develop your activity.
 *.............................................................................
 */

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef READER_H_
#include "Reader.h"
#endif

/*
***********************************************************
* Function name: readerCreate
* Purpose: Creates the buffer reader according to capacity, increment
	factor and operational mode ('f', 'a', 'm')
* Author: Svillen Ranev / Paulo Sousa
* History/Versions: S22
* Called functions: calloc(), malloc()
* Parameters:
*   size = initial capacity
*   increment = increment factor
*   mode = operational mode
* Return value: bPointer (pointer to reader)
* Algorithm: Allocation of memory according to inicial (default) values.
* TODO ......................................................
*	- Adjust datatypes for your LANGUAGE.
*   - Use defensive programming
*	- Check boundary conditions
*	- Check flags.
*************************************************************
*/

ReaderPointer readerCreate(hailey_intg size, hailey_intg increment, hailey_intg mode) {
	ReaderPointer readerPointer;
	/* TO_DO: Defensive programming */
	/* TO_DO: Adjust the values according to parameters */
	/*If there is no value for size, default values(for sizeand increment) are used*/
	if (!size) {
		size = READER_DEFAULT_SIZE;
		increment = READER_DEFAULT_INCREMENT;
	}
	
	
	readerPointer = (ReaderPointer)calloc(1, sizeof(BufferReader));
	/* TO_DO: Defensive programming */
	if (!readerPointer) {
		return NULL;
	}
	
	readerPointer->content = (hailey_char*)malloc(size);
	if (!readerPointer) {
		return NULL;
	}

	/*If there is no value for increment, the mode must be fixed*/
	if (mode == 'F'|| !increment) {
		readerPointer->mode = MODE_FIXED;
		readerPointer->increment = READER_DEFAULT_INCREMENT;
	}
	else if (mode == 'A') {
		readerPointer->mode = MODE_ADDIT;
		readerPointer->increment = increment;
	}
	else if (mode == 'M') {
		readerPointer->mode = MODE_MULTI;
		readerPointer->increment = increment;
	}
	/*If mode is different from valid options (F, A or M), no reader must be created.*/
	else if (mode != MODE_FIXED && mode != MODE_ADDIT && mode != MODE_MULTI) {
		return NULL;
	}

	/* TO_DO: Defensive programming */
	/* TO_DO: Initialize the histogram */
	for (int i = 0; i < NCHAR; i++) {
		readerPointer->histogram[i] = 0;
	}

	/* TO_DO: Initialize flags */
	/* TO_DO: The created flag must be signalized as EMP */
	
	readerPointer->flags = READER_DEFAULT_FLAG;
	readerPointer->size = size;

	return readerPointer;
}


/*
***********************************************************
* Function name: readerAddChar
* Purpose: Adds a char to buffer reader
* Parameters:
*   readerPointer = pointer to Buffer Reader
*   ch = char to be added
* Return value:
*	readerPointer (pointer to Buffer Reader)
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/

ReaderPointer readerAddChar(ReaderPointer const readerPointer, hailey_char ch) {
	hailey_char* tempReader = NULL;
	hailey_intg newSize = 0;
	/* TO_DO: Defensive programming: check buffer and valid char (increment numReaderErrors) */
	if (!readerPointer) {
		return NULL;
	}
	/* TO_DO: Reset Realocation */
	readerPointer->flags &= READER_RESET_FLAG;

	/* TO_DO: Test the inclusion of chars */
	if (readerPointer->position.wrte * (hailey_intg)sizeof(hailey_char) < readerPointer->size) {
		/* TO_DO: This buffer is NOT full */
	} else {
		/* TO_DO: Reset Full flag */
		readerPointer->flags &= READER_RESET_FLAG;

		switch (readerPointer->mode) {
		case MODE_FIXED:
			return NULL;
		case MODE_ADDIT:
			/* TO_DO: Adjust new size */
			newSize = readerPointer->size + readerPointer->increment;
			printf("********** %d\n", newSize);
			/* TO_DO: Defensive programming */
			if (newSize <= 0 || newSize >= READER_MAX_SIZE) {
				return NULL;
			}
			else if (newSize > 0 && newSize >= READER_MAX_SIZE) {
				newSize = READER_MAX_SIZE;
			}
			break;
		case MODE_MULTI:
			/* TO_DO: Adjust new size */
			newSize = readerPointer->size * readerPointer->increment;
			printf("********** %d\n", newSize);
			/* TO_DO: Defensive programming */
			if (newSize <= 0 || newSize >= READER_MAX_SIZE) {
				return NULL;
			}
			else if (newSize > 0 && newSize >= READER_MAX_SIZE) {
				newSize = READER_MAX_SIZE;
			}
			break;

		default:
			return NULL;
		}
		/* TO_DO: Defensive programming */
		/* TO_DO: Check Relocation */
		tempReader = (hailey_char*)realloc(readerPointer->content, newSize);
		if (!tempReader) {
			return NULL;
		}
		if (readerPointer->content != tempReader) {
			readerPointer->flags |= READER_RELOCATION_FLAG;
		}

		readerPointer->size = newSize;
		readerPointer->content = tempReader;
		
	}
	/* TO_DO: New reader allocation */
	/* TO_DO: Add the char */
	readerPointer->content[readerPointer->position.wrte++] = ch;

	/* TO_DO: Updates histogram */
	if (ch >= 0 && ch < NCHAR) {
		readerPointer->histogram[ch]++;
	}

	return readerPointer;
}

/*
***********************************************************
* Function name: readerClear
* Purpose: Clears the buffer reader
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
hailey_boln readerClear(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer) {
		return HAILEY_FALSE;
		/* Reset offsets */
		readerPointer->position.mark= 0;
		readerPointer->position.read = 0;
		readerPointer->position.wrte = 0;
		readerPointer->flags = READER_RESET_FLAG;
	}
	/* TO_DO: Adjust flags original */
	return HAILEY_TRUE;
}

/*
***********************************************************
* Function name: readerFree
* Purpose: Releases the buffer address
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
hailey_boln readerFree(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer) {
		return HAILEY_FALSE;
	}
	/* TO_DO: Free pointers */
	free(readerPointer->content);
	free(readerPointer);
	return HAILEY_TRUE;
}

/*
***********************************************************
* Function name: readerIsFull
* Purpose: Checks if buffer reader is full
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
hailey_boln readerIsFull(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer) {
		return HAILEY_FALSE;
	}
	/* TO_DO: Check flag if buffer is FUL */
	if ((readerPointer->flags & READER_CHECK_FLAG) == READER_FULL_FLAG) {
		return HAILEY_TRUE;  /* Buffer is full */
	}
	else {
		return HAILEY_FALSE; /* Buffer is not full */
	}
}


/*
***********************************************************
* Function name: readerIsEmpty
* Purpose: Checks if buffer reader is empty.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
hailey_boln readerIsEmpty(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer) {
		return HAILEY_FALSE;
	}
	/* TO_DO: Check flag if buffer is EMP */
	if ((readerPointer->flags & READER_CHECK_FLAG) == READER_EMPTY_FLAG) {
		return HAILEY_TRUE;  /* Buffer is empty */
	}
	else {
		return HAILEY_FALSE; /* Buffer is not empty */
	}
}

/*
***********************************************************
* Function name: readerSetMark
* Purpose: Adjust the position of mark in the buffer
* Parameters:
*   readerPointer = pointer to Buffer Reader
*   mark = mark position for char
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
hailey_boln readerSetMark(ReaderPointer const readerPointer, hailey_intg mark) {
	/* TO_DO: Defensive programming */
	if (!readerPointer || mark<0 || mark > readerPointer->position.wrte) {
		return HAILEY_FALSE;
	}
	/* TO_DO: Adjust mark */
	readerPointer->position.mark = mark;
	return HAILEY_TRUE;
}


/*
***********************************************************
* Function name: readerPrint
* Purpose: Prints the string in the buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Number of chars printed.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
hailey_intg readerPrint(ReaderPointer const readerPointer) {
	hailey_intg cont = 0;
	hailey_char c;
	/* TO_DO: Defensive programming (including invalid chars) */
	if (!readerPointer) {
		return  READER_ERROR;
	}
	c = readerGetChar(readerPointer);
	/* TO_DO: Check flag if buffer EOB has achieved */
	while (cont < readerPointer->position.wrte && !(readerPointer->flags & READER_ENDOFBUFFER_FLAG)) {
		cont++;
		printf("%c", c);
		c = readerGetChar(readerPointer);
	}
	return cont;
}

/*
***********************************************************
* Function name: readerLoad
* Purpose: Loads the string in the buffer with the content of
	an specific file.
* Parameters:
*   readerPointer = pointer to Buffer Reader
*   fileDescriptor = pointer to file descriptor
* Return value:
*	Number of chars read and put in buffer.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
hailey_intg readerLoad(ReaderPointer const readerPointer, FILE* const fileDescriptor) {
	hailey_intg size = 0;
	hailey_char c;
	/* TO_DO: Defensive programming */
	if (!readerPointer || !fileDescriptor) {
		return  READER_ERROR;
	}
	c = (hailey_char)fgetc(fileDescriptor);
	while (!feof(fileDescriptor)) {
		if (!readerAddChar(readerPointer, c)) {
			ungetc(c, fileDescriptor);
			return READER_ERROR;
		}
		c = (char)fgetc(fileDescriptor);
		if (c != EOF) {
			size++;
		}
	}
	/* TO_DO: Defensive programming */
	if (ferror(fileDescriptor)) {
		return READER_ERROR;
	}
	return size;
}


/*
***********************************************************
* Function name: readerRecover
* Purpose: Rewinds the buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
hailey_boln readerRecover(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer) {
		return HAILEY_FALSE;
	}
	/* TO_DO: Recover positions */
	readerPointer->position.read = 0;
	readerPointer->position.mark = 0;
	//Read the specification
	return HAILEY_TRUE;
}


/*
***********************************************************
* Function name: readerRetract
* Purpose: Retracts the buffer to put back the char in buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
hailey_boln readerRetract(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer) {
		return HAILEY_FALSE;
	}
	/* TO_DO: Retract (return 1 pos read) */
	if (readerPointer->position.read > 0) {
		readerPointer->position.read--;
		return HAILEY_TRUE;
	}
	else {
		return HAILEY_FALSE;
	}
}


/*
***********************************************************
* Function name: readerRestore
* Purpose: Resets the buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
hailey_boln readerRestore(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer) {
		return HAILEY_FALSE;
	}
	/* TO_DO: Restore positions (read/mark) */
	readerPointer->position.read = readerPointer->position.mark;
	return HAILEY_TRUE;
}



/*
***********************************************************
* Function name: readerGetChar
* Purpose: Returns the char in the getC position.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Char in the getC position.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
hailey_char readerGetChar(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer) {
		return READER_ERROR;
	}
	/* TO_DO: Check condition to read/wrte */
	if (readerPointer->position.read == readerPointer->position.wrte) {
		/* TO_DO: Set EOB flag */
		readerPointer->flags |= READER_ENDOFBUFFER_FLAG;
		return '\0';
	}
	/* TO_DO: Reset EOB flag */
	else {
		readerPointer->flags &= ~READER_ENDOFBUFFER_FLAG;
	}
	return readerPointer->content[readerPointer->position.read++];
}


/*
***********************************************************
* Function name: readerGetContent
* Purpose: Returns the pointer to String.
* Parameters:
*   readerPointer = pointer to Buffer Reader
*   pos = position to get the pointer
* Return value:
*	Position of string char.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
hailey_char* readerGetContent(ReaderPointer const readerPointer, hailey_intg pos) {
	/* TO_DO: Defensive programming */
	if (!readerPointer || !readerPointer->content|| pos < 0 || pos >= readerPointer->position.wrte) {
		return NULL;
	}
	/* TO_DO: Return content (string) */
	return &(readerPointer->content[pos]);
}



/*
***********************************************************
* Function name: readerGetPosRead
* Purpose: Returns the value of getCPosition.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	The read position offset.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
hailey_intg readerGetPosRead(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer) {
		return READER_ERROR;
	}
	/* TO_DO: Return read */
	return readerPointer->position.read;
}


/*
***********************************************************
* Function name: readerGetPosWrte
* Purpose: Returns the position of char to be added
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Write position
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
hailey_intg readerGetPosWrte(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer) {
		return READER_ERROR;
	}
	/* TO_DO: Return wrte */
	//return (readerPointer->position.wrte >= 0) ? readerPointer->position.wrte : READER_DEFAULT_SIZE;
	return readerPointer->position.wrte;
}


/*
***********************************************************
* Function name: readerGetPosMark
* Purpose: Returns the position of mark in the buffer
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Mark position.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
hailey_intg readerGetPosMark(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer) {
		return READER_ERROR;
	}
	readerPointer->position.mark = readerPointer->position.read;
	/* TO_DO: Return mark */
	return readerPointer->position.mark;
}

/*
***********************************************************
* Function name: readerGetMode
* Purpose: Returns the operational mode
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Operational mode.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
hailey_intg readerGetMode(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer) {
		return READER_ERROR;
	}
	/* TO_DO: Return mode */
	return readerPointer->mode;
}

/*
***********************************************************
* Function name: readerGetSize
* Purpose: Returns the current buffer capacity
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Size of buffer.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
hailey_intg readerGetSize(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer) {
		return READER_ERROR;
	}
	/* TO_DO: Return size */
	return readerPointer->size;
}

/*
***********************************************************
* Function name: readerGetInc
* Purpose: Returns the buffer increment.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	The Buffer increment.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
hailey_intg readerGetInc(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer) {
		return READER_ERROR;
	}
	/* TO_DO: Return increment */
	return readerPointer->increment;
}

/*
***********************************************************
* Function name: readerGetFlags
* Purpose: Returns the entire flags of Buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Flags from Buffer.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
hailey_byte readerGetFlags(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer) {
		return READER_DEFAULT_FLAG;
	}
	/* TO_DO: Return flags */
	return readerPointer->flags;
}


/*
***********************************************************
* Function name: readerShowStat
* Purpose: Returns the number of chars used.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Number of chars.
* TO_DO:
*   - Use defensive programming
*	- Adjust for your LANGUAGE.
*************************************************************
*/
hailey_intg readerShowStat(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer) {
		return READER_ERROR;
	}
	/* TO_DO: Updates the histogram */
	int histogram[NCHAR] = { 0 };
	for (int i = 0; i < readerPointer->position.wrte; i++) {
		histogram[readerPointer->content[i]]++;
	}
	int count = 0;
	for (int i = 0; i < NCHAR; i++) {
		if (histogram[i] > 0) {
			count++;
		}
	}
	return count;
}

/*
***********************************************************
* Function name: readerNumErrors
* Purpose: Returns the number of errors found.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Number of errors.
* TO_DO:
*   - Use defensive programming
*	- Adjust for your LANGUAGE.
*************************************************************
*/
hailey_intg readerNumErrors(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer) {
		return READER_ERROR;
	}
	/* Count number of errors */
	hailey_intg count = 0;
	for (hailey_intg i = 0; i < readerPointer->position.wrte; i++) {
		if (readerPointer->content[i] < 0 || readerPointer->content[i] >= NCHAR) {
			count++;
		}
	}

	return count;
}

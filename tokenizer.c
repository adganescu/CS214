/*
 * tokenizer.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
 * Tokenizer type.  You need to fill in the type as part of your implementation.
 */

struct TokenizerT_ {

	char* sep;
	char* tokStr;
	int curr;
	int tail;
	int tokCount;
};

typedef struct TokenizerT_ TokenizerT;

/*
 * TKCreate creates a new TokenizerT object for a given set of separator
 * characters (given as a string) and a token stream (given as a string).
 * 
 * TKCreate should copy the two arguments so that it is not dependent on
 * them staying immutable after returning.  (In the future, this may change
 * to increase efficiency.)
 *
 * If the function succeeds, it returns a non-NULL TokenizerT.
 * Else it returns NULL.
 *
 * You need to fill in this function as part of your implementation.
 */

TokenizerT *TKCreate(char *separators, char *ts) {

/* Copy created and malloc'd tokenizer object to return */


	TokenizerT* token = malloc(sizeof(TokenizerT));

	token->sep = separators;
	token->tokStr = ts;
	token->curr = 0;
	token->tokCount = 0;	
	token->tail = 0;
	
	return token;
}

/*
 * TKDestroy destroys a TokenizerT object.  It should free all dynamically
 * allocated memory that is part of the object being destroyed.
 *
 * You need to fill in this function as part of your implementation.
 */

void TKDestroy(TokenizerT *tk) {
}

/*
 * TKGetNextToken returns the next token from the token stream as a
 * character string.  Space for the returned token should be dynamically
 * allocated.  The caller is responsible for freeing the space once it is
 * no longer needed.
 *
 * If the function succeeds, it returns a C string (delimited by '\0')
 * containing the token.  Else it returns 0.
 *
 * You need to fill in this function as part of your implementation.
 */

char *TKGetNextToken(TokenizerT *tk) {

/* the tokenizer object has the indices, which get updated at the end of this sub_
 * routine
 */
	int i = 0;
	int n = tk->curr;
	int m = tk->tail;

	while (tk->sep[i] != '\0') {

		while (tk->tokStr[n] != '\0') {
			printf("HERE\n");
			if (tk->sep[i] == tk->tokStr[n]) {

/* if the first character checked matches a delimiter, no token can be made*/

				if (n - m == 0) {
					tk->curr += 1;
					tk->tail += 1;
					n++;
					m++;
				continue;
				} 
					else {
/* Else if n - m != 0 (Token is created here) */					
				
				}
			}
				else {
/* Else if the tk->sep[i] != tk->tokStr[n] (variables n is incremented here) */
				}
					

		n++;	
		}
	i++;
	printf("NOT NULL\n");
	}

  return NULL;
}

/*
 * main will have two string arguments (in argv[1] and argv[2]).
 * The first string contains the separator characters.
 * The second string contains the tokens.
 * Print out the tokens in the second string in left-to-right order.
 * Each token should be printed on a separate line.
 */

int main(int argc, char **argv) {


	char* nextToken;
	char* delim;
	char* input;
	TokenizerT* tokenizer =  malloc(sizeof(TokenizerT)) ;

	if (argc != 3) {
		fprintf(stderr, "ERROR: INVALID NUMBER OF INPUTS\n");
		exit(EXIT_FAILURE);
	}


	if (strcmp(argv[2], "") == 0) {
		printf("NO STRING TO TOKENIZE\n");
	}

	delim = argv[1];
	input = argv[2];

	*tokenizer = *TKCreate(delim, input);

	nextToken = TKGetNextToken(tokenizer);	 

	printf("FIRST %s\n", tokenizer->sep);
	printf("SECOND %s\n", tokenizer->tokStr);	

  return 0;
}

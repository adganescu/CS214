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

/* sep stores separators, tokStr stores the String to be tokenized. */


	char* sep;
	char* tokStr;
	int curr;

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
	
	return token;
}

/*
 * TKDestroy destroys a TokenizerT object.  It should free all dynamically
 * allocated memory that is part of the object being destroyed.
 *
 * You need to fill in this function as part of your implementation.
 */

void TKDestroy(TokenizerT *tk) {

	free(tk);
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


/* Where the magic happens. */

	int n = 0; 
	int m = 0; 
	int i = 0;
	char* nextToken;
	char* tempStr = tk->tokStr;
	int j = 0;
	char* backUp = malloc(strlen(tk->tokStr)*sizeof(char));

/* While the original input is not altered, backUp is created from tokStr to manipulate for tokenizing */

	memcpy(backUp, tk->tokStr, strlen(tk->tokStr) + 1);
	backUp[strlen(tk->tokStr)] = '\0';
 	
/* Two loops: each character in tokStr is compared against a separator, and each possible case is accounted for */

	while (tk->tokStr[n] != '\0') {
		i = 0;
		while (tk->sep[i] != '\0') {

/* If there is a match between delimiter and character */

			if (tk->sep[i] == tempStr[n]) {

/* If first character checked is a delimiter */

				if (n - m == 0) {
					tempStr++;
					tk->tokStr = tempStr;
					return 0;
				}
				else {

/* If character isn't the first checked, but matches a delimiter. nextToken stores the token, and then backUp is incremented
 * to remove the string that was already tokenized */
				 
					nextToken = malloc((n-m+1)*sizeof(char));
					while (m + j < n) {
					
						nextToken[j] = tempStr[m + j];
					
						j++;
					}
					tempStr[n - m] = '\0';
				
					j = n - m;
					
						
					while (j > 0) {
						backUp++;
						j--;

					}
					
				
					tk->tokStr = malloc(strlen(backUp)*sizeof(char));
					
					memcpy(tk->tokStr, backUp, strlen(backUp)*sizeof(char));
					backUp = tk->tokStr;	
						
					return nextToken;
				}
			} 
		i++;
		}
	n++; 
		
	}		

/* Taking the last token as a case */


			if (strlen(tk->tokStr) > 0) {
				
				nextToken = malloc(strlen(tk->tokStr) + 1);
				while (j < strlen(tk->tokStr)) {
				nextToken[j] = tk->tokStr[j];
				j++;
				}
				nextToken[strlen(tk->tokStr)] = '\0';
				tk->tokStr = "";
				return nextToken;
			}
		
		
		
	
	return 0;
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

/* iteration for tokens occurs here */
	while (strlen(tokenizer->tokStr) != 0) {	
		nextToken = TKGetNextToken(tokenizer);

		if (nextToken != 0) {
			printf("%s\n", nextToken);
		}
	}

	TKDestroy(tokenizer);
  return 0;
}

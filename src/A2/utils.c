/*
 * Created by Sotirios-Efstathios Maneas on 2017-01-02.
 */

#include <stdio.h>
#include <string.h>

#include <ctype.h>
#include "utils.h"

/*
 * Tokenize the string stored in cmd based on DELIMITERS as separators.
 * Return the number of tokens, and store pointers to them in cmd_argv.
 */
int tokenize(char *cmd, char **cmd_argv) {
		char *token;
		const char del[2] = " ";
	  token = strtok(cmd, del);

		if(*(token) == 'p') {
			return 1;
		}

		if(strcmp(token, "i") != 0 && strcmp(token, "q") != 0 && *(token) != 'p'){
				fprintf(stderr, "Invalid command.\n");
				return 4;
		}

	  int i = 0;
	  cmd_argv[i] = token;

	  while(token != NULL) {
	    token = strtok(NULL, del);
//			fprintf(stdout, "%s\n", token);
	    cmd_argv[i++] = token;
	  }
	  return i++;
}

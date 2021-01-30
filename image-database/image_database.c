/*
 * Created by Sotirios-Efstathios Maneas on 2017-01-02.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"
#include "utils.h"

int main(void) {

        // char array to hold a line of input
	char buf[BUFFER_SIZE] = {'\0'};

        // char* array to hold the pointers to tokens
	char *args[INPUT_ARG_MAX_NUM];

        // the root of the tree
        struct TreeNode root;
        root.value = "";
        root.child = NULL;
        root.sibling = NULL;

	struct TreeNode *root_ptr = &root;

	while(fgets(buf, BUFFER_SIZE, stdin)) {
		int num_args = tokenize(buf, args);

	if(num_args != 5 && num_args != 4 && num_args != 1) {
 		fprintf(stderr, "Invalid command.\n");
	}

		if(num_args == 5 && buf[0] == 'i'){
				tree_insert(root_ptr, args);
		}
		else if(num_args == 4 && buf[0] == 'q'){
				tree_search(root_ptr, args);
		}
		else if(num_args == 1 && buf[0] == 'p'){
				tree_print(root_ptr);
		}
	}

  return 0;
}

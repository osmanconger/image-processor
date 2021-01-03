/*
 * Created by Sotirios-Efstathios Maneas on 2017-01-02.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "tree.h"

/**
 *  A helper function that allocates a new tree node.
 *
 *  @param value The entry's value. It represents either an attribute or a filename.
 *  @return A pointer to the newly allocated node.
 *  (for now it returns NULL, so the compiler does not complain)
 */

struct TreeNode *allocate_node(const char *value) {
	char *value_cpy = malloc(sizeof(char)*60);
	strcpy(value_cpy, value);
	struct TreeNode *p = (struct TreeNode *) malloc(sizeof(struct TreeNode));
	p->value = value_cpy;
	p->child = NULL;
	p->sibling = NULL;

	return p;
}

char *trim(char *string) {
    char* end = string + strlen(string);
    while(isspace(*--end));
    *(end+1) = '\0';
    return string;
}

struct TreeNode *horizontal_search(struct TreeNode *p, char *value){
    struct TreeNode* current = p;
    while(current->sibling != NULL) {
        if(strcmp(trim(current->sibling->value), trim(value)) > 0)
            return current;
        current = current->sibling;
    }
		return current;
}

/**
 *  Insert a new image to a tree
 *
 *  @param tree A pointer to the root of the tree.
 *  @param values An array, whose first three members are the attribute values for
 *                the image and the last one is the filename
 */
void tree_insert(struct TreeNode *root, char **values) {
	int check = 0;
	int check2 = 0;
	int check3 = 0;
	char color[60];
	strcpy(color, values[0]);
	char shape[60];
	strcpy(shape, values[1]);
	char texture[60];
	strcpy(texture, values[2]);
	char name[60];
	strcpy(name, values[3]);

	struct TreeNode *temp = NULL;
	struct TreeNode *temp2 = NULL;
	struct TreeNode *temp3 = NULL;

	if(root->child == NULL) {
		root->child = allocate_node(color);
	}
	temp = root->child;

	temp2 = temp;
	if(strcmp(temp->value, color) != 0) {
		while(temp->sibling != NULL) {
			if(strcmp(temp->sibling->value, color) == 0) {
				temp = temp->sibling;
				check++;
				break;
			}
			temp = temp->sibling;
		}
  }
	else {
		check++;
	}

  if(temp->sibling == NULL && check == 0)  {
		temp = horizontal_search(temp2, color);

		temp3 = temp->sibling;
		temp->sibling = allocate_node(color);
		temp = temp->sibling;
		temp->sibling = temp3;

		temp->child = allocate_node(shape);
		temp = temp->child;

		temp->child = allocate_node(texture);
		temp = temp->child;

		temp->child = allocate_node(name);
	}

	else {
		if(temp->child == NULL) {
			temp->child = allocate_node(shape);
		}
		temp = temp->child;

		temp2 = temp;
		if(strcmp(temp->value, shape) != 0) {
			while(temp->sibling != NULL) {
				if(strcmp(temp->sibling->value, shape) == 0) {
					temp = temp->sibling;
					check2++;
					break;
				}
				temp = temp->sibling;
		  }
		}
		else {
			check2++;
		}

			if(temp->sibling == NULL && check2 == 0)  {
					temp = horizontal_search(temp2, shape);

					temp3 = temp->sibling;
					temp->sibling = allocate_node(shape);
					temp = temp->sibling;
					temp->sibling = temp3;

					temp->child = allocate_node(texture);
					temp = temp->child;

					temp->child = allocate_node(name);
			}
			else {
				if(temp->child == NULL) {
					temp->child = allocate_node(texture);
				}
				temp = temp->child;

				temp2 = temp;
				if(strcmp(temp->value, texture) != 0) {
					while(temp->sibling != NULL) {
						if(strcmp(temp->sibling->value, texture) == 0) {
							temp = temp->sibling;
							check3++;
							break;
						}
						temp = temp->sibling;
				  }
				}
				else {
					check3++;
				}
				if(temp->sibling == NULL && check3 == 0)  {
						temp = horizontal_search(temp2, texture);

						temp3 = temp->sibling;
						temp->sibling = allocate_node(texture);
						temp = temp->sibling;
						temp->sibling = temp3;

						temp->child = allocate_node(name);
				}
				else {
					if(temp->child == NULL) {
						temp->child = allocate_node(name);
					}
			  	else {
						temp = temp->child;
						temp2 = temp;
						temp = horizontal_search(temp2, name);

						temp3 = temp->sibling;
						temp->sibling = allocate_node(name);
						temp = temp->sibling;
						temp->sibling = temp3;
					}
				}
			}
		}
}

struct TreeNode *search(struct TreeNode *p, char *value){
    struct TreeNode *current = p;
    while(current != NULL) {
        if(strcmp(trim(current->value), trim(value)) == 0) return current;
        current = current->sibling;
    }
		return NULL;
}


/**
 *  Searches a tree to print all files with matching attribute values.
 *
 *  @param tree A pointer to the root of the tree.
 *  @param values An array of attribute values
 */
void tree_search(const struct TreeNode *root, char **values) {
		struct TreeNode *temp = search(root->child, values[0]);

		if(temp != NULL) {
			struct TreeNode *temp2 = search(temp->child, values[1]);
			if(temp2 != NULL) {
				struct TreeNode *temp3 = search(temp2->child, values[2]);
  		  if(temp3 != NULL) {
					temp3 = temp3->child;
					while(temp3 != NULL) {
						fprintf(stdout, "%s ",trim(temp3->value));
						temp3 = temp3->sibling;
					}
				}
			}
		}
}

void tree_print_helper(const struct TreeNode *tree, int level, char **values) {
	const struct TreeNode *current;
	current = tree;

	if(current->child == NULL) {
		  const struct TreeNode *temp;
			temp = current;
			while(temp != NULL) {
					values[4] = temp->value;
					fprintf(stdout, "%s %s %s %s\n", values[1], values[2], values[3], values[4]);
					temp = temp->sibling;
			}
			return;
	}

	if(current->child != NULL) {
			values[level] = current->value;
			tree_print_helper(current->child, level + 1, values);
	}

	if(current->sibling != NULL) {
			tree_print_helper(current->sibling, level, values);
	}
}

/**
 *  Prints a complete tree to the standard output.
 *
 *  @param tree A pointer to the root of the tree.
 */
void tree_print(const struct TreeNode *tree) {
 		char *values[5];
		tree_print_helper(tree, 0, values);
}

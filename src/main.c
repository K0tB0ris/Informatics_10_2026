#include <stdio.h>
#include <stdlib.h>

struct list {
	char bracket;
	struct list *prev;
};

struct list *add_last(char brck, struct list *stack) {
	struct list *obj = malloc(sizeof(struct list));
	obj->prev = stack;
	obj->bracket = brck;
	return obj;
}

struct list *init_list(char brck) {
	struct list *obj = malloc(sizeof(struct list));
	obj->prev = NULL;
	obj->bracket = brck;
	return obj;
}

struct list *free_node(struct list *stack) {
	struct list *prev = NULL;
	if (stack != NULL) {
		prev = stack->prev;
	}
	free(stack);
	return prev;
}

struct list *check_list(struct list *stack) {
	struct list *prev = stack;
	if (stack == NULL) {
		return NULL;
	}
	if (stack->prev != NULL) {
		if ((stack->bracket == ')') && (stack->prev->bracket == '(')) {
			prev = stack->prev->prev;
			struct list *tmp = stack;
			tmp = free_node(stack);
			free_node(tmp);
		} else if ((stack->bracket == '}') &&
			   (stack->prev->bracket == '{')) {
			prev = stack->prev->prev;
			struct list *tmp = stack;
			tmp = free_node(tmp);
			free_node(tmp);
		} else if ((stack->bracket == ']') &&
			   (stack->prev->bracket == '[')) {
			prev = stack->prev->prev;
			struct list *tmp = stack;
			tmp = free_node(tmp);
			free_node(tmp);
		}
	}
	return prev;
}

int check_balanced(FILE *stream) {
	char cur_char = '0';
	struct list *stack = NULL;
	do {
		if (fscanf(stream, "%c", &cur_char) == 1) {
			if (cur_char == '\n') {
				break;
			}
			if (stack == NULL) {
				stack = init_list(cur_char);
			} else {
				stack = add_last(cur_char, stack);
			}
			stack = check_list(stack);
		} else {
			break;
		}
	} while (cur_char != '\n');
	if (stack != NULL) {
		printf("NOT BALANCED\n");
		while (stack != NULL) {
			stack = free_node(stack);
		}
		return 0;
	}
	printf("BALANCED\n");
	return 0;
}

int main() { check_balanced(stdin); }

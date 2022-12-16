#include "monty.h"

#define STACK_SIZE 256

int stack[STACK_SIZE]; // the stack
int stack_top = 0; // the top of the stack

void push(int value) {
  if (stack_top == STACK_SIZE) {
    // stack is full, cannot push
    fprintf(stderr, "L%d: stack overflow\n", line_number);
    exit(EXIT_FAILURE);
  }
  stack[stack_top++] = value;
}

void pall() {
  for (int i = stack_top - 1; i >= 0; i--) {
    printf("%d\n", stack[i]);
  }
}

int main(int argc, char **argv) {
  if (argc != 2) {
    // incorrect number of arguments
    fprintf(stderr, "USAGE: monty file\n");
    exit(EXIT_FAILURE);
  }

  // open the file
  FILE *file = fopen(argv[1], "r");
  if (file == NULL) {
    fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
    exit(EXIT_FAILURE);
  }

  // read the file line by line
  char *line = NULL;
  size_t line_size = 0;
  int line_number = 0;
  while (getline(&line, &line_size, file) != -1) {
    line_number++;

    // split the line into words
    char *word = strtok(line, " \n\t\r");
    if (word == NULL) {
      // empty line, skip
      continue;
    }

    // parse the opcode
    if (strcmp(word, "push") == 0) {
      // push opcode

      // get the next word (should be the value to push)
      word = strtok(NULL, " \n\t\r");
      if (word == NULL) {
        fprintf(stderr, "L%d: usage: push integer\n", line_number);
        exit(EXIT_FAILURE);
      }

      // convert the word to an integer
      int value = atoi(word);

      // push the value onto the stack
      push(value);
    } else if (strcmp(word, "pall") == 0) {
      // pall opcode

      // print all values on the stack
      pall();
    } else {
      // unknown opcode
      fprintf(stderr, "L%d: unknown instruction %s\n", line_number, word);
      exit(EXIT_FAILURE);
    }
  }

  // clean up and exit
  free(line);
  fclose(file);
  exit(EXIT_SUCCESS);
}

#include <stdlib.h>
#include <stdio.h>

#define BUF_SIZE 10
#define VL_1 0
#define VL_2 1
#define VL_PRIV 2
#define VL_PASS 10

char *password = "supersecretpassword";

struct List {
  int key;
  int value;
  struct List *next;
} *config = NULL;

enum state { INIT, PASSWORD, INSERT, DUMP_CONFIGURATION };

void insert(int key, int value) {
  struct List **config_ptr = &config;
  while(*config_ptr != NULL && (*config_ptr)->key != key) {
    config_ptr = &((*config_ptr)->next);
  }
  if(*config_ptr == NULL) {
    *config_ptr = (struct List *) malloc(sizeof(*config_ptr));
    (*config_ptr)->key = key;
  }
  (*config_ptr)->value = value;
}

int find(int key) {
  struct List *config_ptr = config;
  while(config_ptr != NULL && config_ptr->key != key) { config_ptr = config_ptr->next; }
  if(config_ptr == NULL) {
    printf("KEY NOT FOUND");
    return -1;
  }
  return config_ptr->value;
}

void dump_configuration() {
  struct List *config_ptr = config;
  printf("configuration:\n");
  while(config_ptr != NULL) {
    printf("\t %d: %d\n", config_ptr->key, config_ptr->value);
    config_ptr = config_ptr->next;
  }
}

void repl() {
  char buf[BUF_SIZE];
  int completed = 0;
  enum state command = INIT;
  int pass = -1;
  int insert_key = VL_2;
  printf("PLEASE ENTER PASSCODE:\n");
  scanf("%d", &pass);
  printf("Please overflow my buffers:\n");
  scanf("%s", buf);
  while(!completed) {
    int value;
    switch (command) {
       case INIT:
         value = find(VL_1);
         printf("INIT_VALUE -- %d\n", value);
         command = PASSWORD;
         break;
    case PASSWORD:
         value = find(VL_PASS);
         if(value == pass) {
            command = DUMP_CONFIGURATION;
         } else {
            completed = 1;
         }
         break;
    case DUMP_CONFIGURATION:
      dump_configuration();
      break;
    case INSERT:
      insert(insert_key, pass);
      command = INIT;
      break;
    }
  }
  printf("local variables:\n\tcompleted: %d\n\tcommand: %d\n\tpass: %d\n\tinsert_key: %d\n", completed, command, pass, insert_key);
}

int main() {
  insert(VL_1, 10);
  insert(VL_2, 32);
  insert(VL_PASS, 1337);
  insert(VL_PRIV, 0);
  repl();
  printf("privilege level is %d!\n", find(VL_PRIV));
  return 0;
}



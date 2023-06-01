#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 100

char *user_input1() {
  return "<replacement>";
}

char *user_input2() {
  return "%s%s%s";
}

void faulty() {

  // null terminated
  char buf[SIZE] = {'\0'};
  int buf_len = sizeof(buf);
  char *start_ptr = buf;
  char *current_ptr = buf;
  // We have a buffer and two pointers to it:
  // buf: [_, _, _, ...]   (buf_len elements)
  //      ^
  //      |- start_ptr, current_ptr

  char *data = user_input1();
  char *src_ptr = user_input2();
  int data_len, avail_cap;

  while(*src_ptr) {

    if(strncmp(src_ptr, "%s", 2) == 0) {
      data_len = strlen(data);
      avail_cap = buf_len - strlen(start_ptr);

      strncpy(current_ptr, data, avail_cap);

      if (((current_ptr + data_len) - start_ptr + 1) > buf_len) {
        current_ptr = start_ptr + buf_len - 1;
        goto done;
      } else {
        current_ptr += data_len;
      }
      src_ptr += 2;
    } else {
      if ((current_ptr - start_ptr + 1) > buf_len) { 
        current_ptr = start_ptr + buf_len - 1;
      }
      // when current_ptr is at the end,
      // i.e. current_ptr = start_ptr + buf_len - 1
      // overwrites the null_terminator of buf
      *current_ptr++ = *src_ptr++;      
    }
  }
  done:
   *current_ptr = '\0';
   printf("%s\n", buf);
}

int main() {
  faulty();
}

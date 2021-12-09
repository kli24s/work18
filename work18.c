#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <errno.h>

#include <sys/shm.h>

#include <unistd.h>
#include <fcntl.h>

#include <ctype.h>

// ============================================================================

#define READ 0
#define WRITE 1

// ============================================================================

int main() {

  printf("=====================================\n");
  printf("outputs in all uppercase\n");
  printf("=====================================\n");

  int fds_write[2];
  pipe(fds_write);

  int fds_read[2];
  pipe(fds_read);

  int f;
  f = fork();

  if (f) {

    while (42) {

      char input[1000];

      printf("enter input: ");
      fgets(input, 1000, stdin);

      write(fds_write[WRITE], input, strlen(input));

      read(fds_read[READ], input, sizeof(input));
      printf("     output: %s", input);

      printf("=====================================\n");

    }

  }

  else {

    while (42) {

      char input[1000];
      read(fds_write[READ], input, sizeof(input));

      int i;
      for (i = 0; i < strlen(input); i++) {
        input[i] = toupper(input[i]);
      }

      write(fds_read[WRITE], input, strlen(input));

    }

  }

  return 0;

}

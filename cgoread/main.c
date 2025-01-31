#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 

static long fileToBuffer(char *path, char **buffer) {
  FILE *fileptr;
  fileptr = fopen(path, "rb");  // Open the file in binary mode
  if (fileptr == NULL) {
    return 1;
  }

  fseek(fileptr, 0, SEEK_END);
  long filelen = ftell(fileptr);
  fseek(fileptr, 0, SEEK_SET);

  *buffer = (char *)malloc(filelen+1);
  fread(*buffer, sizeof(char), filelen, fileptr);
  fclose(fileptr);

  buffer[filelen] = '\0';
  //printf("%s", *buffer);

  return filelen;
}


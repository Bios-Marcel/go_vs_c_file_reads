#include <dirent.h> 
#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 

char* concat(const char *s1, const char *s2)
{
    char *result = malloc(strlen(s1) + strlen(s2) + 1); // +1 for the null-terminator
    // in real code you would check for errors in malloc here
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

int main(void) {
  DIR *d;
  struct dirent *dir;
  const char *dirName = "/home/marcel/scoop/buckets/main/bucket/";
  d = opendir(dirName);
  if (d) {
    FILE *fileptr;
    char *buffer;
    long filelen;

    while ((dir = readdir(d)) != NULL) {
      if (strcmp(dir->d_name, ".") == 0) {
        continue;
      }
      if (strcmp(dir->d_name, "..") == 0) {
        continue;
      }
      char *fileName = concat(dirName, dir->d_name);

      fileptr = fopen(fileName, "rb");  // Open the file in binary mode
      if (fileptr == NULL) {
        perror("Error opening file");
        return 1;
      }
      free(fileName);

      fseek(fileptr, 0, SEEK_END);          // Jump to the end of the file
      long filelen = ftell(fileptr);             // Get the current byte offset in the file
      rewind(fileptr);                      // Jump back to the beginning of the file

      buffer = (char *)malloc(filelen+1);
      fread(buffer, filelen, 1, fileptr); // Read in the entire file
      fclose(fileptr); // Close the file

      buffer[filelen] = '\0';
      printf("%s", buffer);
      free(buffer);
    }
    closedir(d);
  } else {
    printf("no dir\n");
  }
  return(0);
}


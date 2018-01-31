#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int charDist[26] = {0}; // character distribution
int totalCount = 0; // total letter count

void getCount(char *line) {
  
  for (int i = 0; i < strlen(line); i++) {
    int c = line[i];
    
    if (c >= 'a' && c <= 'z') { // for lowercase letters
      int d = c - 97;
      charDist[d]++;
      totalCount++;
    } // if
    else if (c >= 'A' && c <= 'Z') { // for uppercase letters
      int d = c - 65;
      charDist[d]++;
      totalCount++;
    } // else if
  } // for loop
  
} // getCount()

void printCount() {
  
  printf("\n--------------------------------\n");
  printf("Calculating letter counts ...\n\n");
  
  for (int i = 0; i < 26; i++) {
    char e = i + 65;
    double f = ((double) charDist[i] / totalCount) * 100;
    printf("%c : %d (%.2f%%)\n", e, charDist[i], f);
  } // for
  
  printf("\nTotal Letter Count: %d\n", totalCount);
  printf("--------------------------------\n\n");
  
} // printCount()

int main( int argc, char** argv ) {

  char *line = NULL;
  size_t lengthOfBuffer = 0;
  ssize_t numberOfCharactersRead;

  FILE * inputStream = fopen( "beyond-good-and-evil.txt", "r" );

  numberOfCharactersRead = getline(&line, &lengthOfBuffer, inputStream);
  
  if (numberOfCharactersRead == -1) {
      perror("getline");
  } // if
  else {
    getCount(line);
  } // else

  while(numberOfCharactersRead > 0) {
    
    numberOfCharactersRead = getline(&line, &lengthOfBuffer, inputStream);
    
    if (numberOfCharactersRead == -1) {
	perror("getline");
    } // if
    else {
      getCount(line);
    } // else
  } // while

  fclose(inputStream);

  free(line);

  printCount();

  return 0;

} // main( int, char** )

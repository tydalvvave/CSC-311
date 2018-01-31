#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WINNING_TICKETS 2110

typedef struct Ticket {
  int ticketID;
  int first;
  int second;
  int third;
  int fourth;
  int fifth;
  int powerball;
  int powerplay;
  char date[64];
} Ticket;

struct Ticket winningTickets[WINNING_TICKETS];

void createTicket(char *line)
{
  char date[10];
  char first[2];
  char second[2];
  char third[2];
  char fourth[2];
  char fifth[2];
  char powerball[2];
  char powerplay[2];
  
  sscanf(line, "%s" "%s" "%s" "%s" "%s" "%s" "%s" "%s",
        date, first, second, third, fourth, fifth, powerball, powerplay);
  
  printf("%s %s %s %s %s %s %s %s\n",
	date, first, second, third, fourth, fifth, powerball, powerplay);
}

int main(int argc, char** argv)
{
  printf("\nWinning Numbers (Iowa Powerball)");
  printf("\n--------------------------------\n");
  char *line = NULL;
  size_t lengthOfBuffer = 0;
  ssize_t numberOfCharactersRead;

  FILE * inputStream = fopen("iowa-powerball.txt", "r");
  
  numberOfCharactersRead = getline(&line, &lengthOfBuffer, inputStream);

  if (numberOfCharactersRead == -1)
  {
    perror("getline()");
  }
  else
  {
    createTicket(line);
  }

  while (numberOfCharactersRead > 0)
  {
    numberOfCharactersRead = getline(&line, &lengthOfBuffer, inputStream);

    if (numberOfCharactersRead == -1)
    {
      perror("getline()");
    }
    else
    {
      createTicket(line);
    }
  }
  printf("--------------------------------\n\n");
  
  fclose(inputStream);
  
  free(line);

  return 0;  
}

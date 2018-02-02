#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WINNING_TICKETS 2110
#define BALL_RANGE 69
#define POWERBALL_RANGE 29
#define POWERPLAY_RANGE 5

int totalBallCount = 0;
int totalPowerballCount = 0;
int totalPowerPlayCount = 0;

typedef struct Ticket {
  int ticketID;
  int first;
  int second;
  int third;
  int fourth;
  int fifth;
  int powerball;
  int powerplay;
  char drawDate[10];
} Ticket;

Ticket createTicket(char *line, Ticket ticket)
{
  char drawDate[10];
  int first;
  int second;
  int third;
  int fourth;
  int fifth;
  int powerball;
  int powerplay;
  
  sscanf(line, "%s" "%d" "%d" "%d" "%d" "%d" "%d" "%d",
        drawDate, &first, &second, &third, &fourth, &fifth, &powerball, &powerplay);
  
  strcpy(ticket.drawDate, drawDate);
  ticket.first = first;
  ticket.second = second;
  ticket.third = third;
  ticket.fourth = fourth;
  ticket.fifth = fifth;
  ticket.powerball = powerball;
  ticket.powerplay = powerplay;
  
  return ticket;
} // createTicket

void printTickets(struct Ticket *tickets, int numberOfTickets)
{
  for (int i = 0; i < numberOfTickets; i++)
  {
    printf("----------------------------------------------\n");
    printf("Ticket ID: %d\n", tickets[i].ticketID);
    printf("Draw Date: %s\n", tickets[i].drawDate);
    printf("Five Numbers: %d %d %d %d %d\n", tickets[i].first,
	   tickets[i].second, tickets[i].third,
	   tickets[i].fourth, tickets[i].fifth);
    printf("Powerball: %d\n", tickets[i].powerball);
    printf("Power Play: %d\n", tickets[i].powerplay);
    
  }
} // printTickets(struct Ticket *, int)

int *getBallCount(struct Ticket *tickets, int *count)
{  
  for (int i = 0; i < WINNING_TICKETS; i++)
  {
    for (int j = 1; j < 70; j++)
    {
      if (tickets[i].first == j ||
	  tickets[i].second == j ||
	  tickets[i].third == j ||
	  tickets[i].fourth == j ||
	  tickets[i].fifth == j)
      {
	count[j-1]++;
	totalBallCount++;
      }
    }
  }
  
  return count;
} // getBallCount(struct Ticket *, int *)

int *getPowerballCount(struct Ticket *tickets, int *count)
{
  for (int i = 0; i < WINNING_TICKETS; i++)
  {
    for (int j = 1; j < 30; j++)
    {
      if (tickets[i].powerball == j)
      {
	count[j-1]++;
	totalPowerballCount++;
      }
    }
  }

  return count;
} // getPowerballCount(struct Ticket *, int *)

int *getPowerPlayCount(struct Ticket *tickets, int *count)
{
  for (int i = 0; i < WINNING_TICKETS; i++)
  {
      if (tickets[i].powerplay == 2)
      {
	count[0]++;
	totalPowerPlayCount++;
      }
      else if (tickets[i].powerplay == 3)
      {
	count[1]++;
	totalPowerPlayCount++;
      }
      else if (tickets[i].powerplay == 4)
      {
	count[2]++;
	totalPowerPlayCount++;
      }
      else if (tickets[i].powerplay == 5)
      {
	count[3]++;
	totalPowerPlayCount++;
      }
      else if (tickets[i].powerplay == 10)
      {
	count[4]++;
	totalPowerPlayCount++;
      }
    }

  return count;
} // getPowerPlayCount(struct Ticket *, int *)

void printCount(int* numberCount, int whichBall)
{
  if (whichBall == BALL_RANGE)
  {
    printf("White Ball Frequency Chart\n");
    printf("--------------------------\n");

    for (int i = 0; i < whichBall; i++)
    {
      printf("%2d => %d\n", i + 1, numberCount[i]);
    }
  }
  else if (whichBall == POWERBALL_RANGE)
  {
    printf("Powerball Frequency Chart\n");
    printf("-------------------------\n");

    for (int i = 0; i < whichBall; i++)
    {
      printf("%2d => %d\n", i + 1, numberCount[i]);
    }
  }
  else if (whichBall == POWERPLAY_RANGE)
  {
    printf("Power Play Frequency Chart\n");
    printf("--------------------------\n");

    int pwrply = 0;

    for (int i = 0; i < whichBall; i++)
    {
      if (i == 0)      { pwrply = 2; }
      else if (i == 1) { pwrply = 3; }
      else if (i == 2) { pwrply = 4; }
      else if (i == 3) { pwrply = 5; }
      else if (i == 4) { pwrply = 10; }
      
      printf("%2d => %d\n", pwrply, numberCount[i]);
    }
  }
} // printCount(int*, int)


void pdf(int* numberCount, int whichBall)
{
  if (whichBall == BALL_RANGE)
  {
    printf("White Ball Probability Distrubution\n");
    printf("-----------------------------------\n");

    for (int i = 0; i < whichBall; i++)
    {
      printf("%2d => %.9f\n", i + 1,
	       (double) numberCount[i] / (double) totalBallCount);
    }
  }
  else if (whichBall == POWERBALL_RANGE)
  {
    printf("Powerball Probability Distrubution\n");
    printf("----------------------------------\n");

    for (int i = 0; i < whichBall; i++)
    {
      printf("%2d => %.9f\n", i + 1,
	     (double) numberCount[i] / (double) totalPowerballCount);
    }
  }
  else if (whichBall == POWERPLAY_RANGE)
  {    
    printf("Power Play Probability Distrubution\n");
    printf("-----------------------------------\n");

    int pwrply = 0;

    for (int i = 0; i < whichBall; i++)
    {
      if (i == 0)      { pwrply = 2; }
      else if (i == 1) { pwrply = 3; }
      else if (i == 2) { pwrply = 4; }
      else if (i == 3) { pwrply = 5; }
      else if (i == 4) { pwrply = 10; }

      printf("%2d => %.9f\n", pwrply,
	     (double) numberCount[i] / (double) totalPowerPlayCount);
    }
  }
} // pdf(int*, int)

void cdf(int* numberCount, int whichBall)
{
  if (whichBall == BALL_RANGE)
  {
    printf("White Ball Cumulative Distrubution\n");
    printf("----------------------------------\n");

    double cumulativeCount = numberCount[0];
    printf("%2d => %.9f\n", 1,
	       cumulativeCount / (double) totalBallCount);
    
    for (int i = 1; i < whichBall; i++)
    {
      cumulativeCount += numberCount[i];
      printf("%2d => %.9f\n", i + 1,
	       cumulativeCount / (double) totalBallCount);
    }
  }
  else if (whichBall == POWERBALL_RANGE)
  {
    printf("Powerball Cumulative Distrubution\n");
    printf("---------------------------------\n");

    double cumulativeCount = numberCount[0];
    printf("%2d => %.9f\n", 1,
	   cumulativeCount / (double) totalPowerballCount);
    
    for (int i = 1; i < whichBall; i++)
    {
      cumulativeCount += numberCount[i];
      printf("%2d => %.9f\n", i + 1,
	     cumulativeCount / (double) totalPowerballCount);
    }
  }
} // cdf()

int main(int argc, char** argv)
{
  struct Ticket *winningTickets;
  winningTickets = calloc(WINNING_TICKETS, sizeof(struct Ticket));
  if (!winningTickets)
  {
    perror("calloc");
    return -1;
  }

  int *ballCount;
  ballCount = calloc(BALL_RANGE, sizeof(int));
  if (!ballCount)
  {
    perror("calloc");
    return -1;
  }

  int *powerballCount;
  powerballCount = calloc(POWERBALL_RANGE, sizeof(int));
  if (!powerballCount)
  {
    perror("calloc");
    return -1;
  }

  int *powerPlayCount;
  powerPlayCount = calloc(POWERPLAY_RANGE, sizeof(int));
  if (!powerPlayCount)
  {
    perror("calloc");
    return -1;
  }

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
    winningTickets[0] = createTicket(line, winningTickets[0]);
    winningTickets[0].ticketID = 0;
  }

  int i = 1;
  while (numberOfCharactersRead > 0)
  {
    numberOfCharactersRead = getline(&line, &lengthOfBuffer, inputStream);

    if (numberOfCharactersRead == -1)
    {
      perror("getline()");
    }
    else
    {
      winningTickets[i] = createTicket(line, winningTickets[i]);
      winningTickets[i].ticketID = i;
      i++;
    }
  }
  
  fclose(inputStream);

  //printTickets(winningTickets, WINNING_TICKETS);

  printf("\n");
  printCount(getBallCount(winningTickets, ballCount), BALL_RANGE);
  printf("\n");
  printCount(getPowerballCount(winningTickets, powerballCount), POWERBALL_RANGE);
  printf("\n");
  printCount(getPowerPlayCount(winningTickets, powerPlayCount), POWERPLAY_RANGE);

  //printf("Total Ball Count: %d\n", totalBallCount);
  //printf("Total Powerball Count: %d\n", totalPowerballCount);

  printf("\n");
  pdf(ballCount, BALL_RANGE);
  printf("\n");
  pdf(powerballCount, POWERBALL_RANGE);
  printf("\n");
  pdf(powerPlayCount, POWERPLAY_RANGE);

  printf("\n");
  cdf(ballCount, BALL_RANGE);
  printf("\n");
  cdf(powerballCount, POWERBALL_RANGE);  

  free(line);
  free(winningTickets);
  free(ballCount);
  free(powerballCount);
  free(powerPlayCount);
  
  return 0;
  
} // main(int, char**)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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

int* getBallCount(struct Ticket *tickets, int *count)
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

int* getPowerballCount(struct Ticket *tickets, int *count)
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

double* pdf(int* numberCount, int whichBall, double* probDist)
{
  if (whichBall == BALL_RANGE)
  {
    for (int i = 0; i < whichBall; i++)
    {
      probDist[i] = (double) numberCount[i] / (double) totalBallCount;
    }
  }
  else if (whichBall == POWERBALL_RANGE)
  {
    for (int i = 0; i < whichBall; i++)
    {
      probDist[i] = (double) numberCount[i] / (double) totalPowerballCount;
    }
  }

  return probDist;
} // pdf(int*, int)

double* cdf(int* numberCount, int whichBall, double* probDist)
{
  if (whichBall == BALL_RANGE)
  {
    double cumulativeCount = numberCount[0];
    probDist[0] = cumulativeCount / (double) totalBallCount;

    for (int i = 1; i < whichBall; i++)
    {
      cumulativeCount += numberCount[i];
      probDist[i] = cumulativeCount / (double) totalBallCount;
    }
  }
  else if (whichBall == POWERBALL_RANGE)
  {
    double cumulativeCount = numberCount[0];
    probDist[0] = cumulativeCount / (double) totalPowerballCount;

    for (int i = 1; i < whichBall; i++)
    {
      cumulativeCount += numberCount[i];
      probDist[i] = cumulativeCount / (double) totalPowerballCount;
    }
  }

  return probDist;
} // cdf(int*, int)

void printDist(double* probDist, int whichBall)
{
    if (whichBall == BALL_RANGE)
    {
      for (int i = 0; i < whichBall; i++)
      {
        printf("%2d => %.9f (%.2f%%)\n", i + 1, probDist[i], probDist[i]*100);
      }
    }
    else if (whichBall == POWERBALL_RANGE)
    {
      for (int i = 0; i < whichBall; i++)
      {
        printf("%2d => %.9f (%.2f%%)\n", i + 1, probDist[i], probDist[i]*100);
      }
    }
} // printDist()

double getRand()
{ return (rand() / (double) RAND_MAX);
} // getRand()

int* generateTicket(double* probDist, int* genBallPick)
{
  for (int clear = 0; clear < 5; clear++)
  {
    genBallPick[clear] = 0;
  }

  int i = 0;
  LOOP:while (i < 5)
  {
    double genRand = getRand(); // 0.52

    int j = 1;
    while (j < BALL_RANGE)
    {
      if (probDist[j-1] > genRand)
      {
        break;
      }
      j++;
    }

    if (i == 0)
    {
      genBallPick[0] = j;
    }
    else
    {
      for (int k = 0; k < i; k++)
      {
        if (genBallPick[k+1] == genBallPick[k])
        {
          goto LOOP;
        }
      }
    }
    genBallPick[i] = j;
    i++;
  }

  int a, b, c;
  for (a = 1; a < 5; a++)
  {
    c = genBallPick[a];
    b = a - 1;

    while (b >= 0 && genBallPick[b] > c)
    {
      genBallPick[b+1] = genBallPick[b];
      b = b - 1;
    }
    genBallPick[b+1] = c;
  }

  return genBallPick;
} // generateTicket()

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

  double *ballDist;
  ballDist = calloc(BALL_RANGE, sizeof(double));
  if (!ballDist)
  {
    perror("calloc");
    return -1;
  }

  double *powerballDist;
  powerballDist = calloc(POWERBALL_RANGE, sizeof(double));
  if (!powerballDist)
  {
    perror("calloc");
    return -1;
  }

  int* genBallPick;
  genBallPick = calloc(5, sizeof(int));
  if (!genBallPick)
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

  int h = 1;
  while (numberOfCharactersRead > 0)
  {
    numberOfCharactersRead = getline(&line, &lengthOfBuffer, inputStream);

    if (numberOfCharactersRead == -1)
    {
      perror("getline()");
    }
    else
    {
      winningTickets[h] = createTicket(line, winningTickets[h]);
      winningTickets[h].ticketID = h;
      h++;
    }
  }

  fclose(inputStream);

  srand(time(NULL));

  //printTickets(winningTickets, WINNING_TICKETS);
  //printf("\n");

  getBallCount(winningTickets, ballCount);
  getPowerballCount(winningTickets, powerballCount);

  /*
  printf("\nWHITE BALL PROBABILITY DISTRIBUTION");
  printf("\n-----------------------------------\n");
  printDist(pdf(ballCount, BALL_RANGE, ballDist), BALL_RANGE);
  printf("\nPOWERBALL PROBABILITY DISTRIBUTION");
  printf("\n----------------------------------\n");
  printDist(pdf(powerballCount, POWERBALL_RANGE, powerballDist), POWERBALL_RANGE);

  printf("\nWHITE BALL CUMULATIVE DISTRIBUTION");
  printf("\n----------------------------------\n");
  printDist(cdf(ballCount, BALL_RANGE, ballDist), BALL_RANGE);
  printf("\nPOWERBALL CUMULATIVE DISTRIBUTION");
  printf("\n---------------------------------\n");
  printDist(cdf(powerballCount, POWERBALL_RANGE, powerballDist), POWERBALL_RANGE);
  printf("\n");
  */

  pdf(ballCount, BALL_RANGE, ballDist);
  pdf(powerballCount, POWERBALL_RANGE, powerballDist);
  cdf(ballCount, BALL_RANGE, ballDist);
  cdf(powerballCount, POWERBALL_RANGE, powerballDist);

  printf("\nGENERATED TICKET(S)\n");
  printf("-------------------\n");
  for (int i = 0; i < 20; i++)
  {
    generateTicket(ballDist, genBallPick);

    for (int i = 0; i < 5; i++)
    {
      printf("%3d ", genBallPick[i]);
    }
    printf("\n");
  }
  printf("\n");

  free(line);
  free(winningTickets);
  free(ballCount);
  free(powerballCount);
  free(ballDist);
  free(powerballDist);
  free(genBallPick);

  return 0;

} // main(int, char**)

/** TO DO

    - Allocate memory for probability and cumulative distributions
      in order to use the data
    - Set seed for random number generator
    - Generate and display new lottery tickets

 */

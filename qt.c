// Abstract: qt is a "quick time" console program that converts local time
//           to a verbal string.  This utility was inspired by a 512 byte 
//           DOS executable program written in assembler 
// 2020 Jun 25 jhm original creation

#include <stdio.h>
#include <time.h>

char * hmToText(int h, int m) {
  static char szTime[1024];

  char * hour[] = {"twelve", "one", "two", "three", "four", "five", 
                   "six", "seven", "eight", "nine", "ten", "eleven"};

  char * position[] = {"", "five after ", "ten after ", "quarter after ", 
                       "twenty after ", "twenty five after ", "half past ", 
                       "twenty five till ", "twenty till ", "quarter till ",
                       "ten till ", "five till ", ""}; 

  snprintf(szTime, sizeof(szTime), 
    "it's %s%s%s%s%s", 
    (m % 5) ? "about " : "",   // "about" on min 1, 2, 3 & 4 of 5 min intervals
    (m==0) ? "exactly " : "",  // "exactly" on the hour
    position[(m+2) / 5],       // min 3 & 4 of 5 min intervals -> index + 1
    hour[(h + ((m>32) ? 1 : 0)) % 12],   // min >32 indexes to next hour
    (*position[(m+2)/5] == '\0') ? " o'clock" : ""); // "o'clock" close to the hour

  return szTime;
} 

int main() {
  time_t sec = time(NULL);
  struct tm * now = localtime(&sec);
  printf("\n%s\n", hmToText(now->tm_hour, now->tm_min)); 
}

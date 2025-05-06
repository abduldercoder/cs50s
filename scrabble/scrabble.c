#include <stdio.h>
#include <cs50.h>
#include <ctype.h>



int get_score(char c)
{
   if(isalpha(c))
   {
    int UpperC = toupper(c);
       int letterScore[26] =
   {
    1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 1
   };
        return letterScore[UpperC - 'A'];
   }

    return 0;
}

int calculate_score(const char *word)
{
    int sum = 0;
    for (int i = 0; word[i] != '\0'; i++)
    {
        if (isalpha(word[i]))  // Nur alphabetische Zeichen zählen
        {
            sum += get_score(word[i]);
        }
    }
    return sum;
}



int main (void)
{
  char word1[100];
  char word2[100];

  printf("Player 1 : ");
  scanf("%99s", word1);

   printf("Player 2 : ");
  scanf("%99s", word2);

int score1 = calculate_score(word1);
int score2 = calculate_score(word2);

    if(score1 > score2)
    {
        printf("Player 1 wins¡\n");
    }
    else if( score2 > score1)
    {
        printf("Player 2 wins! \n");
    }
    else
    {
        printf("Tie \n");
    }

}

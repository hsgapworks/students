#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MIN_VALUE 1
#define MAX_VALUE 1000

static int read_int(const char *prompt, int *value)
{
    printf("%s", prompt);
    if (scanf("%d", value) != 1) {
        printf("Input error\n");
        return 0;
    }
    return 1;
}

static void mode_program_guesses(void)
{
    srand((unsigned int)time(NULL));
    int secret = MIN_VALUE + rand() % (MAX_VALUE - MIN_VALUE + 1);
    int guess = 0;
    int attempts = 0;

    printf("Program picked a number from %d to %d\n", MIN_VALUE, MAX_VALUE);
    for (;;) {
        if (!read_int("Your guess: ", &guess))
            return;
        if (guess < MIN_VALUE || guess > MAX_VALUE) {
            printf("Number out of range\n");
            continue;
        }
        attempts++;
        if (guess < secret) {
            printf("The number is greater\n");
        } else if (guess > secret) {
            printf("The number is smaller\n");
        } else {
            printf("Correct! Attempts: %d\n", attempts);
            return;
        }
    }
}

static void mode_user_guesses(void)
{
    int secret = 0;
    int low = MIN_VALUE;
    int high = MAX_VALUE;
    int attempts = 0;

    if (!read_int("Think of a number from 1 to 1000: ", &secret))
        return;
    if (secret < MIN_VALUE || secret > MAX_VALUE) {
        printf("Number out of range\n");
        return;
    }

    printf("Answer with >, < or =\n");
    while (low <= high) {
        int mid = low + (high - low) / 2;
        char answer = ' ';

        printf("%d? ", mid);
        if (scanf(" %c", &answer) != 1)
            return;
        attempts++;

        if (answer == '=') {
            printf("Correct! Attempts: %d\n", attempts);
            return;
        }
        if (answer == '>') {
            low = mid + 1;
        } else if (answer == '<') {
            high = mid - 1;
        } else {
            printf("Invalid answer, try again\n");
            attempts--;
        }
    }
    printf("Answers are inconsistent, number not found\n");
}

int main(void)
{
    int choice = 0;

    printf("1 - program picks the number\n");
    printf("2 - you pick the number\n");
    if (!read_int("Choose mode: ", &choice))
        return 1;

    if (choice == 1)
        mode_program_guesses();
    else if (choice == 2)
        mode_user_guesses();
    else
        printf("Unknown mode\n");

    return 0;
}

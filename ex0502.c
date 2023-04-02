#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MIN_STUDENT_NUMBER 1
#define MAX_STUDENT_NUMBER 9
#define MIN_SCORE -1
#define MAX_SCORE 100
#define PASS_SCORE 60
#define MAX_INPUT_LENGTH 100

// Macro for a loop that iterates from 0 to n-1
#define FOR(i, n) for (int i = 0; i < n; i++)
// Macro for checking input functions and returning 1 if invalid
#define CHECK_INPUT(func) \
    if (!func)            \
        return 0;
// Macro for counting number of items in an array
#define COUNT int count = 0;
// Macro for returns the minimum value between A and B.
#define CHECK_MIN(A, B) A < B ? A : B
// Macro for returns the maximum value between A and B.
#define CHECK_MAX(A, B) A > B ? A : B

// Struct to hold various score information
struct scoreInfoStructure
{
    int students;      // Number of students
    int passed;        // Number of students who passed (score >= 60)
    int percentPassed; // Percentage of students who passed
    float avg;         // Average score of all evaluated students
    int max;           // Maximum score of all evaluated students
    int min;           // Minimum score of all evaluated students
};
// Structure that holds the result of checking whether input is an integer or not.
struct checkInputIsIntStructure
{
    int value;  // The integer value of the input (if input is an integer)
    bool isInt; // A flag indicating whether the input is an integer or not
};
// Function that checks if the input from user is an integer.
// Returns a struct containing the result of the check.
struct checkInputIsIntStructure checkInputIsInt()
{
    struct checkInputIsIntStructure checkInput;
    checkInput.value = 0;    // Set the initial value to zero
    checkInput.isInt = true; // Set the initial flag value to true
    char input[MAX_INPUT_LENGTH];
    char c;
    COUNT;
    // Loop through the input character by character
    while ((c = getchar()) != EOF)
    {
        if (!isspace(c))
            input[count++] = c; // If the character is not whitespace, add it to the input array
        if (count > 0 && isspace(c))
            break; // If we have read at least one non-whitespace character and we encounter whitespace, break the loop
    }
    input[count] = '\0';  // Add null terminator to the end of the input string
    FOR(i, strlen(input)) // Loop through the input string
    {
        if (input[i] == '-' && i == 0)
            continue;                         // If the first character is a minus sign, skip it (negative numbers are allowed)
        if (input[i] < '0' || input[i] > '9') // If a character is not a digit
        {
            checkInput.isInt = false; // Set the flag to false
            return checkInput;        // Return the result
        }
    }
    checkInput.value = (int)atoi(input); // Convert the input string to an integer and store it in the struct
    return checkInput;                   // Return the result
}
// Function to input number of students, returns false if input is invalid
bool inputNumberOfStudent(int *n)
{
    struct checkInputIsIntStructure checkInput;
    printf("n = ");
    checkInput = checkInputIsInt();
    *n = checkInput.value;
    if (*n < MIN_STUDENT_NUMBER || *n > MAX_STUDENT_NUMBER)
    {
        checkInput.isInt ? \
        printf("ERROR: invalid number of students (%d)\n", *n) : \
        printf("ERROR: invalid number of students (%s)\n", "NOT INTEGER");
        return false;
    }
    return true;
}
// Function to input scores into an array, returns false if invalid scores are inputted
bool inputScoresArr(int scoresArray[], int size)
{
    struct checkInputIsIntStructure checkInput;
    bool isErrorScoresInput = false;
    bool isNotInteger = false;
    int errorScores[size];
    COUNT;
    printf("scores = ");
    FOR(i, size)
    {
        checkInput = checkInputIsInt();
        if (!checkInput.isInt)
        {
            isNotInteger = true;
            continue;
        }
        scoresArray[i] = checkInput.value;
        if (scoresArray[i] < MIN_SCORE || scoresArray[i] > MAX_SCORE)
        {
            isErrorScoresInput = true;
            errorScores[count++] = scoresArray[i];
        }
    }
    if (isErrorScoresInput || isNotInteger)
    {
        printf("ERROR: invalid scores (");
        if (isNotInteger)
        {
            printf("%s", "NOT INTEGER)\n");
            return false;
        }
        FOR(i, count)
        {
            printf("%d", errorScores[i]);
            if (i == count - 1)
                continue;
            printf(", ");
        }
        printf(")\n");
        return false;
    }
    return true;
}
// Function to check if a score has been evaluated (i.e. not equal to -1)
bool checkNotEvaluated(int score)
{
    return score != MIN_SCORE;
}
// Function to create a sub-array of evaluated scores from the main scores array
void createSubScoreArrayEvaluated(int subScoreArray[], int scoresArray[], int sizeScoresArray, int *subScoresArraySize)
{
    COUNT;
    FOR(i, sizeScoresArray)
    {
        if (checkNotEvaluated(scoresArray[i]))
            subScoreArray[count++] = scoresArray[i];
    }
    *subScoresArraySize = count;
}
// Function to count the number of students who passed (score >= 60)
int checkPassedStudent(int scores[], int size)
{
    COUNT;
    FOR(i, size)
    {
        if (scores[i] >= PASS_SCORE)
            count++;
    }
    return count;
}
// Function to calculate the average score of all evaluated students
float average(int scoresArray[], int size)
{
    if (size == 0)
        return 0;
    int sum = 0;
    FOR(i, size)
    sum += scoresArray[i];
    return (float)sum / size;
}
// Function to find the maximum score of all evaluated students
int max(int scoresArray[], int size)
{
    if (size == 0)
        return 0;
    int maxScore = scoresArray[0];
    FOR(i, size - 1)
    maxScore = CHECK_MAX(maxScore, scoresArray[i + 1]);
    return maxScore;
}
// Function to find the minimum score of all evaluated students
int min(int scoresArray[], int size)
{
    if (size == 0)
        return 0;
    int minScore = scoresArray[0];
    FOR(i, size - 1)
    minScore = CHECK_MIN(minScore, scoresArray[i + 1]);
    return minScore;
}
// This function prints out the score information of the students
void printfScoreInfo(struct scoreInfoStructure scoreInfo)
{
    printf("======= score info =======\n");
    printf(" #students = %d\n", scoreInfo.students);
    printf(" #passed = %d (%d%%)\n\n", scoreInfo.passed, scoreInfo.percentPassed);
    printf(" ave = %.1f\n", scoreInfo.avg);
    printf(" max = %d\n", scoreInfo.max);
    printf(" min = %d\n", scoreInfo.min);
    printf("==========================\n");
}

int main(void)
{
    int numberOfStudent;
    // Prompt user to enter the number of students and check the input validity.
    CHECK_INPUT(inputNumberOfStudent(&numberOfStudent));
    // Declare an array to store the scores of all students, and prompt user to enter and validate each score.
    int scoresArray[numberOfStudent];
    CHECK_INPUT(inputScoresArr(scoresArray, numberOfStudent));
    // Create a new array to store the evaluated sub-scores of all students and get the size of the sub-scores array.
    int subScoresArrayEvaluated[numberOfStudent];
    int subScoresArraySize = numberOfStudent;
    createSubScoreArrayEvaluated(subScoresArrayEvaluated, scoresArray, numberOfStudent, &subScoresArraySize);
    // Create a structure to store the score information of the students, and assign the values to the corresponding fields.
    struct scoreInfoStructure scoreInfo;
    scoreInfo.students = numberOfStudent;
    scoreInfo.passed = checkPassedStudent(scoresArray, numberOfStudent);
    scoreInfo.percentPassed = div(scoreInfo.passed * 100, numberOfStudent).quot;
    scoreInfo.avg = average(subScoresArrayEvaluated, subScoresArraySize);
    scoreInfo.max = max(subScoresArrayEvaluated, subScoresArraySize);
    scoreInfo.min = min(subScoresArrayEvaluated, subScoresArraySize);
    // Print out the score information of the students using the printfScoreInfo function.
    printfScoreInfo(scoreInfo);

    return 0;
}
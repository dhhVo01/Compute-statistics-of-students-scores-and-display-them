#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

// Macro for a loop that iterates from 0 to n-1
#define FOR(i, n) for (int i = 0; i < n; i++)
// Macro for checking input functions and returning 1 if invalid
#define CHECK_INPUT(func) if (!func) return 1;
// Macro for counting number of items in an array
#define COUNT int count = 0;

// Struct to hold various score information
struct scoreInfoStructure
{
    int students;           // Number of students
    int passed;             // Number of students who passed (score >= 60)
    int percentPassed;      // Percentage of students who passed
    float avg;              // Average score of all evaluated students
    int max;                // Maximum score of all evaluated students
    int min;                // Minimum score of all evaluated students
};
// Function to input number of students, returns false if input is invalid
bool inputNumberOfStudent(int* n)
{
    printf("n = ");
    scanf("%d", n);
    if ( *n < 1 || *n > 9 ){
        printf("ERROR: invalid number of students (%d)\n", *n);
        return false;
    }
    return true;
}
// Function to input scores into an array, returns false if invalid scores are inputted
bool inputScoresArr(int scoresArray[], int size){
    bool isErrorScoresInput = false;
    int errorScores[size];
    COUNT;
    printf("scores = ");
    FOR(i, size)
    {
        scanf("%d", &scoresArray[i]);
        if (scoresArray[i] < -1 || scoresArray[i] > 100)
        {
            isErrorScoresInput = true;
            errorScores[count] = scoresArray[i];
            count++;
        }
    }
    if (isErrorScoresInput)
    {
        printf("ERROR: invalid scores (");
        FOR(i, count)
        {
            printf("%d", errorScores[i]);
            if (i == count - 1) continue;
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
    if (score == -1) return false;
    return true;
}
// Function to create a sub-array of evaluated scores from the main scores array
void createSubScoreArrayEvaluated(int subScoreArray[], int scoresArray[], int sizeScoresArray, int *subScoresArraySize)
{
    COUNT;
    FOR(i, sizeScoresArray)
    {
        if(checkNotEvaluated(scoresArray[i]))
        {
            subScoreArray[count] = scoresArray[i];
            count++;
        }
    }
    *subScoresArraySize = count;
}
// Function to count the number of students who passed (score >= 60)
int checkPassedStudent(int scores[], int size)
{
    COUNT;
    FOR(i, size)
    {
        if (scores[i] >= 60 )
            count++;
    }
    return count;
}
// Function to calculate the average score of all evaluated students
float average(int scoresArray[], int size)
{
    if (size == 0) return 0;
    int sum = 0;
    FOR(i, size)
        sum += scoresArray[i];
    return (float)sum/size;
}
int max(int scoresArray[], int size)
{
    if (size == 0) return 0;
    int maxScore = scoresArray[0];
    FOR(i, size - 1)
    {
        if (scoresArray[i+1] > maxScore)
            maxScore = scoresArray[i+1];
    }
    return maxScore;

}
// Function to find the minimum score of all evaluated students
int min(int scoresArray[], int size)
{
    if (size == 0) return 0;
    int minScore = scoresArray[0];
    FOR(i, size - 1)
    {
        if (scoresArray[i+1] < minScore)
            minScore = scoresArray[i+1];
    }
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

int main(void){

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
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define SET_NAME_CHARACTER_LENGTH 4
#define MAX_NUM_IN_SET 128
#define SET_NUM 6
#define DECIMAL 10
#define BYTES_NUM 16
enum checker
{
    CommandChecker,
    SetOne,
    CommaSetOne,
    SetTwo,
    CommaSetTwo,
    ResultSet,
    Number,
    Comma,
    MinusOne,
    Stop
};
typedef struct set set;

int validLine(char *);
/*
checks if the command entered is valid if not prints the error in input
*/

int validCommandName(char *);
/*
checks if the command entered is valid name
*/

int validSetName(char *);
/*
checks if the set name entered is valid name
*/
int validNumber(char *);
/*
checks if the number entered in read set is valid (in rage 0-128)
*/
void number_include(set *s, int index);
/*
adding a number to set
*/
int number_in_set(set *, int);
/*
checks if a number is in set
*/
set *create_set(void);
/*
create set
*/
void empty_set(set *seet);
/*
empty set from input(free memory)
*/
void read_set(set *, int *, int);
/*
read set from input
*/
void print_set(set *s);
/*
prints all the number in set
*/
void union_set(set *set1, set *set2, set *result);
/*
gets two sets and unit them and put result into third set
*/
void intersect_set(set *set1, set *set2, set *result);
/*
gets two sets and intersect them and put result into third set
*/
void sub_set(set *set1, set *set2, set *result);
/*
gets two sets and substract them and put result into third set
*/
void symdiff_set(set *set1, set *set2, set *result);
/*
gets two sets and does symetric difference on them and put result into third set
*/
void stop(void);
/*
stop the execution of the program
*/

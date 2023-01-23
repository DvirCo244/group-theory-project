#include "set.h"
struct set
{
    char bit_array[16];
};

void read_set(set *s, int *num, int number)
{
    int i;
    for (i = 0; i < number && *num != -1; i++)
    {
        number_include(s, *num);
        ++num;
    }
}

void print_set(set *s)
{
    int set_empty = 1;
    int i;
    int counter;
    for (i = 0; i < 128; i++)
        if (number_in_set(s, i))
        {
            set_empty = 0;
            ++counter;

            if (counter % 16 == 0)
            {
                printf("\n\t");
            }
            printf("%d ", i);
        }
    if (set_empty == 1)
        printf("this set is empty.");
}

void stop(void)
{
    exit(EXIT_SUCCESS);
}
set *create_set(void)
{
    set *seet = (set *)calloc(16,8);
    if (seet == NULL)
        return (NULL);
    return (seet);
}
void empty_set(set *seet)
{
    free(seet);
}

void number_include(set *s, int index)
{
    s->bit_array[index / 8] |= 1 << index % 8;
}

int number_in_set(set *s, int index)
{
    return !!(s->bit_array[index / 8] & (1 << index % 8));
}

void sub_set(set *set1, set *set2, set *result)
{
    set *temp;
    int i;
    temp = create_set();
    for (i = 0; i < 128; i++)
    {
        if (number_in_set(set1, i) && !number_in_set(set2, i))
            number_include(temp, i);
    }

    memcpy(result, temp, 128);
    empty_set(temp);
}
void intersect_set(set *set1, set *set2, set *result)
{
    set *temp;
    int i;
    temp = create_set();
    for (i = 0; i < 128; i++)
    {
        if (number_in_set(set1, i) && number_in_set(set2, i))
        {
            number_include(temp, i);
        }
    }
    memcpy(result, temp, 128);
    empty_set(temp);
}
void union_set(set *set1, set *set2, set *result)
{
    set *temp;
    int i;
    temp = create_set();
    for (i = 0; i < 128; i++)
    {
        if (number_in_set(set1, i) || number_in_set(set2, i))
            number_include(temp, i);
    }

    memcpy(result, temp, 128);
    empty_set(temp);
}

void symdiff_set(set *set1, set *set2, set *result)
{
    set *temp;
    int i;
    temp = create_set();
    for (i = 0; i < 128; i++)
    {
        if (!(number_in_set(set1, i) && number_in_set(set2, i)))
            number_include(temp, i);
    }
    memcpy(result, temp, 128);
    empty_set(temp);
}
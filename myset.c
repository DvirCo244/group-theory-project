#include "set.h"
//all set names
static char *sets[] = {"SETA", "SETB", "SETC", "SETD", "SETE", "SETF"};
//all commands name
static char *commands[] = {"read_set", "print_set", "union_set", "intersect_set", "sub_set", "stop", "symdiff_set"};

int main()
{
    char c;
    int size, command_number, index;
    char *string, *input;
    set *set_one, *set_two, *set_three;
    set *sets[SET_NUM];
    int num_array[MAX_NUM_IN_SET];

//instructions to user
    printf("welcome to the group theory program!\n");
    printf("here you could create groups and do functions on them!\n");
    printf("lets go over everything you need to know before using :D \n");
    printf("you can create 6 different group! the group names are SETA,SETB,SETC,SETD,SETE,SETF\n");
    printf("the function read_set gets input into the group,\n you need to use in this format:read_set(thegroupname),thenumberyouwant,....,-1\n");
    printf("the function print set prints the group you've entered\n you need to use in this format: print_set (thegroupname)\n");
    printf("the funcion union_set gets three groups and unit them into third group\n you need to use in this format: union_set (group1name),(group2name),(group3name)\n");
    printf("the function intersect_set gets three groups and put in the third group all the elements that are both in first and second group and puting in group three the result\n you need to use in this format: intersect_set (group1name),(group2name),(group3name)\n");
    printf("the function sub_set gets three groups and substract group one from group two and puting in group three the result \n you need to use this format: sub_set (group1name),(group2name),(group3name)\n");
    printf("the function symdiff_set gets three groups and doing symatric differenece on group one and two and puting in group three the result\n you need to use in this format:symdiff_set (group1name),(group2name),(group3name)\n");
    printf("the function stop stops all the program and the execution is done!\n");
    printf("well this is everything you need to know about the program enjoy :)\n");
    printf("\n\n~enter input: ");

    for (index = 0; index < SET_NUM; index++) // resets all the groups
    {
        sets[index] = create_set();
    }
    while (1) //getting the input
    {
        input = NULL;
        free(input);
        size = 0;
        while (((c = getchar()) != '\n') && (c != EOF)) //dynamicly getting input
        {
            input = (char *)realloc(input, size * sizeof(char) + sizeof(char));
            input[size++] = c;
        }
        input[size] = '\0';
        string = input;
        printf("your input: %s\n", string);
        while (isspace(*string))
        {
            ++string;
        }
        if (validLine(string)) //checking if the input is in correct format
        {
            command_number = validCommandName(string);
            string += strlen(commands[command_number]);
            while (isspace(*string))
                ++string;
            set_one = sets[validSetName(string)];
            string += SET_NAME_CHARACTER_LENGTH;

            switch (command_number) //if the input is in correct format deciding what to do 
            {
            case 0: //checking if the command is read_set
                index = 0;
                while (*string != '\0')
                {
                    while (isspace(*string) || *string == ',')
                        ++string;
                    num_array[index] = strtol(string, &string, DECIMAL);
                    index++;
                }
                memset(set_one, 0, BYTES_NUM);
                read_set(set_one, num_array, index);
                printf("finished reading");
                break;

            case 1: //checking if the command is print_set
                printf("The set: ");
                print_set(set_one);
                printf("\n");
                break;
            //checking if the command is union,intersect,sub,symdiff
            case 2:
            case 3:
            case 4:
            case 6:
                while (isspace(*string) || *string == ',')
                    ++string;
                set_two = sets[validSetName(string)];
                string += SET_NAME_CHARACTER_LENGTH;
                while (isspace(*string) || *string == ',')
                    ++string;
                set_three = sets[validSetName(string)];
                if (command_number == 2)
                    union_set(set_one, set_two, set_three);
                else if (command_number == 3)
                    intersect_set(set_one, set_two, set_three);
                else if(command_number == 4)
                    sub_set(set_one, set_two, set_three);
                    else 
                    symdiff_set(set_one,set_two,set_three);
                printf("Done!\n");
                break;
            //checking if the command is stop
            case 5:
                for (index = 0; index < SET_NUM; index++)
                {
                    empty_set(sets[index]);
                }
                printf("finished see you again\n");
                stop();
                break;
            }
        }
        printf("\n\n~enter input: ");
    }
}

int validLine(char *string)
{
    enum checker part;
    int command_number;
    int num;
    part = CommandChecker;
    command_number = 0;

    while (1)
    {
        if (isspace(*string))
        {
            ++string;
            continue;
        }
        switch (part)
        {

        case CommandChecker:
            command_number = validCommandName(string);
            if (command_number > 6)
            {
                printf("Undefined command name\n");
                return (0);
            }
            else if (command_number == 5)
            {
                string += strlen(commands[command_number]);
                part = Stop;
            }
            else
            {
                string += strlen(commands[command_number]);
                part = SetOne;
            }
            continue;

        case SetOne:
            if (*string == '\0' || *string == '\n')
            {
                printf("Missing parameter\n");
                return (0);
            }
            if (*string == ',')
            {
                printf("Illegal comma\n");
                return (0);
            }
            else
            {
                if (validSetName(string) != -1)
                {
                    string += SET_NAME_CHARACTER_LENGTH;
                    if (command_number == 1)
                    {

                        while (*string != '\0')
                        {

                            if (isspace(*string))
                            {
                                ++string;
                                continue;
                            }
                            else
                            {
                                printf("Extraneous text after end of command\n");
                                return (0);
                            }
                        }
                        return (1);
                    }

                    else if (command_number == 0)
                    {
                        part = Comma;
                    }
                    else
                    {
                        part = CommaSetOne;
                    }
                }

                else
                {
                    printf("Undefined set name\n");
                    return (0);
                }
            }
            continue;

        case CommaSetOne:

            if (*string != ',')
            {

                printf("Missing comma\n");
                return (0);
            }

            else
            {
                if (command_number == 0)
                {
                    part = Number;
                }
                else
                {
                    part = SetTwo;
                }
            }
            ++string;
            continue;

        case SetTwo:

            if (*string == ',')
            {
                printf("Multiple consecutive comma\n");
                return (0);
            }
            if (*string == '\0' || *string == '\n')
            {
                printf("Missing parameter\n");
                return (0);
            }

            if (validSetName(string) == -1)
            {
                printf("Undefined set name\n");
                return (0);
            }
            string += SET_NAME_CHARACTER_LENGTH;
            part = CommaSetTwo;
            continue;

        case CommaSetTwo:
            if (*string != ',')
            {
                printf("Missing comma\n");
                return (0);
            }
            part = ResultSet;
            ++string;
            continue;

        case ResultSet:
            if (*string == '\0')
            {
                printf("Missing parameter\n");
                return (0);
            }
            if (*string == ',')
            {
                printf("Multiple consecutive comma\n");
                return (0);
            }
            if (validSetName(string) == -1)
            {
                printf("Undefined set name\n");
                return (0);
            }
            string += SET_NAME_CHARACTER_LENGTH;
            while (*string != '\0' && *string != '\n')
            {
                if (isspace(*string))
                {
                    ++string;
                    continue;
                }
                else
                {
                    printf("Extraneous text after end of command\n");
                    return (0);
                }
            }
            return (1);
            break;

        case Number:
            if (*string == '\0')
            {
                printf("List of set members is not terminated correctly\n");
                return (0);
            }
            if (*string == ',')
            {
                printf("Multiple consecutive comma\n");
                return (0);
            }
            num = validNumber(string);
            if (num == 0)
            {
                return (0);
            }
            if (num >= 1)
            {
                string += num;
                part = Comma;
            }
            else if (num == -1)
            {
                string += 2;
                part = MinusOne;
            }
            continue;

        case Comma:
            if (*string == '\0')
            {
                printf("List of set members is not terminated correctly\n");
                return (0);
            }
            if (*string != ',')
            {
                if (*string == '.')
                {
                    ++string;
                    if (isdigit(*string))
                    {
                        printf("Invalid set member - not an integer\n");
                        return (0);
                    }
                }
                printf("came here\n");
                printf("Missing comma\n");
                return (0);
            }
            ++string;
            part = Number;
            continue;

        case MinusOne:
            if (*string != '\0')
            {
                printf("Extraneous text after end of command\n");
                return (0);
            }
            else
            {
                return (1);
            }
            break;

        case Stop:

            if (*string != '\0')
            {
                printf("Extraneous text after end of command\n");
                return (0);
            }

            return (1);
            break;

        default:
            printf("default input");
            return (0);
            break;
        }
        return (1);
    }
    return 0;
}

int validCommandName(char *string)
{
    int i;
    for (i = 0; i <= SET_NUM; i++)
    {
        if (memcmp(string, commands[i], strlen(commands[i])) == 0)
            return (i);
    }
    return (i);
}

int validSetName(char *string)
{
    int i;

    for (i = 0; i <= SET_NUM; i++)
    {
        if (memcmp(string, sets[i], SET_NAME_CHARACTER_LENGTH) == 0)
            return (i);
    }
    return (-1);
}

int validNumber(char *string)
{
    char *ptr;
    long num;

    num = strtol(string, &ptr, DECIMAL);

    if (num == -1)
        return (-1);

    if (1 <= num && num <= 9)
        return (1);
   else if (10 <= num && num <= 99)
        return (2);
    else if (100 <= num && num <= 127)
        return (3);
    else if (num < 0 || 127 < num)
        printf("Invalid set member - value out of range\n");
    else if (num == 0)
    {
        if (*string == '0')
        {
            return (1);
        }
        else
        {
            printf("Invalid set member - not an integer\n");
        }
    }
    return (0);
}
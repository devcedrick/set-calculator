#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define UNIVERSAL_SIZE 10
#define UNIVERSAL_MIN 1

int* initialize_universal_set();
int* take_inputs();
int count_elements(int *set);
uint64_t convert_to_bitstring(int *set, int *uSet, int size);
void display_result(uint64_t bits, int *uSet);


int main()
{
    uint64_t A, B;

    //Allocate memory for Set A and B
    int *setA=malloc(10*sizeof(int));
    int *setB=malloc(10*sizeof(int));

    int *universe=malloc(UNIVERSAL_SIZE*sizeof(int));
    // Initialize the universal set
    universe=initialize_universal_set();

    printf("\nDIRECTION: Enter at most 10 elements for each set. Every element should not exceed values from 1 to 10, each seperated by spaces.\n");

    //Taking inputs for Set A
    printf("Set A: ");
    setA=take_inputs();
    int sizeA=count_elements(setA);

    //Taking inputs for Set B
    printf("Set B: ");
    setB=take_inputs();
    int sizeB=count_elements(setB);

    //Converting Set A and B into bit strings
    A=convert_to_bitstring(setA,universe,sizeA);
    B=convert_to_bitstring(setB,universe,sizeB);

    //List of results variable
    uint64_t A_complement = ~A;
    uint64_t B_complement = ~B;
    uint64_t A_union_B = A|B;
    uint64_t A_intersect_B = A&B;
    uint64_t A_minus_B = A&(~B);
    uint64_t B_minus_A = B&(~A);
    uint64_t A_xor_B = A^B;

    printf("\nRESULTS\n");
    printf("~A = ");
    display_result(A_complement,universe);
    printf("~B = ");
    display_result(B_complement,universe);
    printf("A UNION B = ");
    display_result(A_union_B,universe);
    printf("A INTERSECTS B = ");
    display_result(A_intersect_B,universe);
    printf("A-B = ");
    display_result(A_minus_B,universe);
    printf("B-A = ");
    display_result(B_minus_A,universe);
    printf("A XOR B = ");
    display_result(A_xor_B,universe);

    free(universe);
    free(setA);
    free(setB);
    return 0;
}

int* initialize_universal_set()
{
    int *universe=malloc(UNIVERSAL_SIZE*sizeof(int));
    for(int i=0; i<UNIVERSAL_SIZE; i++)
    {
        universe[i]=i+1;
    }
    return universe;
}

int* take_inputs()
{
    char input[256];
    fgets(input,sizeof(input),stdin);

    int *set=malloc(50*sizeof(int));

    char *token=strtok(input, " ");
    int ctr=0;
    while(token!=NULL&&ctr<50)
    {
        set[ctr]=atoi(token);
        if(!(set[ctr]>=UNIVERSAL_MIN&&set[ctr]<=UNIVERSAL_SIZE))
        {
            printf("You are trying to enter values that is beyond the range of 1-10. Please restart the program to try again.");
            break;
        }
        token=strtok(NULL," ");
        ctr++;
    }
    set[ctr]=-21505;

    return set=(int*)realloc(set,(ctr+1)*sizeof(int));
}

int count_elements(int *set)
{
    int ctr=0;
    while(set[ctr]!=-21505)
    {
        ctr++;
    }
    return ctr;
}

uint64_t convert_to_bitstring(int *set, int *uSet, int size)
{
    uint64_t bit=0;
    for(int i=0; i<UNIVERSAL_SIZE; i++)
    {
        for(int j=0; j<size; j++)
        {
            if(uSet[i]==set[j])
            {
                bit=bit|(1ULL<<(uSet[i]-1));
                break;
            }
        }
    }
    return bit;
}

void display_result(uint64_t bits, int *uSet)
{
    printf("{");
    for(int i=0; i<UNIVERSAL_SIZE; i++)
    {
        if(1ULL<<i&bits)
        {
            printf("%d ",uSet[i]);
        }
    }
    printf("}\n");
}
/*
 * uva 100 The 3n+1 problem
 * http://uva.onlinejudge.org/external/1/100.pdf
 *
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 1000000+1
static unsigned long cycle[MAX_SIZE];

bool is_valid(unsigned long input)
{
    return ( input > 0 && input < MAX_SIZE) ? true : false;
}

// the 3n plus one problem
unsigned long tnpo(unsigned long input) 
{
    unsigned long i = 0, j = 0, cycle_count = 1, id = 0;
    unsigned long ref[MAX_SIZE]; 
    
    // perform algorithm
    while (input != 1) {
        if (is_valid(input) && cycle[input] != 0){ 
            cycle_count += cycle[input] - 1;
            break;
        }   
        input = (input%2 == 0) ? (input/2) : (3*input+1);
        ref[i] = input;
        cycle_count++;
        i++;
    }   
    
    // set known cycle count to the cycle[] array 
    while (j < i) {
        id = ref[j];
        if (is_valid(id) && cycle[id] == 0)
            cycle[id] = cycle_count - j - 1;
        j++;
    }   

    return cycle_count;
}

int main(int argc, char* argv[])
{
    static unsigned long start, end,  i, max = 0;

    if (argc < 3) {
        goto usage;
    } else {
        start = atoi(argv[1]);
        end = atoi(argv[2]);

        if ( !is_valid(start) || !is_valid(end) || start > end)
            goto usage;
    }

    for (i = start; i <= end; i++){
        cycle[i] = tnpo(i);
        if (cycle[i] > max)
            max = cycle[i];
    }

    printf("Sample Input\n%lu %lu\n", start, end);
    printf("Sample Output\n%lu %lu %lu\n", start, end, max);

    return 0;

usage:
    printf("usage: ./test <integer1> <integer2>\n");
    printf("\tchoose two integers from 1 to %d as input\n", MAX_SIZE-1);
    return -1;
}

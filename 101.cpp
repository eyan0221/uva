/*
 * UVa 101 The Blocks Problem
 * http://uva.onlinejudge.org/external/1/101.pdf
 */

#include <stdlib.h>
#include <string>
#include <iostream>

using namespace std;

static unsigned long array_size;
static unsigned long **block;
static unsigned long *pos;
static unsigned long *count;
static unsigned long a, b;
static bool move, onto;

void init_array(void)
{
    unsigned long i;
    block = new unsigned long*[array_size];
    count = new unsigned long[array_size];
    pos = new unsigned long[array_size];

    for (i = 0; i < array_size; i++) {
        block[i] = new unsigned long[array_size];
        block[i][0] = i;
        count[i] = 1;
        pos[i] = i;
    }
}

void dump_array(void)
{
    unsigned long i, j;
    for (i = 0; i < array_size; i++) {
        cout << i << ":";
        for (j = 0; j < array_size; j++) {
            if (block[i][j]>0 || (i==j && i==0)) {
                cout << " " << block[i][j];
            }
        }
        cout << endl;
    }
    cout << endl;
}

int is_valid(unsigned long a, unsigned long b)
{
    int ret = ((a < array_size) && (b < array_size) && (a != b)) ? 0 : -1;
    ret = (pos[a] == pos[b])? -2 : 0;
    return ret;
}

unsigned long pop(unsigned long from_idx)
{
    unsigned long from_count = count[from_idx]--;
    unsigned long item = block[from_idx][from_count-1];
    block[from_idx][from_count-1] = 0;
    pos[item] = 0;
    return item;
}

void push(unsigned long item, unsigned long to_idx)
{
    unsigned long to_count = count[to_idx]++;
    block[to_idx][to_count] = item;
    pos[item] = to_idx;
}

void move_action(unsigned long a, unsigned long b)
{
    unsigned long from_idx = pos[a], to_idx = pos[b];
    unsigned long from_count = count[from_idx];
    unsigned long item, i;

    for (i=from_count-1; i>=0; i--){
        item = pop(from_idx);
        push(item, to_idx);
        if (item == a)
            break;
    }
}

void pile_action(unsigned long a, unsigned long b)
{
    unsigned long from_idx = pos[a], to_idx = pos[b];
    unsigned long from_count = count[from_idx];
    unsigned long item, i;

    for (i=from_count-1; i>=0; i--){
        if (block[from_idx][i] == a)
            break;
    }

    for (; i<from_count; i++) {
        item = block[from_idx][i];
        block[from_idx][i] = 0;
        count[from_idx]--;
        push(item, to_idx);
    }
}

void clear_block(unsigned long id)
{
    unsigned long i, item;
    unsigned long from_idx = pos[id];
    unsigned long from_count = count[from_idx];

    for (i=from_count-1; i>=0; i--) {
        item = pop(from_idx);
        if (item == id) {
            push(item, from_idx);
            break;
        } else {
            push(item, item);
        }
    }
}

int parsing(void)
{
    int err;
    string input1, input2;
  
    cin >> input1;
    
    if (input1 == "move") { move = true;
    } else if (input1 == "pile") { move = false;
    } else if (input1 == "quit") {
        cout << "Sample Output" << endl;
        dump_array();
        return 1;
    } else goto invalid_input;
  
    cin >> a;
    cin >> input2;

    if (input2 == "onto") onto = true;        
    else if (input2 == "over") onto = false;        
    else goto invalid_input;

    cin >> b;

    if ((err = is_valid(a,b)) < 0) goto invalid_input;  

    return 0;

invalid_input:    
    cout << "illegal command! ";
    if (err == -1) cout << "a cannot be equal to b";
    if (err == -2) cout << "a and b cannot be in the same stack of blocks";
    cout << endl;
    return err;
}

int main(int argc, char* argv[])
{
    int ret;
    if (argc < 2)
        goto usage;

    // init array
    array_size = atoi(argv[1]); 
    init_array();
    dump_array();

    cout << "Sample Input" << endl;
    cout << "\t[move|pile] <integer1> [onto|over] <integer2> or" << endl;
    cout << "\t[quit] to leave this program" << endl;

    do {
        // parsing commands
        ret = parsing();
        if (ret == 1) break;
        else if (ret < 0) continue;

        // moving blocks
        if (move) clear_block(a);
        if (onto) clear_block(b);
        if (move) move_action(a,b);
        else pile_action(a,b);

        // show results
        dump_array();
    } while(1);

    return 0;

usage: 
    cout << "usage: ./101 <integer>" << endl;
    return -1;
}

/*
 * UVa 102 Ecological Bin Packing
 * http://uva.onlinejudge.org/external/1/102.pdf
 *
 */

#include <iostream>
using namespace std;

unsigned int line[3][3];
unsigned int count[6];
char color[3] = { 'B', 'G', 'C'};

enum {
    B = 0,
    G = 1,
    C = 2
};

unsigned int pattern[6][3] = { 
    {B, C, G}, 
    {B, G, C}, 
    {C, B, G},
    {C, G, B}, 
    {G, B, C}, 
    {G, C, B} 
};

unsigned int move_count (int c1, int c2, int c3)
{
    return line[1][c1] + line[2][c1] + 
           line[0][c2] + line[2][c2] +
           line[0][c3] + line[1][c3];
}

int main()
{
    unsigned int i, j, min, idx;
    
    cout << "Sample Input" << endl;
    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
            cin >> line[i][j];
  
    for (i = 0; i < 6; i++) {
        count[i] = move_count(pattern[i][0], pattern[i][1], pattern[i][2]);
        if (min == 0 || count[i] < min) {
            min = count[i];
            idx = i;
        }
    }

    cout << "Sample Output" << endl;
    cout << color[pattern[idx][0]] << color[pattern[idx][1]] << color[pattern[idx][2]] << " " << min << endl;

    return 0;
}

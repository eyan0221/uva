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

int main()
{
    unsigned int i, j, min, idx, sum = 0;
    
    cout << "Sample Input" << endl;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            cin >> line[i][j];
            sum += line[i][j];
        }
    }
  
    for (i = 0; i < 6; i++) {
        count[i] = sum - (line[0][pattern[i][0]] + line[1][pattern[i][1]] + line[2][pattern[i][2]]);
        if (min == 0 || count[i] < min) {
            min = count[i];
            idx = i;
        }
    }

    cout << "Sample Output" << endl;
    cout << color[pattern[idx][0]] << color[pattern[idx][1]] << color[pattern[idx][2]] << " " << min << endl;

    return 0;
}

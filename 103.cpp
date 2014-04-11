/*
 * UVa 103 Stacking Boxes
 * http://uva.onlinejudge.org/external/1/103.pdf
 *
 * Find more input samples in 
 * http://www.algorithmist.com/index.php/UVa_103
 */

#include <iostream>
using namespace std;

#define NUM_BOXES 30
#define MAX_DIMENSIONS 10
unsigned int box[NUM_BOXES][MAX_DIMENSIONS];
unsigned int num_boxes;
unsigned int dimensions;

/* Quick Sorting */
void swap(unsigned int *array, 
          unsigned int x, 
          unsigned int y)
{
    unsigned int temp;
    temp = array[x];
    array[x] = array[y];
    array[y] = temp;
}

unsigned int pick_pivot(unsigned int left, 
                        unsigned int right)
{
    return (unsigned int)(left + (right - left)/2);
}

unsigned int partition(unsigned int *array, 
                       unsigned int left, 
                       unsigned int right, 
                       unsigned int pivot_idx, 
                       unsigned int *a)
{
    unsigned int new_idx, pivot, i;
    pivot = array[pivot_idx];
    swap(array, pivot_idx, right);
    if (a) swap(a, pivot_idx, right);
    new_idx = left;

    for (i = left; i < right; i++) {
        if (array[i] <= pivot ) {
            swap(array, i, new_idx);
            if (a) swap(a, i, new_idx);
            new_idx++;
        }
    }
    swap(array, new_idx, right);
    if (a) swap(a, new_idx, right);

    return new_idx;
}

int quicksort(unsigned int *array, 
              unsigned int left, 
              unsigned int right, 
              unsigned int *a)
{
    unsigned int pivot_idx, pivot_new_idx;

    if (left < right) {
        pivot_idx = pick_pivot(left, right);
        pivot_new_idx = partition(array, left, right, pivot_idx, a);
        if (pivot_new_idx == 0) {
            quicksort(array, 1, right, a);
        } else {
            quicksort(array, left, pivot_new_idx - 1, a);
            quicksort(array, pivot_new_idx + 1, right, a);
        }
    }

    return 0;
}

/* End of Quick Sorting */

int input(void)
{
    unsigned int i, j;

    cout << "Sample Input" << endl;
    cout << "<number of boxes> <dimensions>: ";
    cin >> num_boxes >> dimensions;

    if ((num_boxes > NUM_BOXES) || (num_boxes < 2) || (dimensions > MAX_DIMENSIONS) || (dimensions == 0)) {
        cout << "Error! <number of boxes> must be within (2," << NUM_BOXES << ")" << endl;
        cout << "<dimensions> must be within (1," << MAX_DIMENSIONS << ")" << endl;
        return -1;
    }
    
    cout << endl;
    cout << "box sequences: ";
    for (i = 0; i < num_boxes; i++)
        for (j = 0; j < dimensions; j++)
            cin >> box[i][j];
    cout << endl;

    return 0;
}

void dump(unsigned int *array, 
          unsigned int left, 
          unsigned int right)
{
    unsigned int i;
    for (i = left; i <= right; i++) cout << array[i] << " ";
    cout << endl;
}

bool is_fits(unsigned int *a, 
             unsigned int *b)
{
    unsigned int i;
    for (i = 0; i < dimensions; i++) {
        if (a[i] >= b[i])
            return false;
    }

    return true;
}

int main(void)
{
    unsigned int i, j, k, x, max, max_idx, num_fits = 0;
    unsigned int start_idx, old_idx, start_sum;
    unsigned int target_idx, target_sum; 
    unsigned int temp[2][NUM_BOXES];
    unsigned int fits_idx[NUM_BOXES][NUM_BOXES];
    bool valid = false;

    if (input() < 0) return -1;

    // sorting each box sequence and init temp array
    for (i = 0; i < num_boxes; i++) {
        quicksort(box[i], 0, dimensions - 1, 0);
        temp[0][i] = 0; // sum
        temp[1][i] = i; // box index
        for (j = 0; j < dimensions; j++) temp[0][i] += box[i][j];
    }

    // sorting temp[0] and reorder box index in temp[1] accordingly
    quicksort(temp[0], 0, num_boxes - 1, temp[1]);

#if 0 // print sorted box sequences
    for (i = 0; i < num_boxes; i++) {
        j = temp[1][i];
        cout << "sum(" << temp[0][i] << "),\t";
        cout << "box[" << j+1 << "]: ";
        dump(box[j], 0, dimensions - 1);
    }
    cout << endl;
#endif

    // init the fitting boxes index list
    x = max = max_idx = 0;
    for (k = 0; k < num_boxes; k++) {
        // init a starting candidate box[start_idx]
        start_sum = temp[0][k];
        start_idx = temp[1][k];
        num_fits = 0;
        
        for (i = 0; i < num_boxes; i++) {
            target_sum = temp[0][i];
            target_idx = temp[1][i];

            // call is_fits() only if target_sum - start_sum >= dimensions
            valid = ((target_sum > start_sum) && ((target_sum - start_sum) >= dimensions)) ? true : false;
            if (valid && is_fits(box[start_idx], box[target_idx])) {
                // found fitting boxes
                if (num_fits == 0) fits_idx[x][num_fits++] = start_idx;
                start_idx = fits_idx[x][num_fits++] = target_idx; 
                start_sum = target_sum;
            }
        }
        
        if (num_fits > max) { 
            max = num_fits;
            max_idx = x;
        }

        // early exit when the number of fitting boxes is bigger enough
        if (num_fits > (num_boxes - num_fits)) break;
        if (num_fits > 0) x++;
    }
    
    if (max == 0) {
        fits_idx[0][0] = temp[1][0];
        max = 1;
    }
    
    // print the results
    cout << "Sample Output" << endl;
    cout << max << endl;
    for (i = 0; i < max; i++) {
         cout << fits_idx[max_idx][i]+1 << " ";
    }
    cout << endl;

    return 0;
}

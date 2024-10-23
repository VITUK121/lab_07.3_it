#include <iostream>
#include <iomanip>
#include <time.h>
#include <stdlib.h>

using namespace std;

int** make_arr(int rows, int cols, int low, int high) {
    int** arr = new int* [rows];
    for (int i = 0; i != rows; i++) {
        arr[i] = new int[cols];
    }
    for (int i = 0; i != rows; i++) {
        for (int j = 0; j != cols; j++) {
            arr[i][j] = low + rand() % (high - low + 1);
        }
    }
    return arr;
}

void print_arr(int** arr, int rows, int cols) {
    for (int i = 0; i != rows; i++) {
        for (int j = 0; j != cols; j++) {
            cout << setw(4) << arr[i][j];
        }
        cout << endl;
    }
    cout << endl;
}

int rowSpec(int** arr, int rows, int col_index) {
    int sum = 0;
    for (int i = 0; i != rows; i++) {
        if (arr[i][col_index] < 0 && arr[i][col_index] % 2 != 0) {
            sum += abs(arr[i][col_index]);
        }
    }
    return sum;
}

void sortBySpecs(int** arr, int rows, int cols) {
    int tmp;
    for (int i = 0; i != cols - 1; i++) {
        for (int j = 0; j != cols - i - 1; j++) {
            if (rowSpec(arr, rows, j) > rowSpec(arr, rows, j + 1)) {
                for (int k = 0; k != rows; k++) {
                    tmp = arr[k][j];
                    arr[k][j] = arr[k][j + 1];
                    arr[k][j + 1] = tmp;
                }
            }
        }
    }
}

int sumWithNegative(int** arr, int rows, int cols) {
    int sum = 0;
    for (int i = 0; i != cols; i++) {
        bool isNegative = false;
        int col_sum = 0;
        for (int j = 0; j != rows; j++) {
            if (arr[j][i] < 0) {
                isNegative = true;
            }
            col_sum += arr[j][i];
        }
        if (isNegative) {
            sum += col_sum;
        }
    }
    return sum;
}

int main(){
    srand(time(NULL));
    int k, n, col_index;
    cout << "k = "; cin >> k;
    cout << "n = "; cin >> n;
    cout << "nth row = "; cin >> col_index;

    int** a = make_arr(k, n, -10, 10);
    print_arr(a, k, n);
    cout << col_index << " col specs = " << rowSpec(a, k, col_index-1) << endl << endl;
    sortBySpecs(a, k, n);
    print_arr(a, k, n);
    cout << "sum = " << sumWithNegative(a, k, n) << endl;


    for (int i = 0; i != k; i++) {
        delete[] a[i];
    }
    delete[] a;
}
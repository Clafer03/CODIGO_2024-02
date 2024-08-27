#include <iostream>
#include <vector>
using namespace std;


int maxSubArraySum(vector<int> &arr){
    int max_actual = arr[0];
    int max_global = arr[0];

    for(int i = 0; i < arr.size(); i++){
        max_actual = max(arr[i], max_actual + arr[i]);
        if(max_actual > max_global){
            max_global = max_actual;
        }
    }
    return max_global;
}

int main(){

    vector<int> arr = {-2, 8, -3, 4, -1, 3, 1, -5, 4};
    cout << "Sum: " << maxSubArraySum(arr);

}
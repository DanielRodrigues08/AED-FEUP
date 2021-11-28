#include "funSearchProblem.h"

FunSearchProblem::FunSearchProblem() {}

//-----------------------------------------------------------------

// TODO
int FunSearchProblem::facingSun(const vector<int> & values) {
    int numBuilds = 1, maxSize = values[0];
    for(unsigned int i = 1; i < values.size(); i++){
        if(values[i] > maxSize){
            maxSize = values[i];
            numBuilds += 1;
        }
    }
    return numBuilds;
}

// TODO
int FunSearchProblem::squareR(int num) {
    int left = 1, center, right = num, result;
    if(num < 2){
        return num;
    }

    while(left <= right){
        center = (right+left) / 2;
        if(center * center == num)
            return center;
        else if(center*center > num)
            right = center -1;
        else {
            left = center + 1;
            result = center;
        }
    }
    return result;

}

// TODO
int FunSearchProblem::smallestMissingValue(const vector<int> & values) {
    int minVal = 0;
    for(auto idx: values){
        if(idx > 0){
            minVal = idx;
            break;
        }
    }
    if(minVal <= 0)
        return 0;

    for(auto idx: values){
        if(idx > 0 && idx < minVal )
            minVal = idx;
    }

    return minVal;
}

// TODO
int FunSearchProblem::minPages(const vector<int> & values, int numSt) {
    return 0;
}


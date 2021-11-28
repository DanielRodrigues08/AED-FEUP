#include "funSortProblem.h"
#include <algorithm>
#include <random>

FunSortProblem::FunSortProblem() {}


//-----------------------------------------------------------------

// TODO
bool mySort(const Product &p1, const Product &p2) {
    if (p1.getPrice() == p2.getPrice())
        return p1.getWeight() < p2.getWeight();
    return p1.getPrice() < p2.getPrice();
}


void FunSortProblem::expressLane(vector<Product> &products, unsigned k) {
    if(products.size() > k) {
        std::sort(products.begin(), products.end(), mySort);
        products.erase(products.begin()+k);
    }
}

// TODO
int FunSortProblem::minDifference(const vector<unsigned> &values, unsigned nc) {
    if(values.size()<nc)
        return -1;
    vector<unsigned> myValues;
    for(auto idx: values)
        myValues.push_back(idx);
    sort(myValues.begin(),myValues.end());

    if(myValues.size() == nc)
        return myValues.back() - myValues[0];

    int minVal = myValues.back();
    for(size_t i = 0; i < myValues.size() - nc; i++)
        for(size_t j = i+nc-1; j < myValues.size();j++)
            if((myValues[j]-myValues[i])<minVal)
                minVal = myValues[j]-myValues[i];
    return minVal;
}


// TODO
unsigned FunSortProblem::minPlatforms (const vector<float> &arrival, const vector<float> &departure) {
    vector<float> myDeparture = departure;
    sort(myDeparture.begin(),myDeparture.end());

    unsigned result=1, plataformNeeded=1;
    int i=1, j=0;
    while (i<arrival.size() && j<arrival.size()){
        if(arrival[i] <= myDeparture[j]){
            plataformNeeded++;
            i++;
        }else{
            plataformNeeded--;
            j++;
        }
        if(plataformNeeded>result)
            result = plataformNeeded;
    }
    return result;
}


// TODO


void FunSortProblem::nutsBolts(vector<Piece> &nuts, vector<Piece> &bolts) {
}


#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "funSearchProblem.h"

using testing::Eq;

/*
TEST(test, facingsun){
    FunSearchProblem problem;
    ASSERT_EQ(3,problem.facingSun({10,5,20,15,30}));
    ASSERT_EQ(1,problem.facingSun({50,40,30,20,10}));
    ASSERT_EQ(5,problem.facingSun({10,20,30,40,50}));
    ASSERT_EQ(4,problem.facingSun({10,100,20,30,200,500,400}));
    ASSERT_EQ(5,problem.facingSun({10,20,100,200,200,500}));
}
 */

/*
TEST(test, squareR){
    FunSearchProblem problem;
    ASSERT_EQ(2,problem.squareR(4));
    ASSERT_EQ(3,problem.squareR(13));
    ASSERT_EQ(4,problem.squareR(16));
    ASSERT_EQ(5,problem.squareR(25));
    ASSERT_EQ(4,problem.squareR(17));
    ASSERT_EQ(5,problem.squareR(29));
    ASSERT_EQ(8,problem.squareR(70));
    ASSERT_EQ(5,problem.squareR(30));
    ASSERT_EQ(5,problem.squareR(31));
    ASSERT_EQ(5,problem.squareR(32));
}
*/

TEST(test, missingvalue){
    FunSearchProblem problem;
    ASSERT_EQ(0,problem.smallestMissingValue({-10,-6,0,0,-5,-4}));
    ASSERT_EQ(0,problem.smallestMissingValue({0,0,0,0,0,0,0}));
    ASSERT_EQ(7,problem.smallestMissingValue({-5,-4,-10,-20,7,8}));
    //ASSERT_EQ(,problem.smallestMissingValue({}));
}
/*
TEST(test, minPages){

}
*/
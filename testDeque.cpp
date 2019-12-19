#define CATCH_CONFIG_MAIN
#include <iostream>
#include "cs221util/catch.hpp"
#include "deque.h"
//using namespace cs221util;
using namespace std;

TEST_CASE("stack::basic functions","[weight=1][part=stack]"){
    Deque<int> intDeque;
    for(int i=1; i<=5; i++){
        intDeque.pushR(i);
    }
    intDeque.popL();
    intDeque.popL();
    intDeque.pushR(6);
    intDeque.popL();
    intDeque.popR();
    intDeque.popR();
}
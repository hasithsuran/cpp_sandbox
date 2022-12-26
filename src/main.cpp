#include <iostream>
#include <TC_Vector.h>
#include <TC_BitwiseOp.h>

int main( int argc, char **argv) {
    #ifdef USE_BITWISE_DEMO
        techyB::TC_BitwiseOp bOp;
        bOp.performBitLeftShift();
        bOp.performBitRightShift();
        bOp.doLogicalBitwiseOperation();
    #endif

    #ifdef USE_VECTOR_DEMO
        techyB::TC_Vector vecDemo;
        vecDemo.printVec();
    #endif


    
    return 0;
}

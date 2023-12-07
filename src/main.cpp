#include <iostream>
#include <TC_Vector.h>
#include <TC_BitwiseOp.h>
#include <TC_Lambda.h>
#include <TC_Map.h>
#include <TC_Memory.h>
#include <TC_Adapter.h>
#include <TC_Facade.h>
#include <TC_Variant.h>
#include <TC_Optional.h>


int main(int argc, char **argv)
{
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

#ifdef USE_LAMBDA_DEMO
    techyB::TC_Lambda lambdaDemo;
    lambdaDemo.basicLambdaDemo();
    lambdaDemo.basicLambdaValuePassingDemo();
#endif

#ifdef USE_MAP_DEMO
    techyB::TC_Map mapDemo;
    mapDemo.attributeDemo();
    mapDemo.insertOrAssign();
    mapDemo.initDemo();
    mapDemo.creationDemo();
#endif

#ifdef USE_BASIC_MEMORY_DEMO
    techyB::TC_Memory memoryDemo;
    memoryDemo.basicCopyDemo();
    memoryDemo.advancedMemoryMovement();
#endif

#ifdef USE_DESIGN_CONCEPT_DEMO
    techyB::designs::adaptor::runClient();
    techyB::designs::facade::runClient();
#endif

#ifdef USE_VARIANT_OPTIONAL_DEMO
    techyB::essentials::VariantDemo::runClient();
    techyB::essentials::OptionalDemo::runClient();
#endif

    return 0;
}

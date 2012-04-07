//
//  main.cpp
//  ATRayTracer
//
//  Created by Andrew Taeoalii on 4/6/12.
//  Copyright (c) 2012 Apple Inc. All rights reserved.
//

#include <iostream>
#include "ATScene.h"

int main(int argc, const char * argv[])
{
    ATScene ats;
    ats.readInScene("test.txt");
    return 0;
}


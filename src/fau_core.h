#pragma once
#include <bits/stdc++.h>

// although being a fault but worth a memorialize
namespace fau {
    typedef int status_t; // a type of integer that describes the status of
                          // functions while they're running
    namespace code { // codes that describes status of functions
        const status_t ERROR = 0;
        const status_t SUCCEEDED = 1;
        const status_t WARNING = 2;
        const status_t ACCEPTED = 1;
        const status_t NOT_EXISTS = -1;
        const status_t UNKNOWN_RESULT = -255;
    }; // namespace code
    
}; // namespace esp
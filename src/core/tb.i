%module tbpy
%{

#define SWIG_FILE_WITH_INIT
namespace arma{
}

#include "Lead.h"
#include "Insulator.h"
#include "Chain.h"
%}


namespace arma{
}


//%include "include/armanpy.i"
%include "std_string.i"
%include "std_vector.i"
%include "TB.h"
%include "Lead.h"
%include "Insulator.h"
%include "Chain.h"


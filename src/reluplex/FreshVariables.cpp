/*********************                                                        */
/*! \file FreshVariables.cpp
 ** \verbatim
 ** Top contributors (to current version):
 **   Guy Katz
 ** This file is part of the Marabou project.
 ** Copyright (c) 2016-2017 by the authors listed in the file AUTHORS
 ** in the top-level source directory) and their institutional affiliations.
 ** All rights reserved. See the file COPYING in the top-level source
 ** directory for licensing information.\endverbatim
 **/

#include "FreshVariables.h"

unsigned FreshVariables::_nextVariable = 0;

unsigned FreshVariables::getNextVariable()
{
    return _nextVariable++;
}

void FreshVariables::setNextVariable( unsigned value )
{
    _nextVariable = value;
}

//
// Local Variables:
// compile-command: "make -C .. "
// tags-file-name: "../TAGS"
// c-basic-offset: 4
// End:
//

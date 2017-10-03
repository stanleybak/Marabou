/*********************                                                        */
/*! \file PiecewiseLinearCaseSplit.h
** \verbatim
** Top contributors (to current version):
**   Guy Katz
** This file is part of the Marabou project.
** Copyright (c) 2016-2017 by the authors listed in the file AUTHORS
** in the top-level source directory) and their institutional affiliations.
** All rights reserved. See the file COPYING in the top-level source
** directory for licensing information.\endverbatim
**/

#ifndef __PiecewiseLinearCaseSplit_h__
#define __PiecewiseLinearCaseSplit_h__

#include "Equation.h"
#include "IEngine.h"
#include "Pair.h"
#include "Tightening.h"

class PiecewiseLinearCaseSplit
{
public:
    enum EquationType {
        EQ = 0,
        GE = 1,
        LE = 2
    };

    /*
      Store information regarding a bound tightening.
    */
    void storeBoundTightening( const Tightening &tightening );
    List<Tightening> getBoundTightenings() const;

    /*
      Store information regarding a new equation to be added.
    */
    void addEquation( const Equation &equation, EquationType type );
  	List<Pair<Equation, EquationType> > getEquations() const;

    /*
      Dump the case split - for debugging purposes.
    */
    void dump() const;

private:
    /*
      Bound tightening information.
    */
    List<Tightening> _bounds;

    /*
      The equation that needs to be added.
    */
    List<Pair<Equation, EquationType> > _equations;
};

#endif // __PiecewiseLinearCaseSplit_h__

//
// Local Variables:
// compile-command: "make -C ../.. "
// tags-file-name: "../../TAGS"
// c-basic-offset: 4
// End:
//
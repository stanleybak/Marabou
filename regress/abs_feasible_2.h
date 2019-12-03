//
// Created by shirana on 10/11/2019.
//

#ifndef MARABOU_ABS_FEASIBLE_H
#define MARABOU_ABS_FEASIBLE_H


#include "Engine.h"
#include "FloatUtils.h"
#include "InputQuery.h"
#include "AbsConstraint.h"

class Abs_Feasible_2
{
public:
    void run()
    {
        // The example from the CAV'17 paper, without the aux variables:
        //   0   <= x0  <= 1
        //   0   <= x1f
        //   0   <= x2f
        //   1/2 <= x3  <= 1
        //
        //  x0 - x1b = 0
        //  x0 + x2b = 0
        //  x1f + x2f - x3 = 0
        //
        //  x2f = Abs(x2b)
        //  x3f = Abs(x3b)
        //
        //   x0: x0
        //   x1: x1b
        //   x2: x1f
        //   x3: x2b
        //   x4: x2f
        //   x5: x3

        InputQuery inputQuery;
        inputQuery.setNumberOfVariables( 6 );

        inputQuery.setLowerBound( 0, -1 );
        inputQuery.setUpperBound( 0, 1 );

        inputQuery.setLowerBound( 5, 0.5 );
        inputQuery.setUpperBound( 5, 1 );

        Equation equation1;
        equation1.addAddend( 1, 0 );
        equation1.addAddend( -1, 1 );
        equation1.setScalar( 0 );
        inputQuery.addEquation( equation1 );

        Equation equation2;
        equation2.addAddend( 1, 0 );
        equation2.addAddend( 1, 3 );
        equation2.setScalar( 0 );
        inputQuery.addEquation( equation2 );

        Equation equation3;
        equation3.addAddend( 1, 2 );
        equation3.addAddend( 1, 4 );
        equation3.addAddend( -1, 5 );
        equation3.setScalar( 0 );
        inputQuery.addEquation( equation3 );

        AbsConstraint *abs1 = new AbsConstraint( 1, 2 );
        AbsConstraint *abs2 = new AbsConstraint( 3, 4 );

        inputQuery.addPiecewiseLinearConstraint( abs1 );
        inputQuery.addPiecewiseLinearConstraint( abs2 );

        int outputStream = redirectOutputToFile( "logs/abs_feasible_2.txt" );

        struct timespec start = TimeUtils::sampleMicro();

        Engine engine;
        if ( !engine.processInputQuery( inputQuery ) )
        {
            struct timespec end = TimeUtils::sampleMicro();
            restoreOutputStream( outputStream );
            printFailed( "abs_feasible_2", start, end );
            return;
        }

        bool result = engine.solve();

        struct timespec end = TimeUtils::sampleMicro();

        restoreOutputStream( outputStream );

        if ( !result )
        {
            printFailed( "abs_feasible_2", start, end );
            return;
        }

        engine.extractSolution( inputQuery );

        bool correctSolution = true;
        // Sanity test

        double value_x0 = inputQuery.getSolutionValue( 0 );
        double value_x1b = inputQuery.getSolutionValue( 1 );
        double value_x1f = inputQuery.getSolutionValue( 2 );
        double value_x2b = inputQuery.getSolutionValue( 3 );
        double value_x2f = inputQuery.getSolutionValue( 4 );
        double value_x3 = inputQuery.getSolutionValue( 5 );



        if ( !FloatUtils::areEqual( value_x0, value_x1b ) )
            correctSolution = false;



        if ( !FloatUtils::areEqual( value_x0, -value_x2b ) )
        {
            correctSolution = false;
        }


        if ( !FloatUtils::areEqual( value_x3, value_x1f + value_x2f ) )
        {
            correctSolution = false;
        }

        if ( FloatUtils::lt( value_x0, -1 ) || FloatUtils::gt( value_x0, 1 ) ||
             FloatUtils::lt( value_x1f, 0 ) || FloatUtils::lt( value_x2f, 0 ) ||
             FloatUtils::lt( value_x3, 0.5 ) || FloatUtils::gt( value_x3, 1 ) )
        {
            correctSolution = false;
        }

        if ( !FloatUtils::areEqual(FloatUtils::abs(value_x1b), value_x1f ) )
        {
            correctSolution = false;
        }

        if ( !FloatUtils::areEqual(FloatUtils::abs(value_x2b), value_x2f ) )
        {
            correctSolution = false;
        }

        if ( !correctSolution )
            printFailed( "abs_feasible_2", start, end );
        else
            printPassed( "abs_feasible_2", start, end );
    }
};


#endif //MARABOU_ABS_FEASIBLE_H
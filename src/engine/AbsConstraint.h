//
// Created by shirana on 5/22/19.
//

#ifndef MARABOU_ABSCONSTRAINT_H
#define MARABOU_ABSCONSTRAINT_H




#include "PiecewiseLinearConstraint.h"


class AbsConstraint : public PiecewiseLinearConstraint
{

public:
    enum PhaseStatus {
        PHASE_NOT_FIXED = 0,
        PHASE_POSITIVE = 1,
        PHASE_NEGATIVE = 2,
    };

    AbsConstraint(unsigned b, unsigned f );

    /*
    Return a clone of the constraint.
  */
    PiecewiseLinearConstraint *duplicateConstraint() const;

    /*
      Restore the state of this constraint from the given one.
    */
    void restoreState(const PiecewiseLinearConstraint *state);

    /*
      Register/unregister the constraint with a talbeau.
     */
    void registerAsWatcher(ITableau *tableau);

    void unregisterAsWatcher(ITableau *tableau);

    /*
    These callbacks are invoked when a watched variable's value
    changes, or when its bounds change.
  */
    void notifyVariableValue( unsigned variable, double value );
    void notifyLowerBound( unsigned variable, double bound );
    void notifyUpperBound( unsigned variable, double bound );


    /*
       Returns true iff the variable participates in this piecewise
       linear constraint.
     */
    bool participatingVariable(unsigned variable) const;

    /*
      Get the list of variables participating in this constraint.
    */
    List<unsigned> getParticipatingVariables() const;

    /*
      Returns true iff the assignment satisfies the constraint
    */
    bool satisfied() const;

    /*
    Returns a list of possible fixes for the violated constraint.
    */
    List<PiecewiseLinearConstraint::Fix> getPossibleFixes() const;

    List<PiecewiseLinearConstraint::Fix> getSmartFixes( ITableau *tableau ) const;

    List<PiecewiseLinearCaseSplit> getCaseSplits() const;

    bool phaseFixed() const;

    PiecewiseLinearCaseSplit getValidCaseSplit() const;

    void eliminateVariable( unsigned variable, double fixedValue );
    void updateVariableIndex( unsigned oldIndex, unsigned newIndex );
    bool constraintObsolete() const;

    void getEntailedTightenings( List<Tightening> &tightenings ) const;

    void getAuxiliaryEquations( List<Equation> &newEquations ) const;

    String serializeToString() const;



private:
    // variables name. example x_1, x_2, etc.
    unsigned _b, _f;

    // if one of our variable i.e _b or _f have been terminated
    // caused by bound tightening
    bool _haveEliminatedVariables;

    PhaseStatus _phaseStatus;

    PiecewiseLinearCaseSplit getPositiveSplit() const;
    PiecewiseLinearCaseSplit getNegativeSplit() const;


    /*
      Set the phase status not fixed pos neg.
    */
    void setPhaseStatus( PhaseStatus phaseStatus );
};

#endif //MARABOU_ABSCONSTRAINT_H

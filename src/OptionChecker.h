/*****************************************************************
 * OptionChecker.h
 * Team 22
 * Authors : Abdelkarim Andolerzak & Anasse Ghira & Nicolas Pepin
 ****************************************************************/

 #ifndef OPTIONCHECKER_H
 #define OPTIONCHECKER_H

#include <unistd.h>
#include <stdlib.h>

#define PARAM_MASK "p:t:me:"


class OptionChecker {
private :
    int nbPeople, nbThread;
    int measures = 0, peopleArg = 0, threadArg = 0, phaseArg = 0;

    bool checkThread(int thread);
    bool checkPeople(int people);
    bool checkPhase(int phase);
    void parameterFiller(int nbArgs, char* parameters[]);
    void parameterChecker();


public:
    OptionChecker(int argc, char* argv[]);
    int getnbPeople();
    int getnbThread();
    bool getMeasures();
    int getnbPhase();

};
#endif

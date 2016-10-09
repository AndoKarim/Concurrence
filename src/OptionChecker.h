#include <unistd.h>
#include <stdlib.h>

#define PARAM_MASK "p:t:m"


class OptionChecker {
private :
    int nbPeople, nbThread;
    int measures = 0, peopleArg = 0, threadArg = 0;

    bool checkThread(int thread);
    bool checkPeople(int people);
    void parameterFiller(int nbArgs, char* parameters[]);
    void parameterChecker();


public:
    OptionChecker(int argc, char* argv[]);
    int getnbPeople();
    int getnbThread();
    bool getMeasures();
};
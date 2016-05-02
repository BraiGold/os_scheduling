#ifndef __SCHED_NOMIS__
#define __SCHED_NOMIS__

#include <vector>
#include <queue>
#include <list>
#include <map>
#include "basesched.h"

class SchedNoMistery : public SchedBase {
  public:
    SchedNoMistery(std::vector<int> argn);
    virtual void load(int pid);
    virtual void unblock(int pid);
    virtual int tick(int cpu, const enum Motivo m);

  private:
    std::vector<int> quantumCola;
    int quantumRestante;
    std::list<int> cola;
    std::map<int,int> pid_cola;
    std::map<int,int> pid_quantumExtra;
    int n;
    int next(void);
};

#endif

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
    std::vector<std::queue<int> > colas;
    std::vector<int> quantumCola;
    std::map<int,int> pid_cola;
    int quantumRestante, n, cur_pri;

    int next(void);
};

#endif

#ifndef __SCHED_RR2__
#define __SCHED_RR2__

#include <vector>
#include <queue>
#include <map>
#include "basesched.h"

class SchedRR2 : public SchedBase {
	public:
		SchedRR2(std::vector<int> argn);
        ~SchedRR2();
		virtual void load(int pid);
		virtual void unblock(int pid);
		virtual int tick(int cpu, const enum Motivo m);

	private:
		int cantCores;
		int next(/*int cpu*/);
		std::vector<std::queue<int> > colas;
		std::vector<int> quantum;
		std::vector<int> quantumRestante;
		std::vector<int> cantProc;
		std::map<int,int> pid_cpu;
};

#endif

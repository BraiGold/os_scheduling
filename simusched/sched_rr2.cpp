#include <vector>
#include <queue>
#include "sched_rr2.h"
#include "basesched.h"
#include <iostream>
#include <map>
#include <utility>

using namespace std;

SchedRR2::SchedRR2(vector<int> argn) {
	// Round robin recibe la cantidad de cores y sus cpu_quantum por parámetro
	queue<int> cola;
	for (int i = 0; i < argn[0]; i++) { //a cada core le doy su quantum
		quantum.push_back(argn[i+1]);
		quantumRestante.push_back(argn[i+1]);
		colas.push_back(cola);
		cantProc.push_back(0);
	}
	cantCores=argn[0];
//<<<REMOVE>>>
//<<<REMOVE END>>>
}

SchedRR2::~SchedRR2() {

}


void SchedRR2::load(int pid) {
//<<<REMOVE>>>
int proxCpu=next();
colas[proxCpu].push(pid);
pid_cpu.insert( std::pair<int,int>(pid,proxCpu) );
cantProc[proxCpu]++;
//<<<REMOVE END>>>
}

void SchedRR2::unblock(int pid) {
//<<<REMOVE>>>
int cpu = pid_cpu.at(pid);
colas[cpu].push(pid);
//<<<REMOVE END>>>
}

int SchedRR2::tick(int cpu, const enum Motivo m) {
//<<<REMOVE>>>
int r=IDLE_TASK;
if (m==EXIT || m==BLOCK){
	quantumRestante[cpu]=quantum[cpu]-1;
	if (!colas[cpu].empty()){
		r=colas[cpu].front(); colas[cpu].pop();
	}else{
		r=IDLE_TASK;
	}
	if(m==EXIT){
		pid_cpu.erase(current_pid(cpu));
		cantProc[cpu]--;
	}
}else{
	if(quantumRestante[cpu]==0 || current_pid(cpu)==IDLE_TASK){
		quantumRestante[cpu]=quantum[cpu]-1;
		if(!colas[cpu].empty()){
			r=colas[cpu].front(); colas[cpu].pop();
			if(current_pid(cpu)!=IDLE_TASK)
				colas[cpu].push(current_pid(cpu));
		}else{
			r=current_pid(cpu);
		}
	}else{
			quantumRestante[cpu]--;
			r=current_pid(cpu);
	}
}
return r;
//<<<REMOVE END>>>
}

int SchedRR2::next(/*int cpu*/) {
//<<<REMOVE>>>
int cpuMinimo=0;

for (int i = 0; i < cantCores; i++) {
	if(cantProc[i] < cantProc[cpuMinimo])
		cpuMinimo = i;
}

return cpuMinimo;
//<<<REMOVE END>>>
}

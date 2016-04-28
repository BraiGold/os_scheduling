#include <vector>
#include <queue>
#include "sched_rr.h"
#include "basesched.h"
#include <iostream>

using namespace std;

SchedRR::SchedRR(vector<int> argn) {
	// Round robin recibe la cantidad de cores y sus cpu_quantum por parámetro
	for (int i = 0; i < argn[0]; i++) { //a cada core le doy su quantum
		quantum.push_back(argn[i+1]);
		quantumRestante.push_back(argn[i+1]);
	}
//<<<REMOVE>>>
//<<<REMOVE END>>>
}

SchedRR::~SchedRR() {

}


void SchedRR::load(int pid) {
//<<<REMOVE>>>
	cola.push(pid);
//<<<REMOVE END>>>
}

void SchedRR::unblock(int pid) {
//<<<REMOVE>>>
	cola.push(pid);
//<<<REMOVE END>>>
}

int SchedRR::tick(int cpu, const enum Motivo m) {
//<<<REMOVE>>>
	int r=IDLE_TASK;
	if (m==EXIT || m==BLOCK){
		quantumRestante[cpu]=quantum[cpu]-1;
		if (!cola.empty()){
			r=cola.front(); cola.pop();
		}else{
			r=IDLE_TASK;
		}
	}else{
		if(quantumRestante[cpu]==0 || current_pid(cpu)==IDLE_TASK){
			quantumRestante[cpu]=quantum[cpu]-1;
			if(!cola.empty()){
				r=cola.front(); cola.pop();
				if(current_pid(cpu)!=IDLE_TASK)
					cola.push(current_pid(cpu));
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

//<<<REMOVE>>>

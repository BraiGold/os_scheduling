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
	for (int i = 0; i < argn[0]; i++) { //a cada core le doy su quantum ,seteo los quantumRestante y creo una cola por cada cuantum. ademas seteo en 0 la cantidad de procesos por cpu
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
int proxCpu=next(); //busco el cpu con menor cantidad de procesos y encolo el nuevo proceso ahi
colas[proxCpu].push(pid);
pid_cpu.insert( std::pair<int,int>(pid,proxCpu) );//en el diccionario me guardo que este proceso pertenece a dicho procesador
cantProc[proxCpu]++;//incremento la cantidad de procesos en esta cpu
//<<<REMOVE END>>>
}

void SchedRR2::unblock(int pid) {
//<<<REMOVE>>>
int cpu = pid_cpu.at(pid);//busco a que cola pertenece y  luego encolo:
colas[cpu].push(pid);
//<<<REMOVE END>>>
}

int SchedRR2::tick(int cpu, const enum Motivo m) {
//<<<REMOVE>>>
int r=IDLE_TASK; //por defecto retorno IDLE_TASK
if (m==EXIT || m==BLOCK){ //si es EXIT o un BLOCK, resetear el quantumRestante de esta cpu y desencolar el proximo y devolverlo
	quantumRestante[cpu]=quantum[cpu]-1;
	if (!colas[cpu].empty()){
		r=colas[cpu].front(); colas[cpu].pop();
	}else{
		r=IDLE_TASK;
	}
	if(m==EXIT){//si era un EXIT lo borro del diccionario al proceso y ademas decremento la cant de procesos en este cpu
		pid_cpu.erase(current_pid(cpu));
		cantProc[cpu]--;
	}
}else{//si es un TICK
	if(quantumRestante[cpu]==0 || current_pid(cpu)==IDLE_TASK){//si se acabo el quantumRestante desencolo al proximo y lo retorno, ademas encolo al current en la cola de ready de este procesador
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
//busco el cpu con la minima cantidad de proceso
for (int i = 0; i < cantCores; i++) {
	if(cantProc[i] < cantProc[cpuMinimo])
		cpuMinimo = i;
}

return cpuMinimo;
//<<<REMOVE END>>>
}

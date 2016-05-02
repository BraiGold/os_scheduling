#include <vector>
#include <queue>
#include "sched_no_mistery.h"
#include "basesched.h"
#include <list>
#include <map>
using namespace std;

SchedNoMistery::SchedNoMistery(vector<int> argn) {
  // MFQ recibe los quantums por parÃ¡metro
  for (int i = 0; i < argn.size()-1; i++) { //a cada core le doy su quantum
		quantumCola.push_back(argn[i+1]);
	}
  n=argn.size()-1;
  quantumRestante=quantumCola[0]-1;
  pid_cola.insert(std::pair<int,int>(IDLE_TASK,0));
  pid_quantumExtra.insert(std::pair<int,int>(IDLE_TASK,0));
}

void SchedNoMistery::load(int pid) {
  cola.push_back(pid);
  pid_cola.insert(std::pair<int,int>(pid,0));
  pid_quantumExtra.insert(std::pair<int,int>(pid,0));
}

void SchedNoMistery::unblock(int pid) {
cola.push_front(pid);
}

int SchedNoMistery::tick(int cpu, const enum Motivo m) {
  int r=IDLE_TASK;

  //seteo el quantumRestante

  if (m==EXIT || m==BLOCK){
    if (!cola.empty()){
      r=cola.front(); cola.pop_front();
    }else{
      r=IDLE_TASK;
    }
    if(m==BLOCK){
      pid_quantumExtra.at(current_pid(cpu))=quantumRestante;
      if(pid_cola.at(current_pid(cpu)) > 0)//si esta en la cola n que pase a la n-1 exepto si esta en la 0 que no cambie
        pid_cola.at(current_pid(cpu))--;
    }
    if (m==EXIT){
      pid_cola.erase(current_pid(cpu));
      pid_quantumExtra.erase(current_pid(cpu));
    }
    quantumRestante=quantumCola[pid_cola.at(r)] + pid_quantumExtra.at(r)-1;
    pid_quantumExtra.at(r)=0;
  }else{
    if(quantumRestante==0 || current_pid(cpu)==IDLE_TASK){
    //  quantumRestante=quantum[cpu]-1;
      if(!cola.empty()){
        r=cola.front(); cola.pop_front();
        quantumRestante=quantumCola[pid_cola.at(r)] + pid_quantumExtra.at(r)-1;
        pid_quantumExtra.at(r)=0;
        if(current_pid(cpu)!= IDLE_TASK){
          cola.push_back(current_pid(cpu));
          if(pid_cola.at(current_pid(cpu))< n-1)
            pid_cola.at(current_pid(cpu))++;
        }



      }else{
        r=current_pid(cpu);
        pid_cola.at(r)++;
        pid_quantumExtra.at(r)=0;
        quantumRestante=quantumCola[r];
      }

    }else{
        quantumRestante--;
        r=current_pid(cpu);
    }
  }
  return r;
}

int SchedNoMistery::next(void) {
  // Elijo el nuevo pid
}

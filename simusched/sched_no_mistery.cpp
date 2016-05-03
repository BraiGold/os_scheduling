#include <vector>
#include <queue>
#include "sched_no_mistery.h"
#include "basesched.h"
#include <list>
#include <map>
#include <iostream>
using namespace std;

SchedNoMistery::SchedNoMistery(vector<int> argn) {
  // MFQ recibe los quantums por parÃ¡metro
  queue<int> cola;
  quantumCola.push_back(1);//meto La Cola De 1
  colas.push_back(cola);
  
  for (int i = 0; i < argn.size()-1; i++) {
    quantumCola.push_back(argn[i+1]);
    colas.push_back(cola);
  }
  quantumRestante=quantumCola[0];
  n=quantumCola.size();
  pid_cola.insert(std::pair<int,int>(IDLE_TASK,0));
}

void SchedNoMistery::load(int pid) {
  colas[0].push(pid);
  pid_cola.insert(std::pair<int,int>(pid,0));
}

void SchedNoMistery::unblock(int pid) {
colas[pid_cola.at(pid)].push(pid);
}

int SchedNoMistery::tick(int cpu, const enum Motivo m) {
  int r=IDLE_TASK;

  if (m==EXIT || m==BLOCK || quantumRestante==0 || current_pid(cpu)==IDLE_TASK){


    bool unicaCosa=true;

    if(m==BLOCK && unicaCosa){
      if(pid_cola.at(current_pid(cpu)) > 0){
        pid_cola.at(current_pid(cpu))=pid_cola.at(current_pid(cpu))-1;
      }
      unicaCosa=false;
    }

    if(m==TICK && quantumRestante==0 && unicaCosa){
      if(pid_cola.at(current_pid(cpu))< n-1){
        pid_cola.at(current_pid(cpu))=pid_cola.at(current_pid(cpu))+1;
      }

      colas[pid_cola.at(current_pid(cpu))].push(current_pid(cpu));
      unicaCosa=false;
    }


    int numCola;

    for (numCola = 0; numCola < n; numCola++) {
      if(!colas[numCola].empty()){
        r=colas[numCola].front();colas[numCola].pop();
        break;
      }
    }



      if(m == TICK && r == IDLE_TASK && unicaCosa){
        r=current_pid(cpu);
        if(pid_cola.at(current_pid(cpu))< n-1){
          pid_cola.at(current_pid(cpu))=pid_cola.at(current_pid(cpu))+1;
        }
        unicaCosa=false;
      }



      quantumRestante=quantumCola[pid_cola.at(r)]-1;

      if(m==EXIT && unicaCosa){
          pid_cola.erase(current_pid(cpu));
      }
  }else{
      quantumRestante--;
      r=current_pid(cpu);
  }

  return r;

}

int SchedNoMistery::next(void) {
  // Elijo el nuevo pid
}

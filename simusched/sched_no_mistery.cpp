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
  quantumCola.push_back(1);//meto La Cola De quantum=1
  colas.push_back(cola);//creo la cola correspondiente al quantum =1

  for (int i = 0; i < argn.size()-1; i++) {//para cada parametro asigno su quantum y creo una cola, seteo el quantumRestante y guarda la cantidad de colas
    quantumCola.push_back(argn[i+1]);
    colas.push_back(cola);
  }
  quantumRestante=quantumCola[0];
  n=quantumCola.size();
  pid_cola.insert(std::pair<int,int>(IDLE_TASK,0));//meto el IDLE_TASK en la cola 0
}

void SchedNoMistery::load(int pid) {
  colas[0].push(pid);//meto al nuevo proceso en la primer cola
  pid_cola.insert(std::pair<int,int>(pid,0));
}

void SchedNoMistery::unblock(int pid) {
colas[pid_cola.at(pid)].push(pid);//encolo al proceso que se desbloquea en la cola a la que pertenece (que resulta ser 1 mas que l aque estaba antes)
}

int SchedNoMistery::tick(int cpu, const enum Motivo m) {
  int r=IDLE_TASK;//por defecto retorno IDLE_TASK

  if (m==EXIT || m==BLOCK || quantumRestante==0 || current_pid(cpu)==IDLE_TASK){//si es un bloqueo o exit o se acabo el quantumRestante determinare el proximo proceso a correr


    bool unicaCosa=true;//para que no ejecute como BLOCK si fue quantumRestante o EXIT U otra cosa.

    if(m==BLOCK && unicaCosa){//si fue BLOCK movelo en el diccionario a una cola mas a la izq (si se puede, si esta en la 0 dejalo ahi)
      if(pid_cola.at(current_pid(cpu)) > 0){
        pid_cola.at(current_pid(cpu))=pid_cola.at(current_pid(cpu))-1;
      }
      unicaCosa=false;
    }

    if(m==TICK && quantumRestante==0 && unicaCosa){//si se acabo el quantumRestante movelo a la cola de la derecha y encolalo
      if(pid_cola.at(current_pid(cpu))< n-1){
        pid_cola.at(current_pid(cpu))=pid_cola.at(current_pid(cpu))+1;
      }

      colas[pid_cola.at(current_pid(cpu))].push(current_pid(cpu));
      unicaCosa=false;
    }


    int numCola;

    for (numCola = 0; numCola < n; numCola++) {//busco la mejor cola (la de mas a la izq) que tenga a alguien y ese es el siguiente
      if(!colas[numCola].empty()){
        r=colas[numCola].front();colas[numCola].pop();
        break;
      }
    }



      if(m == TICK && r == IDLE_TASK && unicaCosa){//un caso borde para optimizar y no pasar por el idle si soy el unico
        r=current_pid(cpu);
        if(pid_cola.at(current_pid(cpu))< n-1){
          pid_cola.at(current_pid(cpu))=pid_cola.at(current_pid(cpu))+1;
        }
        unicaCosa=false;
      }



      quantumRestante=quantumCola[pid_cola.at(r)]-1;//reseteo quantumRestante con el quantum correspondiente a la cola

      if(m==EXIT && unicaCosa){//si es un exit borro la entrada de este procesos del diccionario
          pid_cola.erase(current_pid(cpu));
      }
  }else{//si aun no se consumio el quantum decrementar  quantumRestante y devolver el current
      quantumRestante--;
      r=current_pid(cpu);
  }

  return r;

}

int SchedNoMistery::next(void) {
  // Elijo el nuevo pid
}

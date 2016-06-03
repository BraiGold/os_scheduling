#include "tasks.h"
#include <iostream>     // std::cout
#include <algorithm>
#include <vector>


using namespace std;



void TaskCPU(int pid, vector<int> params) { // params: n
	uso_CPU(pid, params[0]); // Uso el CPU n milisegundos.
}

void TaskIO(int pid, vector<int> params) { // params: ms_pid, ms_io,
	uso_CPU(pid, params[0]); // Uso el CPU ms_pid milisegundos.
	uso_IO(pid, params[1]); // Uso IO ms_io milisegundos.
}

void TaskAlterno(int pid, vector<int> params) { // params: ms_pid, ms_io, ms_pid, ...
	for(int i = 0; i < (int)params.size(); i++) {
		if (i % 2 == 0) uso_CPU(pid, params[i]);
		else uso_IO(pid, params[i]);
	}
}

int randombis() {
	return rand() % 1000 + (rand() % 1000) * 1000 + (rand() % 1000) * 1000000;
}

void TaskConsola(int pid, vector<int> params) { // params: n, bmin, bmax
	time_t seconds;
	time(&seconds);
	srand((unsigned int) seconds);
	int r;
	for(int i = 0; i < params[0]; i++) {
		r = randombis() % (params[2] - params[1] + 1) + params[1];
		cout << r << endl;
		uso_IO(pid, r);
	}
	return; 
}

void TaskEj2(int pid, vector<int> params) { // params: dondeEmpiezoLlamadaBloqueante
	time_t seconds;
	time(&seconds);
	srand((unsigned int) seconds);
	uso_CPU(pid, params[0] - 1);  
	int r;
	r = randombis() % 4 + 1;
	uso_IO(pid, r);
	return;
}

bool estaEnElVector(int r, vector<int> randoms) {
	bool res = false;
	for (int i = 0; i < randoms.size(); i++) {
		if (randoms[i] == r) {
			res = true;
		}
	}
	return res;
} 

void TaskBatch(int pid, vector<int> params){ //params: total_cpu, cant_bloqueos
	time_t seconds;
	time(&seconds);
	srand((unsigned int) seconds);
	int total_cpu = params[0];
	int cant_bloqueos = params[1];
	int r;
	vector<int> randoms; //en cada posición va a estar en qué tiempo se tiene que bloquear
	r = randombis() % total_cpu + 1; //max = total_cpu; min = 1;
	randoms.push_back(r);
	for (int j = 1; j < cant_bloqueos; j++) {
		r = randombis() % total_cpu + 1; //max = total_cpu; min = 1;
		while(estaEnElVector(r, randoms)) {
			r = randombis() % total_cpu + 1; //max = total_cpu; min = 1;
		}
		randoms.push_back(r);
	}
	sort(randoms.begin(), randoms.end());
	cerr << "Tarea: " << pid << endl;
	for (int i = 0; i < randoms.size(); i++) {
		cerr << randoms[i] << endl;
	}

	uso_CPU(pid, randoms[0]-1);
	uso_IO(pid, 2);
	for(int i = 1; i < cant_bloqueos; i++){ //formula random = % (max - min + 1) + min
		uso_CPU(pid, randoms[i]-randoms[i-1]-1);
		uso_IO(pid, 2);
	}
	if (randoms[cant_bloqueos-1] != total_cpu) {
		uso_CPU(pid, total_cpu-randoms[cant_bloqueos-1]-1);
	}
	return;
}

void tasks_init(void) {
	/* Todos los tipos de tareas se deben registrar acá para poder ser usadas.
	 * El segundo parámetro indica la cantidad de parámetros que recibe la tarea
	 * como un vector de enteros, o -1 para una cantidad de parámetros variable. */
	register_task(TaskCPU, 1);
	register_task(TaskIO, 2);
	register_task(TaskAlterno, -1);
	register_task(TaskConsola, 3);
	register_task(TaskEj2, 1);
	register_task(TaskBatch, 2);
}

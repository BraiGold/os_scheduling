#include "tasks.h"


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
	int r;
	for(int i = 0; i < params[0]; i++) {
		r = randombis() % (params[2] - params[1] + 1) + params[1];
		uso_IO(pid, r);
	}
	//return ????? 
}

void TaskEj2(int pid, vector<int> params) { // params: dondeEmpiezoLlamadaBloqueante
	uso_CPU(pid, params[0]); //params[0] -1 ????? 
	int r;
	r = randombis() % (4 - 1 + 1) + 1;
	uso_IO(pid, r);
	//return???
}


void tasks_init(void) {
	/* Todos los tipos de tareas se deben registrar acá para poder ser usadas.
	 * El segundo parámetro indica la cantidad de parámetros que recibe la tarea
	 * como un vector de enteros, o -1 para una cantidad de parámetros variable. */
	register_task(TaskCPU, 1);
	register_task(TaskIO, 2);
	register_task(TaskAlterno, -1);
	register_task(TaskConsola, 3);
	register_task(TaskEj2, 1)
}
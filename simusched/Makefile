export LC_ALL=C
CXXFLAGS= -Wall -pedantic -g -ggdb
LDFLAGS= -lpthread

OBJS=main.o simu.o basesched.o basetask.o tasks.o sched_rr.o sched_fcfs.o sched_rr2.o sched_no_mistery.o
MAIN=simusched

.PHONY: all clean new
all: $(MAIN)

$(MAIN): $(OBJS) sched_mistery.o 
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp %.h basesched.h
basesched.o: basesched.cpp basesched.h
basetask.o: basetask.cpp basetask.h
main.o: main.cpp simu.h basetask.h basesched.h tasks.h sched_fcfs.h \
 sched_rr.h sched_rr2.h
simu.o: simu.cpp simu.h basetask.h basesched.h
simusched.o: simusched.cpp basetask.h basesched.h tasks.h
tasks.o: tasks.cpp tasks.h basetask.h

clean:
	rm -f $(OBJS) $(MAIN)

new: clean all

ejercicio1: ej1/lote1.tsk 
	./simusched ej1/lote1.tsk 1 1 1 SchedFCFS | python graphsched.py > ej1/lote1.png 

ejercicio2: ej2/lote1.tsk
	./simusched ej2/lote1.tsk 1 5 1 SchedFCFS | python graphsched.py > ej2/lote1-1.png
	./simusched ej2/lote1.tsk 2 5 5 SchedFCFS | python graphsched.py > ej2/lote1-2.png
	./simusched ej2/lote1.tsk 4 5 5 SchedFCFS | python graphsched.py > ej2/lote1-4.png

ejercicio3: ej3/lote1.tsk
	./simusched ej3/lotei.tsk 1 1 1 SchedFCFS | python graphsched.py > ej3/lote1.png

ejercicio5: ej5/lote1.tsk
	./simusched ej5/lote1.tsk 1 2 1 SchedRR 2 | python graphsched.py > ej5/lote1-q2.png
	./simusched ej5/lote1.tsk 1 2 1 SchedRR 10 | python graphsched.py > ej5/lote1-q10.png
	./simusched ej5/lote1.tsk 1 2 1 SchedRR 30 | python graphsched.py > ej5/lote1-q30.png

ejercicio6: ej6/lote1.tsk
	./simusched ej6/lote1.tsk 1 2 1 SchedFCFS | python graphsched.py > ej6/lote1.png

ejercicio7: ej7/lote1.tsk ej7/lote2.tsk ej7/lote3.tsk
	./simusched ej7/lote1.tsk 1 2 1 SchedMistery 3 9 5| python graphsched.py > ej7/lote1.png
	./simusched ej7/lote2.tsk 1 2 1 SchedMistery 3 9 5| python graphsched.py > ej7/lote2.png
	./simusched ej7/lote3.tsk 1 2 1 SchedMistery 3 9 5| python graphsched.py > ej7/lote3.png

ejercicio8: ej8/lote1.tsk ej8/lote2.tsk
	./simusched ej8/lote1.tsk 2 2 2 SchedRR 5 5 | python graphsched.py > ej8/lote1-RR.png
	./simusched ej8/lote1.tsk 2 2 2 SchedRR2 5 5 | python graphsched.py > ej8/lote1-RR2.png
	./simusched ej8/lote2.tsk 2 2 10 SchedRR 7 7 | python graphsched.py > ej8/lote2-RR.png 
	./simusched ej8/lote2.tsk 2 2 10 SchedRR2 7 7 | python graphsched.py > ej8/lote2-RR2.png 








### CPP compiler wrapper
CXX=mpicxx

### Optimization flags
FFLAGS=-fopenmp

all: pi_openmp_parallel.exec

pi_openmp_parallel.exec:
	$(CXX) $(FFLAGS) pi_openmp_parallel.cpp -o pi_openmp_parallel.exec

clean:
	rm -f *.exec

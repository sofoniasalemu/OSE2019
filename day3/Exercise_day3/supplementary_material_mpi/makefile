### CPP compiler wrapper
CXX=mpicxx

####  Optimization flag
FFLAGS=-03

#########################
all:broadcast.exec allreduce.exec scatter.exec

########################

broadcast.exec: broadcast.cpp
	$(CXX)  broadcast.cpp -o broadcast.exec

allreduce.exec: allreduce.cpp
	$(CXX)  allreduce.cpp -o allreduce.exec

scatter.exec: scatter.cpp
	$(CXX)  scatter.cpp -o scatter.exec

clean:
	rm -f *.exec

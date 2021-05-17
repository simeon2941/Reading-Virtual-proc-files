
# Compiler variables
CCFLAGS = -Wall

# Rule to link object code files to create executable file
assignment1.exe: assignment1.cc
	g++ $(CCFLAGS) assignment1.cc -o assignment1.exe

clean:
	-rm *.o assignment1.exe


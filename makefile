# Compiler to use
CC = g++

# Compiler flags
CFLAGS = -Wall -Wextra -g
	# -g debugging information

# Include paths for header files
INCLUDES = -I. 
	# -I. looks in current directory for header files

# Paths to required libraries -L option
LFLAGS = 

# The specific libraries that project depends on -l option
LIBS = 

# All source files
SRCS = Driver.cpp Weather.cpp 

# All object files
OBJS = $(SRCS:.cpp=.o)
	# Uses macro to replace extension of all source files

# name of executable
MAIN = weather

# following section is generic

all: $(MAIN)

$(MAIN): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS) $(LFLAGS) $(LIBS)	

# Automatically builds all object files from source files
# -c option compiles but does not link (create object files)
# -o is output filename
.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@

# This is used in case there is a file named clean 
# removes all object files and executable
.PHONY: clean
clean:
	rm *.o $(MAIN)


CC = gcc -std=c99 -g -ggdb3

# Flags and other libraries
override CFLAGS += -Wall -Wextra -pedantic -O$(O) -I$(INCLUDES)
LDFLAGS =
LIBS =
INCLUDES = include

####### Automatic dependency magic #######
# Set-up dependency directory
DEPSDIR := .deps
BUILDSTAMP := $(DEPSDIR)/rebuildstamp
DEPFILES := $(wildcard $(DEPSDIR)/*.d)
ifneq ($(DEPFILES),)
include $(DEPFILES)
endif
DEPCFLAGS = -MD -MF $(DEPSDIR)/$*.d -MP

# Dependency compilation
ifneq ($(DEP_CC),$(CC) $(CFLAGS) $(DEPCFLAGS) $(O))
DEP_CC := $(shell mkdir -p $(DEPSDIR); echo >$(BUILDSTAMP); echo "DEP_CC:=$(CC) $(CFLAGS) $(DEPCFLAGS) $(O)" >$(DEPSDIR)/_cc.d)
endif

%.o : %.c $(BUILDSTAMP)
	$(CC) $(CFLAGS) $(DEPCFLAGS) -O$(O) -o $@ -c $<

unit_tests: unit_tests.o graph.o

# Hum...actually this is not working, but "make bfs" is...
bfs: BFS.o graph.o
	gcc graph.c  BFS.c -o BFS.o -lm

clean:
	-rm -f *.o
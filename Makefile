#-------------------------------------------------------------
# Makefile for cmc++ library
#-------------------------------------------------------------
include ./root_dir.mk # must be included first
include ./options.mk
#-------------------------------------------------------------
# Source files
PROJECT_SRCS = scheduler/cmdargs.cpp 
PROJECT_SRCS+= scheduler/inputparams.cpp 
PROJECT_SRCS+= scheduler/taskparams.cpp 
PROJECT_SRCS+= scheduler/worker.cpp 
PROJECT_SRCS+= scheduler/master_scheduler.cpp
PROJECT_SRCS+= scheduler/scheduler.cpp
PROJECT_SRCS+= lattice/lattice.cpp
PROJECT_SRCS+= kspace/scatterer.cpp
PROJECT_SRCS+= kspace/valley.cpp
PROJECT_SRCS+= kspace/band.cpp
PROJECT_SRCS+= particle/particle.cpp
PROJECT_SRCS+= simulator/physical.cpp
PROJECT_SRCS+= simulator/random.cpp simulator/system.cpp
PROJECT_SRCS+= simulator/simulator.cpp
PROJECT_SRCS+= main.cpp
#-------------------------------------------------------------
# Headers
PROJECT_HDRS=scheduler/optionparser.h scheduler/cmdargs.h \
         scheduler/inputparams.h scheduler/worker.h scheduler/task.h \
         scheduler/scheduler.h \
         lattice/constants.h lattice/matrix.h lattice/lattice.h \
	 kspace/scatterer.h kspace/valley.h kspace/band.h \
	 simulator/physical.h simulator/particle.h \
	 simulator/random.h simulator/system.h simulator/simulator.h \
	 montecarlo.h 
#         observable/mcdata.h observable/observables.h \
#         montecarlo/random.h montecarlo/sitebasisstate.h \
#	 montecarlo/observable_operator.h montecarlo/simulator.h \
	 simulation.h
#-------------------------------------------------------------
# Target
TAGT=a.out

# Put all auto generated stuff to this build dir.
ifeq ($(BUILD_DIR), $(CURDIR))
  $(error In-source build is not allowed, choose another build directory)
endif

# All .o files go to BULD_DIR
OBJS=$(patsubst %.cpp,$(BUILD_DIR)/%.o,$(PROJECT_SRCS))
# GCC/Clang will create these .d files containing dependencies.
DEPS=$(patsubst %.o,%.d,$(OBJS)) 
# compiler flags
CXXFLAGS = $(PROJECT_INCLUDEFLAGS) $(OPTIMIZATIONS) 

#PROJECT_INCLDIR=$(PROJECT_INCLUDE)/cmc
#INCL_HDRS = $(addprefix $(PROJECT_INCLDIR)/, $(PROJECT_HDRS))

.PHONY: all
all: $(TAGT) #$(INCL_HDRS)

$(TAGT): $(OBJS)
	$(PROJECT_CXX) -o $(TAGT) $(OBJS) $(BOOST_LDFLAGS) $(BOOST_LIBS) 

%.o: %.cpp
	$(PROJECT_CXX) -c $(CXXBFLAGS) -o $@ $<


# Include all .d files
-include $(DEPS)

$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	@echo "$(PROJECT_CXX) -c $(PROJECT_CXXBFLAGS) -o $(@F) $(<F)"
	@$(PROJECT_CXX) -MMD -c $(PROJECT_CXXBFLAGS) -o $@ $<

$(PROJECT_INCLDIR)/%.h: %.h 
	@mkdir -p $(@D)
	@echo "Copying $< to 'include'" 
	@cp -f $< $@

# installation
#prefix = ../install#/usr/local
#libdir = $(prefix)/lib
#includedir = $(prefix)/include/cmc++

.PHONY: install
install:	
	@echo "Already installed in $(PROJECT_LIBDIR) and $(PROJECT_INCLDIR)" 

.PHONY: clean
clean:	
	@echo "Removing temporary files in the build directory"
	@rm -f $(OBJS) $(DEPS) 
	@echo "Removing $(TAGT)"
	@rm -f $(TAGT) 

.PHONY: bclean
bclean:	
	@echo "Removing temporary files in the build directory"
	@rm -f $(OBJS) $(DEPS) 

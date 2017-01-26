# User Configurable Options
#PROJECT_ROOT=/Users/amedhi/projects/Codes/ParticleMC/src

# Building the cmc++ lib
#-------------------------------------------------------------
# 1. Set compiler option
PROJECT_CXX=clang++ -std=c++11 # Clang compiler 
#PROJECT_CXX=g++ -std=c++11 # GNU GCC compiler

ifndef PROJECT_CXX
$(error Makefile variable PROJECT_CXX not defined in options.mk; please define it.)
endif
#-------------------------------------------------------------
# 2. Compile flag options
# Flags to give the compiler for "release mode"
PROJECT_OPTFLAGS=-Wall -O3
# Flags to give the compiler for "debug mode"
PROJECT_DEBUGFLAGS=-DDEBUG_MODE -g -Wall -pedantic

#-------------------------------------------------------------
# 3. Boost and Eigen library
# Flags to give the compiler for "release mode"
BOOST_INCLUDE=-I/usr/local/include
EIGEN_INCLUDE=-I/usr/local/include
#BOOST_LIBS=-lboost_system -lboost_filesystem
#BOOST_LDFLAGS=-L/usr/local/lib

INCLUDE = $(BOOST_INCLUDE)
ifneq ($(BOOST_INCLUDE), $(EIGEN_INCLUDE))
INCLUDE += $(EIGEN_INCLUDE)
endif

PROJECT_CXXBFLAGS= $(PROJECT_OPTFLAGS) $(INCLUDE)
#-------------------------------------------------------------
# 4. Where to put the 'cmc' library & the includes
PREFIX=$(PROJECT_ROOT)
BUILD_DIR=$(PREFIX)/build
PROJECT_LIBDIR=$(PREFIX)/lib
PROJECT_INCLUDE=$(PREFIX)/include
PROJECT_CXXFLAGS= $(PROJECT_OPTFLAGS) $(INCLUDE) -I$(PROJECT_INCLUDE)
PROJECT_LDFLAGS=$(BOOST_LDFLAGS) -L$(PROJECT_LIBDIR)
PROJECT_LIBS=$(BOOST_LIBS) -lcmc++
#-------------------------------------------------------------

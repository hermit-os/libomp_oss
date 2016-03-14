NEWLIB = ../x86/x86_64-hermit
MAKE = make
ARFLAGS_FOR_TARGET = rsv
CFLAGS_DEBUG = #-D KMP_DEBUG
CFLAGS_ADD =  -Isrc -Isrc/thirdparty/safeclib -Isrc/thirdparty/ittnotify -D INTEL_NO_ITTNOTIFY_API -D USE_ITT_NOTIFY=0 -D USE_ITT_BUILD=1 -D NDEBUG -D KMP_ARCH_STR="\"Intel(R) 64\"" -pthread -D KMP_USE_HWLOC=0 -D KMP_USE_ASSERT -D BUILD_I8 -D BUILD_TV=0 -D KMP_LIBRARY_FILE=\"libiomp5.so\" -D KMP_VERSION_MAJOR=5 -D CACHE_LINE=64 -D KMP_ADJUST_BLOCKTIME=0 -D BUILD_PARALLEL_ORDERED -D KMP_ASM_INTRINS -D KMP_USE_INTERNODE_ALIGNMENT=0 -D KMP_USE_VERSION_SYMBOLS -D USE_CBLKDATA -D KMP_GOMP_COMPAT -D KMP_NESTED_HOT_TEAMS -D KMP_USE_ADAPTIVE_LOCKS=0 -D KMP_DEBUG_ADAPTIVE_LOCKS=0 -D KMP_STATS_ENABLED=0 -D OMP_50_ENABLED=0 -D OMP_41_ENABLED=0 -D OMP_40_ENABLED=1 -D KMP_TDATA_GTID  -D _KMP_BUILD_TIME="\"$(date)\""
GASFLAGS_ADD = -x assembler-with-cpp
CP = cp
C_source =  $(wildcard src/kmp_*.c src/thirdparty/safeclib/*.c src/z_Linux_util.c)
CPP_source = $(wildcard src/kmp_*.cpp)
S_source = $(wildcard src/*.s)
NAME = libiomp.a
OBJS = $(C_source:.c=.o) $(CPP_source:.cpp=.o) $(S_source:.s=.o)

#
# Prettify output
V = 0
ifeq ($V,0)
	Q = @
	P = > /dev/null
endif

# other implicit rules
%.o : %.c
	@echo [CC] $@
	$Q$(CC_FOR_TARGET) -c $(CFLAGS_FOR_TARGET) $(CFLAGS_ADD) $(CFLAGS_DEBUG) -x c++ -std=c++11 -fno-exceptions -Wsign-compare -o $@ $<

%.o : %.s
	@echo [CC] $@
	$Q$(CC_FOR_TARGET) -c $(CFLAGS_FOR_TARGET) $(CFLAGS_ADD) $(CFLAGS_DEBUG) -x assembler-with-cpp -o $@ $<

%.o : %.cpp
	@echo [CPP] $@
	$Q$(CXX_FOR_TARGET) -c $(CXXFLAGS_FOR_TARGET) $(CFLAGS_ADD) $(CFLAGS_DEBUG) -o $@ $<

default: all

all: $(NAME)

$(NAME): $(OBJS)
	$Q$(AR_FOR_TARGET) $(ARFLAGS_FOR_TARGET) $@ $(OBJS)
	$Q$(CP) $@ $(NEWLIB)/lib
	$Q$(CP) libgomp.spec $(NEWLIB)/lib
	$Q$(CP) src/omp.h $(NEWLIB)/include
	
clean:
	@echo Cleaning examples
	$Q$(RM) $(NAME) src/*.o src/thirdparty/safeclib/*.o

veryclean:
	@echo Propper cleaning examples
	$Q$(RM) $(NAME) src/*.o src/thirdparty/safeclib/*.o

depend:
	$Q$(CC_FOR_TARGET) -MM $(CFLAGS_FOR_TARGET) $(CFLAGS_ADD) src/kmp_*.c src/thirdparty/safeclib/*.c > Makefile.dep

-include Makefile.dep
# DO NOT DELETE

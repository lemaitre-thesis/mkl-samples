# -------------------- #
# -- poiAV Makefile -- #
# -------------------- #

# -- Lile list ----------
FILE = main.c mkl-main.c mkl-cholesky.c

# -- Paths ----------
SRC_PATH = src
OBJ_PATH = obj
EXE_PATH = exe
INC_PATH = include

LIB_LIB_PATH = -lmkl_rt -lrt -static-libgcc -static-libstdc++
LIB_INC_PATH = 

# -- Macros ----------
CC = gcc
#CC = icc
AR = ar -rc

# -- Make arguments ----------
ifndef DEBUG
	DEBUG = 0
endif

ifneq ($(if $(DEBUG),$(strip $(DEBUG)),0),0)
	DEBUG_SUFFIX = _dbg
else
	DEBUG_SUFFIX = 
endif

SUFFIX = $(DEBUG_SUFFIX)

# -- Flags ----------
C_VEC_FLAGS = -ftree-vectorize -fopt-info-vec
#C_FP_FLAGS = -fassociative-math -fno-math-errno -fno-trapping-math -fno-signed-zeros -fno-signaling-nans
#C_FP_FLAGS = -fassociative-math -fno-trapping-math -fno-signed-zeros -fno-math-errno -ffinite-math-only -fno-rounding-math -fno-signaling-nans
C_DEBUG_FLAGS = -std=c99 -O0 -g
C_OPTIMISATION_FLAGS = -std=c99 -O3
C_ARCH_FLAGS = -march=native
C_INC_FLAGS = -I$(INC_PATH)

# -- Options ----------
C_OPTIONS_FLAGS = $(C_DOUBLE_FLAGS)

ifneq ($(if $(DEBUG),$(strip $(DEBUG)),0),0)
	CFLAGS  = $(C_DEBUG_FLAGS)        $(C_OPENMP_FLAGS) $(C_OPTIONS_FLAGS) $(C_ARCH_FLAGS) $(C_INC_FLAGS) $(LIB_INC_PATH)
	LDFLAGS = $(C_DEBUG_FLAGS)        $(C_OPENMP_FLAGS) $(C_OPTIONS_FLAGS) $(C_ARCH_FLAGS) $(C_INC_FLAGS) $(LIB_LIB_PATH)
else
	CFLAGS  = $(C_OPTIMISATION_FLAGS) $(C_OPENMP_FLAGS) $(C_OPTIONS_FLAGS) $(C_ARCH_FLAGS) $(C_INC_FLAGS) $(LIB_INC_PATH)
	LDFLAGS = $(C_OPTIMISATION_FLAGS) $(C_OPENMP_FLAGS) $(C_OPTIONS_FLAGS) $(C_ARCH_FLAGS) $(C_INC_FLAGS) $(LIB_LIB_PATH)
endif

# -- Final product ----------
PRODUCT   = mkl-sample$(SUFFIX)

# -- src and obj List ----------
SRC = $(addprefix ${SRC_PATH}/, $(FILE))
OBJ = $(addprefix ${OBJ_PATH}/, $(addsuffix $(SUFFIX).o, $(basename $(FILE))))

# -- Base rules ----------
$(OBJ_PATH)/%$(SUFFIX).o : $(SRC_PATH)/%.c
	$(CC) $(CFLAGS) -c $< -o $@
   
#-----Main rule ----------
$(EXE_PATH)/$(PRODUCT): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS) $(OPTFLAGS) $(CFG) $(INC) 

# -- Other stuff ----------
depend:
	makedepend $(CFLAGS) -Y $(SRC)

clean:
	rm -f $(OBJ_PATH)/*
	rm -f $(EXE_PATH)/*

compile: $(EXE_PATH)/$(PRODUCT)
run: $(EXE_PATH)/$(PRODUCT)
	$(EXE_PATH)/$(PRODUCT)

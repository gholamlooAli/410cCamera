TARGET = conformal

OBJS = capabilities.o  device.o  esShader.o esUtil.o conformal.o 
       

LDFLAGS = -L/usr/X11R6/lib -g -lGLESv2 -lEGL  -lm -lX11 

# profiling, debugging
OPT = -g
CPU_OPT =

# set CPU_OPT based on the contents of /proc/cpuinfo. in particular pay 
# attention to the model name and flags. compare against the listing for 
# cpu type on the gcc info pages entry for cpu type 

CPU_OPT = -march=native #nocona

DFLAGS = -DGL_CHECK

CFLAGS = -Wformat=2 -Wswitch-default -Wswitch-enum \
         -Wunused-parameter -Wextra -Wshadow \
         -Wbad-function-cast -Wsign-compare -Wstrict-prototypes \
         -Wmissing-prototypes -Wmissing-declarations -Wunreachable-code \
	 -ffast-math  $(PROFILE) $(OPT) #$(CPU_OPT)

$(TARGET): $(OBJS)
	cc  -o $(TARGET) $(LDFLAGS) $(OBJS)  $(PROFILE) $(OPT)

%.o : %.c
	cc -c $(CFLAGS) $(DFLAGS) $<


flow:
	cflow $(OBJS:.o=.c)

lint:
	cc -O2  $(DFLAGS) -Wuninitialized -Wextra -fsyntax-only \
	         -pedantic  $(OBJS:.o=.c)

clean:
	@rm $(OBJS)

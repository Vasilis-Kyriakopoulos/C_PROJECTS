HEADER=header.h
PROGRAM=Project3
MAIN=Project3.c 
MIRROR=mirror.c
ROTATE=rotate.c
NOISE=noise.c
MAINO=Project3.o 
MIRRORO=mirror.o
ROTATEO=rotate.o
NOISEO=noise.o
COMP=gcc 
k=-c
t=-o



$(PROGRAM):$(MAINO) $(MIRRORO) $(ROTATEO) $(NOISEO)
	$(COMP) $(t) $(PROGRAM) $(MAINO) $(MIRRORO) $(ROTATEO) $(NOISEO)

$(MAINO):$(MAIN) $(HEADER)
	$(COMP) $(k) $(MAIN)
$(MIRRORO):$(MIRROR) $(HEADER)
	$(COMP) $(k) $(MIRROR) 
$(ROTATEO):$(ROTATE) $(HEADER)
	$(COMP) $(k) $(ROTATE) 
$(NOISEO):$(NOISE) $(HEADER)
	$(COMP) $(k)  $(NOISE) 

 






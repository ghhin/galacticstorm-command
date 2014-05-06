
CXX	= xc8
CHIP	= 12F683
MAIN	= gs_command
SRCS	= $(MAIN).c

DEST	= funclist $(MAIN).hex $(MAIN).hxl $(MAIN).p1 $(MAIN).sym $(MAIN).cof $(MAIN).lst \
	  $(MAIN).rlf $(MAIN).d $(MAIN).obj $(MAIN).pre $(MAIN).sdb

all: $(MAIN).p1 $(MAIN).hex

$(MAIN).p1: $(SRCS)
	$(CXX) --pass1 --chip=$(CHIP) -G --asmlist --double=24 --float=24 --opt=default,+asm,-asmfile,+speed,-space,-debug,9 --addrqual=ignore -P -N255 --warn=0 --summary=default,-psect,-class,+mem,-hex,-file --runtime=default,+clear,+init,-keep,-no_startup,+osccal,-resetbits,-download,-stackcall,+clib $(SRCS)

$(MAIN).hex: $(MAIN).p1
	$(CXX) --chip=$(CHIP) -G --asmlist --double=24 --float=24 --opt=default,+asm,-asmfile,+speed,-space,-debug,9 --addrqual=ignore -P -N255 --warn=0 --summary=default,-psect,-class,+mem,-hex,-file --runtime=default,+clear,+init,-keep,-no_startup,+osccal,-resetbits,-download,-stackcall,+clib $(MAIN).p1

clean:
	rm -f $(DEST)


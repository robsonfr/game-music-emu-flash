export TOPDIR	:=	$(CURDIR)
 
export DATESTRING	:=	$(shell date +%Y)$(shell date +%m)$(shell date +%d)

default: release

all: release dist

lib:
	@[ -d $@ ] || mkdir -p $@

release: lib
	make -C build BUILD=release

debug: lib
	make -C build BUILD=debug

clean:
	make -C build clean

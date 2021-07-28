.PHONY: all build install check clean distclean
all: build
	ninja -C $< $@

install: all
	ninja -C build $@

build:
	mkdir -p $@
	cmake -B $@ -S . -G Ninja -D SNMP_PP_LOGGING=NO -D CMAKE_CXX_COMPILER_LAUNCHER=ccache

check: build/compile_commands.json
	# run-clang-tidy.py -p build -checks='-*,cppcoreguidelines-init-variables' -j1 -fix src
	# run-clang-tidy.py -p build -checks='-*,cppcoreguidelines-explicit-virtual-functions' -j1 -fix src
	run-clang-tidy.py -p build src

clean: build
	rm -f include/snmp_pp/config_snmp_pp.h
	rm -f $</*.h
	-ninja -C $< clean

distclean: clean
	rm -rf build
#

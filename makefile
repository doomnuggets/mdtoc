local: mdtoc.c lib/*.h
	gcc mdtoc.c lib/*.h -o mdtoc

install: mdtoc.c lib/*.h
	sudo gcc mdtoc.c lib/*.h -o /usr/bin/mdtoc

uninstall:
	sudo rm -f /usr/bin/mdtoc

debug: mdtoc.c lib/*.h
	gcc mdtoc.c lib/*.h -g

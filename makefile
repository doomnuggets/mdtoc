local: mdtoc.c lib/*.h
	gcc mdtoc.c -std=c99 -o mdtoc

install: mdtoc.c lib/*.h
	gcc mdtoc.c -std=c99 -o /usr/bin/mdtoc

uninstall:
	rm -f /usr/bin/mdtoc

debug: mdtoc.c lib/*.h
	gcc mdtoc.c -std=c99 -g

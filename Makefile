TARGETS+=libllist.so
libllist.so: llistmacro.h _llist.h llist.c llist_l.c llscan.c
	cc -shared -o libllist.so llist.c llist_l.c llscan.c

TARGETS+=llist.o
llist.o: llist.c llistmacro.h _llist.h

TARGETS+=llist_l.o
llist_l.o: llist_l.c llistmacro.h _llist.h

TARGETS+=llscan.o
llscan.o: llscan.c llistmacro.h _llist.h

TARGETS+=libllist.a
libllist.a: llist.o llist_l.o llscan.o
	ar -rcs libllist.a llist.o llist_l.o llscan.o

TARGETS+=ltest
ltest: ltest.c llist.h libllist.a
	clang -o ltest ltest.c -L. -lllist

.PHONY: lib
lib: libllist.so

.PHONY: test
test: ltest
	./ltest

.PHONY: clean
clean:
	rm -f ${TARGETS}

.PHONY: push
push:
	git push -u origin master

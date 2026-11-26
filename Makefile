CC?=		cc
CFLAGS?=	-O2 -Wall -Wextra -std=c99
PREFIX?=	/usr/local
BINDIR?=	$(PREFIX)/bin

all: allswap-validator

allswap-validator: allswap-validator.c
	$(CC) $(CFLAGS) -o allswap-validator allswap-validator.c

install: allswap-validator
	mkdir -p $(DESTDIR)$(BINDIR)
	install -m 0755 allswap-validator $(DESTDIR)$(BINDIR)/allswap-validator

clean:
	rm -f allswap-validator

.PHONY: all install clean

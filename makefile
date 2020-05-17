CC = gcc
CFLAGS = -w

TARGET = main

BINDIR = bin
OBJDIR = build
SRCDIR = src
LIBNME = lib.a
LIBOBJ = $(OBJDIR)/sc.o $(OBJDIR)/mt.o $(OBJDIR)/bc.o $(OBJDIR)/rk.o $(OBJDIR)/graphics.o $(OBJDIR)/alu.o

all: folders $(OBJDIR)/$(LIBNME) $(BINDIR)/$(TARGET)

folders:
	if ! test -d $(OBJDIR); then mkdir -p $(OBJDIR); fi
	if ! test -d $(BINDIR); then mkdir -p $(BINDIR); fi

$(BINDIR)/$(TARGET): $(OBJDIR)/$(TARGET).o
	$(CC) $^ -o $@ $(OBJDIR)/$(LIBNME) -lm

$(OBJDIR)/$(LIBNME): $(LIBOBJ)
	ar rc $@ $^
	ranlib $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(SRCDIR)/%.h
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJDIR)/$(TARGET).o: $(SRCDIR)/$(TARGET).c $(LIBOBJ)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	if test -d $(OBJDIR); then rm -r $(OBJDIR); fi
	if test -d $(BINDIR); then rm -r $(BINDIR); fi

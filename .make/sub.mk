.PHONY:all
all:debug

MAKESUBDIR = @for i in $(SUBFOLDERS); do echo $$i:; $(MAKE) -C $$i $@ --no-print-directory | sed 's/^/  /'; done;

debug:
	$(MAKESUBDIR)

release:
	$(MAKESUBDIR)

clean:
	$(MAKESUBDIR)

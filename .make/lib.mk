.PHONY:debug
debug: export _CFLAGS := $(CFLAGS) $(DEBUGCFLAGS)
debug: export _LDFLAGS := $(LDFLAGS) $(DEBUGLDFLAGS)
debug: export _DEPEND:= $(DEPEND) $(DEBUGDEPEND)
debug: export _LIBFOLDER :=$(LIBFOLDER)/debug
debug: export _OBJFOLDER :=$(OBJFOLDER)/debug
debug:
	@make all --no-print-directory

.PHONY:release
release: export _CFLAGS := $(CFLAGS) $(RELEASECFLAGS)
release: export _LDFLAGS := $(LDFLAGS) $(RELEASELDFLAGS)
release: export _DEPEND:= $(DEPEND) $(RELEASEDEPEND)
release: export _LIBFOLDER :=$(LIBFOLDER)/release
release: export _OBJFOLDER :=$(OBJFOLDER)/release
release:
	@make all --no-print-directory

.PHONY:all
all:dirs $(_LIBFOLDER)/$(LIB)

OBJ = $(addprefix $(_OBJFOLDER)/,$(SRC:%.cpp=%.o))

DEPS = $(OBJ:.o=.d)
-include $(DEPS)

DIRS = $(sort $(subst $(SRCFOLDER)/,,$(dir $(SRC))))
dirs:
	@for i in $(DIRS); do mkdir -p $(_OBJFOLDER)/$$i; done;
	@mkdir -p $(_LIBFOLDER)

$(_LIBFOLDER)/$(LIB):$(OBJ) $(_DEPEND)
	ar rcs $@ $(OBJ)

$(_OBJFOLDER)/%.o:$(SRCFOLDER)/%.cpp
	@echo "$< -> $@ : $(_CFLAGS)"
	@$(CC) $(_CFLAGS) -MMD -c $< -o $@

.PHONY:clean
clean:
	@rm -rf lib/** build/**

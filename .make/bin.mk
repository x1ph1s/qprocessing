PHONY:debug
debug: export _CFLAGS := $(CFLAGS) $(DEBUGCFLAGS)
debug: export _LDFLAGS := $(LDFLAGS) $(DEBUGLDFLAGS)
debug: export _DEPEND:= $(DEPEND) $(DEBUGDEPEND)
debug: export _BINFOLDER :=$(BINFOLDER)/debug
debug: export _OBJFOLDER :=$(OBJFOLDER)/debug
debug:
	@make all --no-print-directory

.PHONY:release
release: export _CFLAGS := $(CFLAGS) $(RELEASECFLAGS)
release: export _LDFLAGS := $(LDFLAGS) $(RELEASELDFLAGS)
release: export _DEPEND:= $(DEPEND) $(RELEASEDEPEND)
release: export _BINFOLDER :=$(BINFOLDER)/release
release: export _OBJFOLDER :=$(OBJFOLDER)/release
release:
	@make all --no-print-directory

.PHONY:all
all:dirs $(_BINFOLDER)/$(BIN)

OBJ = $(addprefix $(_OBJFOLDER)/,$(SRC:%.cpp=%.o))
DEPS = $(OBJ:.o=.d)

-include $(DEPS)

DIRS = $(sort $(subst $(SRCFOLDER)/,,$(dir $(SRC))))
dirs:
	@for i in $(DIRS); do mkdir -p $(_OBJFOLDER)/$$i; done;
	@mkdir -p $(_BINFOLDER)

$(_BINFOLDER)/$(BIN):$(OBJ) $(_DEPEND)
	@$(CC) $(OBJ) -o $@ $(_LDFLAGS)
	@echo "$(OBJ) -> $@ : $(_LDFLAGS)"

$(_OBJFOLDER)/%.o:$(SRCFOLDER)/%.cpp
	@$(CC) $(_CFLAGS) -MMD -c $< -o $@
	@echo "$< -> $@ : $(_CFLAGS)"

.PHONY:clean
clean:
	@rm -rf bin/** build/**

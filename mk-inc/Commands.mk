
.PHONY += compile run re rerun clear clean fclear fclean

# Default target entry
# NOTE: We call this Makefile target or Makefile.Android target
compile: $(PROJECT_NAME)
# @$(MAKE) $(MAKEFILE_PARAMS)
	@printf "Compilation finished\n"

# Project target defined by PROJECT_NAME
$(PROJECT_NAME): $(OBJS)
	@$(CC) -o $(PROJECT_NAME)$(EXT) $(OBJS) $(CFLAGS) $(INCLUDE_PATHS) $(LDFLAGS) $(LDLIBS) -D$(PLATFORM)

# Compile source files
# NOTE: This pattern will compile every module defined on $(OBJS)
# %.o: %.c
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_SUB_DIRS)
	@$(CC) -c $< -o $@ $(CFLAGS) $(INCLUDE_PATHS) -D$(PLATFORM)

run: compile
	@printf "Launching $(PROJECT_NAME)...\n"
	@./$(PROJECT_NAME)$(EXT)
	@printf "Project executed\n"

re: clean compile

rerun: re run

# Clean all .o files
clear: clean
clean:
	@printf "Cleaning .o files...\n"
	@rm -rf $(OBJ_DIR)
ifeq ($(PLATFORM),PLATFORM_DESKTOP)
ifeq ($(PLATFORM_OS),WINDOWS)
	@del *.o *.exe /s
else ifeq ($(PLATFORM_OS),LINUX)
	@find -type f -executable | xargs file -i | grep -E 'x-object|x-archive|x-sharedlib|x-executable' | rev | cut -d ':' -f 2- | rev | xargs rm -fv
else ifeq ($(PLATFORM_OS),OSX)
	@find . -type f -perm +ugo+x -delete
	@rm -f *.o
endif
else ifeq ($(PLATFORM),PLATFORM_RPI)
	@find . -type f -executable -delete
	@rm -fv *.o
else ifeq ($(PLATFORM),PLATFORM_WEB)
	@del *.o *.html *.js
endif
	@printf "Files cleaned\n"

# Clean all .o files and executable
fclear: fclean
fclean: clean
	@printf "Cleaning executable...\n"
	@rm -f $(PROJECT_NAME)$(EXT)
	@printf "Executable cleaned\n"
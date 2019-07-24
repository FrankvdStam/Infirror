# Alternative GNU Make workspace makefile autogenerated by Premake

ifndef config
  config=debug
endif

ifndef verbose
  SILENT = @
endif

ifeq ($(config),debug)
  glfw_config = debug
  glad_config = debug
  imgui_config = debug
  simulator_config = debug
  cli_config = debug
  infirror_lib_config = debug

else ifeq ($(config),release)
  glfw_config = release
  glad_config = release
  imgui_config = release
  simulator_config = release
  cli_config = release
  infirror_lib_config = release

else
  $(error "invalid configuration $(config)")
endif

PROJECTS := glfw glad imgui simulator cli infirror_lib

.PHONY: all clean help $(PROJECTS) desktop graphics

all: $(PROJECTS)

desktop: cli simulator

graphics: glad glfw imgui

glfw:
ifneq (,$(glfw_config))
	@echo "==== Building glfw ($(glfw_config)) ===="
	@${MAKE} --no-print-directory -C projects/simulator/libraries/glfw -f Makefile config=$(glfw_config)
endif

glad:
ifneq (,$(glad_config))
	@echo "==== Building glad ($(glad_config)) ===="
	@${MAKE} --no-print-directory -C projects/simulator/libraries/glad -f Makefile config=$(glad_config)
endif

imgui:
ifneq (,$(imgui_config))
	@echo "==== Building imgui ($(imgui_config)) ===="
	@${MAKE} --no-print-directory -C projects/simulator/libraries/imgui -f Makefile config=$(imgui_config)
endif

simulator: glfw glad imgui
ifneq (,$(simulator_config))
	@echo "==== Building simulator ($(simulator_config)) ===="
	@${MAKE} --no-print-directory -C projects/simulator -f Makefile config=$(simulator_config)
endif

cli:
ifneq (,$(cli_config))
	@echo "==== Building cli ($(cli_config)) ===="
	@${MAKE} --no-print-directory -C projects/cli -f Makefile config=$(cli_config)
endif

infirror_lib:
ifneq (,$(infirror_lib_config))
	@echo "==== Building infirror_lib ($(infirror_lib_config)) ===="
	@${MAKE} --no-print-directory -C projects/infirror/src/infirror_lib -f Makefile config=$(infirror_lib_config)
endif

clean:
	@${MAKE} --no-print-directory -C projects/simulator/libraries/glfw -f Makefile clean
	@${MAKE} --no-print-directory -C projects/simulator/libraries/glad -f Makefile clean
	@${MAKE} --no-print-directory -C projects/simulator/libraries/imgui -f Makefile clean
	@${MAKE} --no-print-directory -C projects/simulator -f Makefile clean
	@${MAKE} --no-print-directory -C projects/cli -f Makefile clean
	@${MAKE} --no-print-directory -C projects/infirror/src/infirror_lib -f Makefile clean

help:
	@echo "Usage: make [config=name] [target]"
	@echo ""
	@echo "CONFIGURATIONS:"
	@echo "  debug"
	@echo "  release"
	@echo ""
	@echo "TARGETS:"
	@echo "   all (default)"
	@echo "   clean"
	@echo "   glfw"
	@echo "   glad"
	@echo "   imgui"
	@echo "   simulator"
	@echo "   cli"
	@echo "   infirror_lib"
	@echo ""
	@echo "For more information, see https://github.com/premake/premake-core/wiki"
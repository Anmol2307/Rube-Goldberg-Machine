.SUFFIXES: .cpp .hpp

# Programs
SHELL 	= bash
CC     	= g++
LD	= ld
RM 	= rm
ECHO	= /bin/echo
CAT	= cat
PRINTF	= printf
SED	= sed
DOXYGEN = doxygen
######################################
# Project Name (generate executable with this name)
TARGET = cs296_base

# Project Paths
PROJECT_ROOT=$(HOME)/g25_project/cs296_base_code
EXTERNAL_ROOT=$(PROJECT_ROOT)/external
SRCDIR = $(PROJECT_ROOT)/src
OBJDIR = $(PROJECT_ROOT)/obj
BINDIR = $(PROJECT_ROOT)/bin
DOCDIR = $(PROJECT_ROOT)/doc
SCRIPTDIR = $(PROJECT_ROOT)/scripts
# Library Paths
BOX2D_ROOT=$(EXTERNAL_ROOT)
GLUI_ROOT=/usr
GL_ROOT=/usr

#Libraries
LIBS = -lBox2D -lglui -lglut -lGLU -lGL

# Compiler and Linker flags
CPPFLAGS =-g -Wall -O3 -std=c++0x
CPPFLAGS+=-I $(BOX2D_ROOT)/include -I $(GLUI_ROOT)/include
LDFLAGS+=-L $(BOX2D_ROOT)/lib -L $(GLUI_ROOT)/lib

######################################

NO_COLOR=\e[0m
OK_COLOR=\e[1;32m
ERR_COLOR=\e[1;31m
WARN_COLOR=\e[1;33m
MESG_COLOR=\e[1;34m
FILE_COLOR=\e[1;37m

OK_STRING="[OK]"
ERR_STRING="[ERRORS]"
WARN_STRING="[WARNINGS]"
OK_FMT="${OK_COLOR}%30s\n${NO_COLOR}"
ERR_FMT="${ERR_COLOR}%30s\n${NO_COLOR}"
WARN_FMT="${WARN_COLOR}%30s\n${NO_COLOR}"
######################################

SRCS := $(wildcard $(SRCDIR)/*.cpp)
INCS := $(wildcard $(SRCDIR)/*.hpp)
OBJS := $(SRCS:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

INSTALLPATH = $(HOME)/install

.PHONY: all setup report doc clean distclean

all: setup $(EXTERNAL_ROOT)/lib/libBox2D.a $(BINDIR)/$(TARGET) report doc

setup:
	@$(ECHO) "Setting up compilation..."
	@mkdir -p obj
	@mkdir -p bin

$(BINDIR)/$(TARGET): $(OBJS)
	@$(PRINTF) "$(MESG_COLOR)Building executable:$(NO_COLOR) $(FILE_COLOR) %16s$(NO_COLOR)" "$(notdir $@)"
	@$(CC) -o $@ $(CPPFLAGS) $(LDFLAGS) $(OBJS) $(LIBS) 2> temp.log || touch temp.err
	@if test -e temp.err; \
	then $(PRINTF) $(ERR_FMT) $(ERR_STRING) && $(CAT) temp.log; \
	elif test -s temp.log; \
	then $(PRINTF) $(WARN_FMT) $(WARN_STRING) && $(CAT) temp.log; \
	else $(PRINTF) $(OK_FMT) $(OK_STRING); \
	fi;
	@$(RM) -f temp.log temp.err

-include $(OBJS:.o=.d)

$(OBJS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	@$(PRINTF) "$(MESG_COLOR)Compiling: $(NO_COLOR) $(FILE_COLOR) %25s$(NO_COLOR)" "$(notdir $<)"
	@$(CC) $(CPPFLAGS) -c $< -o $@ -MD 2> temp.log || touch temp.err
	@if test -e temp.err; \
	then $(PRINTF) $(ERR_FMT) $(ERR_STRING) && $(CAT) temp.log; \
	elif test -s temp.log; \
	then $(PRINTF) $(WARN_FMT) $(WARN_STRING) && $(CAT) temp.log; \
	else printf "${OK_COLOR}%30s\n${NO_COLOR}" "[OK]"; \
	fi;
	@$(RM) -f temp.log temp.err

doc:
	@$(ECHO) -n "Generating Doxygen Documentation ...  "
	@$(RM) -rf doc/html
	@$(DOXYGEN) $(DOCDIR)/Doxyfile 2 > /dev/null
	@$(ECHO) "Done"

$(EXTERNAL_ROOT)/lib/libBox2D.a: ./external/src/Box2D.tgz
	@cd $(EXTERNAL_ROOT)/src ;\
	rm -rf Box2D ;\
	tar -zxvf Box2D.tgz ;\
	cd Box2D ;\
	mkdir build296 ;\
	cd build296 ;\
	cmake ../ ;\
	make ;\
	make install

report: $(DOCDIR)/g25_project_report.tex $(DOCDIR)/ReportImages
	@cd doc/;\
	latex g25_project_report.tex ;\
	bibtex 	g25_project_report.aux ;\
	latex g25_project_report.tex ;\
	latex g25_project_report.tex ;\
	dvips g25_project_report.dvi ;\
	ps2pdf g25_project_report.ps ;\
	rm -rf *.dvi *.ps *.log *.aux *.bbl *.blg ;\
	cd .. ;\
	#chmod ./scripts/g25_gen_html.py ;\	
	@./scripts/g25_gen_html.py

dist : distclean
	@cd ../ ;\
	tar -zcvf cs296_g25_project.tar.gz cs296_base_code

install : 
	@mkdir -p $(INSTALLPATH)
	@mkdir -p $(INSTALLPATH)/doc
	@cp -r $(BINDIR) $(INSTALLPATH)/
	@cp  $(DOCDIR)/g25_project_report.pdf $(INSTALLPATH)/doc/
	@cp -r $(DOCDIR)/html $(INSTALLPATH)/doc/
	@cp  $(DOCDIR)/g25_project_report.html $(INSTALLPATH)/doc/
	
clean:
	@$(ECHO) -n "Cleaning up..."
	@$(RM) -rf $(OBJDIR) *~ $(DEPS) $(SRCDIR)/*~ $(BINDIR) $(DOCDIR)/html  $(DOCDIR)/*~ $(DOCDIR)/*.pdf
	@$(ECHO) "Done"

distclean: clean
	@$(RM) -rf $(EXTERNAL_ROOT)/lib/* $(EXTERNAL_ROOT)/include/* $(EXTERNAL_ROOT)/src/Box2D

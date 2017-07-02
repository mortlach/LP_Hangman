#!/usr/bin/make -f
# ngram_chainer 7/17
# Where to install the program)?
BINDIR = .

# what to call the programme?
PROGRAM += ngram_chainer

# List all sources of the program 
SRCS += main.cpp
SRCS += controller.cpp
SRCS += file_io.cpp
SRCS += next_data.cpp
SRCS += ngram_file_finder.cpp
SRCS += output_writer.cpp
SRCS += settings_reader.cpp
SRCS += start_data.cpp

# list all include directories, source directories, etc
INCDIRS += $(CURDIR)/c++
INCDIRS += $(CURDIR)/c++/src
INCDIRS += $(CURDIR)/c++/include

# where to put object-code 
OBJDIR = $(CURDIR)/c++/obj

OBJS = $(addprefix $(OBJDIR)/, $(addsuffix .o,$(basename $(SRCS))))

#optimize, include pthreads, -g(debug), Wall and use c++14
#CFLAGS = -O3 -g -Wall -std=c++14
CFLAGS = -O3 -std=c++14

INC = $(addprefix -I,$(INCDIRS))

VPATH = $(INCDIRS)

obj%:
	mkdir $@

$(BINDIR)/$(PROGRAM): $(OBJS)
	@echo ''
	@echo '         !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!'
	@echo '         !!!!!!!!!!!!!!!!!!!!!!!  Linking Objects   !!!!!!!!!!!!!!!!!!!!!'
	@echo '         !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!'
	@echo ''
	$(CXX) -o $@ $^ 


$(OBJDIR)/%.o: %.cpp
	@echo ''
	@echo '         !!!!!!!!!!!!!!!!!!!!!!!  BUILDING $@  !!!!!!!!!!!!!!!!!!!!!!!'
	@echo ''
	$(CXX) -c $(INC) $(CFLAGS)  $< -o $@


printVar:
	@echo ''
	@echo ''
	@echo $(OBJS)
	@echo ''
	@echo $(VPATH)

clean:
	rm -rf $(OBJDIR)/*.o
	rm -f $(foreach prog,$(PROGRAM),$(BINDIR)/$(prog))

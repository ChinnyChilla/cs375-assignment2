TARFILE = ../Michael_Zheng_C++.tar
REPODIR = ./*
ZIPFILE = ${TARFILE}.gz

all: submission makeInput

submission: submission.cpp
	g++ -o submission submission.cpp -std=c++11 -O3 -Wall -Wextra -Werror -pedantic

makeInput: makeInput.cpp
	g++ -o makeInput makeInput.cpp -std=c++11 -O3 -Wall -Wextra -Werror -pedantic

clean:
	rm -rf submission makeInput *.o output*.txt 
tar:	clean
	tar cvvf $(TARFILE) ${REPODIR}
	gzip $(TARFILE)
	@echo "Tarred and gzipped file is in the directory one level up"
	@echo $(ZIPFILE)
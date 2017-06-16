CC=gcc
CAENDIGLIB=CAENDigitizer

bin/simpledaq: src/*.c
	mkdir -p bin
	$(CC) $^ -l$(CAENDIGLIB) -o $@ inih/ini.c  -Iinih -Isrc

clean:
	rm -rf bin
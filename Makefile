CC=gcc
CAENDIGLIB=CAENDigitizer

bin/simpledaq: src/simpledaq.c
	mkdir -p bin
	$(CC) $< -l$(CAENDIGLIB) -o $@

clean:
	rm -rf bin
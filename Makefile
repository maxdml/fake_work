CFLAGS = -Wno-register -O3 -mtune=intel -DNDEBUG

mb: libfake
	$(CXX) -I. -L. mb.cc -o mb -lfake $(CFLAGS)
	chmod +x mb

libfake:
	$(CC) -c $(CFLAGS) -fPIC fake_work.c
	$(CC) -shared -o libfake.so fake_work.o

clean:
	rm -rf libfake.so fake_work.h.gch fake_work.o mb

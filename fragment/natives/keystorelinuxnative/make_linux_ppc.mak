# Use this makefile to build ppc 32-bit.

LIBSECURE_CFLAGS = `pkg-config --cflags libsecret-1`
LIBSECURE_LIBS = `pkg-config --libs libsecret-1`

BUILD_DIR = .

CFLAGS = -shared -fPIC -I"${JAVA_HOME}/include" -I"${JAVA_HOME}/include/linux"

all: libkeystoreLinuxNative.so install

install: libkeystoreLinuxNative.so
	if test $(BUILD_DIR) != '.'; then cp -u $< $(BUILD_DIR)/$<; fi
	
clean:
	rm libkeystoreLinuxNative.so keystoreLinuxNative.o
	
libkeystoreLinuxNative.so: keystoreLinuxNative.o
	$(CC) $(CFLAGS) -o $@ $< $(LIBSECURE_LIBS)
	
keystoreLinuxNative.o: keystoreLinuxNative.c
	$(CC) -c -m32 -fPIC -I"${JAVA_HOME}/include" -I"${JAVA_HOME}/include/linux" $(TESTFLAGS) $(LIBSECURE_CFLAGS) $<

LIBSECURE_CFLAGS = `pkg-config --cflags libsecret-1`
LIBSECURE_LIBS = `pkg-config --libs libsecret-1`

BUILD_DIR = .

CFLAGS = -shared -fPIC -I"${JAVA_HOME}/include" -I"${JAVA_HOME}/include/linux"

all: libkeystorelinuxnative.so install

install: libkeystorelinuxnative.so
	if test $(BUILD_DIR) != '.'; then cp -u $< $(BUILD_DIR)/$<; fi
	
clean:
	rm libkeystorelinuxnative.so keystoreLinuxNative.o
	
libkeystorelinuxnative.so: keystoreLinuxNative.o
	$(CC) $(CFLAGS) -o $@ $< $(LIBSECURE_LIBS)
	
keystoreLinuxNative.o: keystoreLinuxNative.c
	$(CC) -c -fPIC -I"${JAVA_HOME}/include" -I"${JAVA_HOME}/include/linux" $(TESTFLAGS) $(LIBSECURE_CFLAGS) $<

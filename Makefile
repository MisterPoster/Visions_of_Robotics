# Compiler
CC = g++

# Compiler flags
CFLAGS = -Wall

# Source files for different targets
TEST_SRCS = utilsTest.cc utils.cc
QR_SRCS = qrDecomp.cc utils.cc matrixUtils.cc
CALIB_SRCS = calib.cc readParams.cc readData.cc utils.cc

# Object files (replace .cc with .o)
TEST_OBJS = $(TEST_SRCS:.cc=.o)
QR_OBJS = $(QR_SRCS:.cc=.o)
CALIB_OBJS = $(CALIB_SRCS:.cc=.o)

# Output executables
TEST_TARGET = utilsTest
QR_TARGET = qrDecomp
CALIB_TARGET = calib

# Generic rule to build the final executable
$(TEST_TARGET): $(TEST_OBJS)
	$(CC) $(CFLAGS) -o $@ $(TEST_OBJS)

$(QR_TARGET): $(QR_OBJS)
	$(CC) $(CFLAGS) -o $@ $(QR_OBJS)

$(CALIB_TARGET): $(CALIB_OBJS)
	$(CC) $(CFLAGS) -o $@ $(CALIB_OBJS)

# Rule to build object files
%.o: %.cc
	$(CC) $(CFLAGS) -c $< -o $@

# Clean rule
clean:
	rm -f $(TEST_OBJS) $(QR_OBJS) $(CALIB_OBJS) $(TEST_TARGET) $(QR_TARGET) $(CALIB_TARGET)

# Generic run rule
run: $(TARGET)
	./$(TARGET)

# Specific run targets
run_tests: TARGET=$(TEST_TARGET)
run_tests: run

run_qr: TARGET=$(QR_TARGET)
run_qr: run

run_calib: TARGET=$(CALIB_TARGET)
run_calib: run


# ==== To run the tests ====
# make utilsTest	// build
# make run_tests	// build + run

# ==== To run the QR decomposition ====
# make qrDecomp		// build
# make run_qr		// build + run

# ==== To run the calibration ====
# make calib		// build
# make run_calib	// build + run


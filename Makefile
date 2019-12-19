TESTFILLS = testFills
TESTSQ = testStackQueue
TESTDQ = testDeque

OBJS_FILLS_STUDENT = testFills.o solidColorPicker.o fadeColorPicker.o
OBJS_FILLS_PROVIDED = animation.o PNG.o HSLAPixel.o lodepng.o dotColorPicker.o
OBJS_SQ = testStackQueue.o
OBJS_DQ = testDeque.o

CXX = clang++
LD = clang++
CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic
LDFLAGS = -std=c++1y -stdlib=libc++ -lc++abi -lpthread -lm

all: $(TESTSQ) $(TESTFILLS)

$(TESTDQ) : $(OBJS_DQ)
	$(LD) $(OBJS_DQ) $(LDFLAGS) -o $(TESTDQ)

$(TESTSQ) : $(OBJS_SQ)
	$(LD) $(OBJS_SQ) $(LDFLAGS) -o $(TESTSQ)

$(TESTFILLS) : $(OBJS_FILLS_STUDENT) $(OBJS_FILLS_PROVIDED)
	$(LD) $(OBJS_FILLS_STUDENT) $(OBJS_FILLS_PROVIDED) $(LDFLAGS) -o $(TESTFILLS)

testDeque.o : testDeque.cpp cs221util/PNG.h cs221util/HSLAPixel.h deque.h
	$(CXX) $(CXXFLAGS) testDeque.cpp

testStackQueue.o : testStackQueue.cpp cs221util/PNG.h cs221util/HSLAPixel.h stack.h queue.h deque.h
	$(CXX) $(CXXFLAGS) testStackQueue.cpp

testFills.o : testFills.cpp cs221util/PNG.h cs221util/HSLAPixel.h point.h center.h stack.h queue.h deque.h vor.h vor.cpp vor_given.cpp dotColorPicker.h solidColorPicker.h fadeColorPicker.h
	$(CXX) $(CXXFLAGS) testFills.cpp

# Pattern rules for object files
%.o: %.cpp 
	$(CXX) $(CXXFLAGS) $< -o $@

PNG.o : cs221util/PNG.cpp cs221util/PNG.h cs221util/HSLAPixel.h cs221util/lodepng/lodepng.h
	$(CXX) $(CXXFLAGS) cs221util/PNG.cpp

HSLAPixel.o : cs221util/HSLAPixel.cpp cs221util/HSLAPixel.h
	$(CXX) $(CXXFLAGS) cs221util/HSLAPixel.cpp

lodepng.o : cs221util/lodepng/lodepng.cpp cs221util/lodepng/lodepng.h
	$(CXX) $(CXXFLAGS) cs221util/lodepng/lodepng.cpp

clean:
	rm -rf $(TESTSQ) $(TESTFILLS) $(TESTDQ) $(OBJS_DIR) *.o


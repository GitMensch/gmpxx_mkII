CXX = g++-12
CXXFLAGS = -Wall -Wextra
LDFLAGS = -L/home/docker/gmpxx_mkII/i/GMP-6.3.0/lib -lgmp
INCLUDES = -I/home/docker/gmpxx_mkII/i/GMP-6.3.0/include

TARGET = test_gmpxx_mkII
TARGET_EXTRA = test_gmpxx

SOURCES = test_gmpxx_mkII.cpp
HEADERS = gmpxx_mkII.h
OBJECTS = $(SOURCES:.cpp=.o)
OBJECTS_EXTRA = $(SOURCES:.cpp=_extra.o)

all: $(TARGET) $(TARGET_EXTRA)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -DGMPXX_MKII -o $(TARGET) $(OBJECTS) $(LDFLAGS)

$(OBJECTS): $(SOURCES) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $(@:.o=.cpp)

$(TARGET_EXTRA): $(OBJECTS_EXTRA)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $(TARGET_EXTRA) $(OBJECTS_EXTRA) -lgmpxx $(LDFLAGS)

$(OBJECTS_EXTRA): $(SOURCES) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $(SOURCES) -o $@

clean:
	rm -f $(TARGET) $(TARGET_EXTRA) $(OBJECTS) $(OBJECTS_EXTRA) *~

.PHONY: all clean test_gmpxx

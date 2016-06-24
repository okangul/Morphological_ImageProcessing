CVPATH=/usr/local/Cellar/opencv/2.4.12/
INCLUDE_PATH=-I${CVPATH}/include
LIB_PATHS=-L${CVPATH}/lib
LIBS=-lopencv_highgui -lopencv_core -lopencv_imgproc
all: skeleton

skeleton: skeleton.cpp
	g++ skeleton.cpp ${INCLUDE_PATH} ${LIB_PATHS} ${LIBS} -o skeleton

.PHONY:clean

clean:
	rm skeleton

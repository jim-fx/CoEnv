build: 
	g++ shape-detect.cpp modules/*.cpp -o .output/sigil-scanner -I/home/jim/COCO/CoEnv/scanner/ `pkg-config --cflags --libs opencv4` 

build-debug: 
	g++ -g shape-detect.cpp modules/*.cpp -o .output/sigil-scanner -I/home/jim/COCO/CoEnv/scanner/ `pkg-config --cflags --libs opencv4` 

run: build
	killall sigil-scanner; \
	./.output/sigil-scanner 0 & 

dev:
	make run;
	while true; do \
    inotifywait -qr -e modify -e create -e delete -e move ./**/*.cpp ./*.cpp; \
    make run;\
  done

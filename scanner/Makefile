build: 
	g++ scanner.cpp modules/*.cpp -o .output/sigil-scanner -I/home/jim/COCO/16_FunctionObjects/scanner/ `pkg-config --cflags --libs opencv4` 

run: build
	killall sigil-scanner; \
	./.output/sigil-scanner & 

dev:
	make run;
	while true; do \
    inotifywait -qr -e modify -e create -e delete -e move ./**/*.cpp; \
    make run;\
  done

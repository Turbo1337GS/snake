all: GigaSoft

GigaSoft: main.cpp
	 g++  ./*.cpp ./*.hpp -lcurl -lboost_system -o GigaSoft 

clean:
	rm -f GigaSoft 

disable:
	lsof -t -i:8000 | xar gs -I {} kill -9 {}

restart:
	@if [ ! -d "BUILD" ]; then mkdir BUILD; fi
	lsof -t -i:8000 | xargs -I {} kill -9 {} && GigaSoft

build:
	@if [ ! -d "BUILD" ]; then mkdir BUILD; fi
	g++ ./*.cpp ./*.hpp -lcurl -lboost_system -o GigaSoft

start: 
	GigaSoft

dev: main.cpp
	 g++ ./*.cpp ./*.hpp -lcurl -lboost_system -o GigaSoft && ./GigaSoft
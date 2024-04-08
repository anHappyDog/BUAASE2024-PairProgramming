
.PHONY:ff
ff:
	emcc -o bocchi.cjs bocchi.cpp -s WASM=1 -O3 -s EXPORTED_FUNCTIONS='["_bocchi_shut_up","_malloc"]' -s EXTRA_EXPORTED_RUNTIME_METHODS='["cwrap"]'	
ff:
	emcc -o mancala.cjs mancala.cpp -s WASM=1 -O3 -s EXPORTED_FUNCTIONS='["_mancala_result","_malloc"]' -s EXTRA_EXPORTED_RUNTIME_METHODS='["cwrap"]'	
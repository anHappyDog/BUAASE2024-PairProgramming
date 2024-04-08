.PHONY:ff
ff:
	emcc -o mancala.cjs mancala.cpp -s WASM=1 -O3 -s EXPORTED_FUNCTIONS='["_mancala_board","_mancala_operator","_malloc","_mancala_operator2"]' -s EXTRA_EXPORTED_RUNTIME_METHODS='["cwrap"]'	
import Module from "./mancala.cjs";

let _mancala_result;
let _malloc;
let _heap32;
const moduleInitialized = new Promise((resolve, reject) => {
  Module.onRuntimeInitialized = () => {
    try {
      _mancala_result = Module.cwrap("mancala_result", "number", ["number", "number", "number"]);
      _malloc = Module._malloc;
      _heap32  = Module.HEAP32;
      resolve();
    } catch (e) {
      reject(e);
    }
  };
});

await moduleInitialized;

const mancalaResult = (flag,seq,size) => {
    let _seq = _malloc(size * 4);
    for(let i = 0; i < size; ++i) {
        _heap32[_seq / 4 + i] = seq[i];
    }
    return _mancala_result(flag,_seq,size);
}


export { mancalaResult };
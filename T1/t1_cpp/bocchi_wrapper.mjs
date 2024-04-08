import Module from "./bocchi.cjs";

let _bocchi_shut_up;
let _malloc;
let _heap32;
const moduleInitialized = new Promise((resolve, reject) => {
  Module.onRuntimeInitialized = () => {
    try {
      _bocchi_shut_up = Module.cwrap("bocchi_shut_up", "number", ["number", "number", "number"]);
      _malloc = Module._malloc;
      _heap32  = Module.HEAP32;
      resolve();
    } catch (e) {
      reject(e);
    }
  };
});

await moduleInitialized;

const bocchiShutUp = (flag,seq,size) => {
    let _seq = _malloc(size * 4);
    for(let i = 0; i < size; ++i) {
        _heap32[_seq / 4 + i] = seq[i];
    }
    return _bocchi_shut_up(flag,_seq,size);
}

export { bocchiShutUp };
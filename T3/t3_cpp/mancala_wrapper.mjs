import Module from "./mancala.cjs";

let _mancala_board;
let _mancala_operator;
let _mancala_operator2;
let _malloc;
let _heap32;
const moduleInitialized = new Promise((resolve, reject) => {
  Module.onRuntimeInitialized = () => {
    try {
      _mancala_board = Module.cwrap("mancala_board", "number", ["number", "number", "number"]);
      _mancala_operator = Module.cwrap("mancala_operator","number",["number","number"]);
      _mancala_operator2 = Module.cwrap("mancala_operator2","number",["number","number"]);
      _malloc = Module._malloc;
      _heap32  = Module.HEAP32;
      resolve();
    } catch (e) {
      reject(e);
    }
  };
});

await moduleInitialized;
let answer = new Int32Array(15);
let _status = _malloc(14 * 4);
const mancalaBoard= (flag,seq,size) => {
    let _seq = _malloc(size * 4);
    let _answer;

    _heap32.set(seq,_seq  / 4);
    _answer =  _mancala_board(flag,_seq,size);
    for (let i = 0; i < 15; ++i) {
      answer[i] = _heap32[_answer / 4 + i];
    }
    return answer;
}

const mancalaOperator = (flag,status) => {
    _heap32.set(status, _status / 4);
    return _mancala_operator2(flag,_status);
}

const mancalaOperator2 = (flag,status) => {
  _heap32.set(status, _status / 4);
  return _mancala_operator(flag,_status);
}

// 导出已初始化的函数
export { mancalaBoard,mancalaOperator,mancalaOperator2 };
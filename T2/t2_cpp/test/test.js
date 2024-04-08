import {mancalaResult } from '../mancala_wrapper.mjs';
import assert from 'assert';

const flags=  [
    1,1,1,1,1,1,1,1
];
const seqs = [
    [21],
    [11],
    [13,11],
    [13,13],
    [13,21],
    [13,11,22],
    [13,11,22,22],
    [13,11,22,12,23,21],
    
];
const sizes = [
    1,1,2,2,2,3,4,6
];
const res = [
    30000,20000,20001,30001,30001,20001,30003,30004
];

for (let i = 0; i < seqs.length; ++i) {
    assert.strictEqual(mancalaResult(flags[i],seqs[i],sizes[i]),res[i]);
}

console.log("🎉 You have passed all the tests provided.");
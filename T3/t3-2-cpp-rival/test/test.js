import assert from 'assert';
import { mancalaBoard } from '../mancala_wrapper.mjs';

const mancalaBoardTest = () => {
    const flags = [
        1,2
    ];
    const seqs = [
        [11,11],[11,23],
    ];
    const sizes = [
        2,2,
    ];
    const res = [
        [0,5,5,5,5,4,0,4,4,4,4,4,4,0,152],
        [0,5,5,5,5,4,0,4,4,0,5,5,5,1,2],
    ];
    for (let i = 0; i < seqs.length; ++i) {
        let ans = mancalaBoard(flags[i],seqs[i],sizes[i]);
        for(let j = 0; j < 15; ++j) {
            assert.strictEqual(ans[j],res[i][j]);
        }
    }
    console.log("all passed");
};
mancalaBoardTest();

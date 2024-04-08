import assert from "assert";

// Choose proper "import" depending on your PL.
// import { bocchiShutUp } from "./t1-as/build/release.js";
import { bocchiShutUp } from "../bocchi_wrapper.mjs";

const flags = [1,2,2,1,2,2,1];
const arrs = [
    [13,14,15,16], // many ghost
    [22,23,23,21], // one ghost for 2
    [11,11,11,23], // one ghost for 1
    [12,13,13,14,15], // one ghost for 1
    [22], // one size
    [22,23,24,25,25], 
    [11],
];
const sizes = [
    4,4,4,5,1,5,1
];
const res = [
    10,23,23,13,22,25,11
];
for(let i = 0; i < arrs.length; ++i) {
    assert.strictEqual(bocchiShutUp(flags[i],arrs[i],sizes[i]),res[i]);
}
// assert.strictEqual(bocchiShutUp(1,[13,14,15,21,11,16],6),10);
// assert.strictEqual(bocchiShutUp(2,[13,14,13,11,21,13,21,22],8),21);

console.log("🎉 You have passed all the tests provided.");

import {ok} from "node:assert";
import * as U from "./util.ts";

type Input = {
    a: Array<number>,
    b: Array<number>,
};

function parseInput(input: string): Input {
    const a: Array<number> = [];
    const b: Array<number> = [];
    for (const line of U.lines(input)) {
        const [s1, s2] = line.split("   ");
        const n1 = Number(s1);
        ok(!isNaN(n1));
        a.push(n1);
        const n2 = Number(s2);
        ok(!isNaN(n2));
        b.push(n2);
    }
    return {a, b};
}

function partOne(input: Input): number {
    /** We could simply sort both arrays
     *  and traverse in order. */
    const a = input.a.toSorted();
    const b = input.b.toSorted();
    const xs: Array<number> = [];
    for (let i = 0; i < a.length; i++) {
        /** Using abs to get the distance
         *  between both values. */
        xs.push(Math.abs(a[i] - b[i]));
    }
    return U.sum(xs);
}

function partTwo(input: Input): number {
    /** First let's count how many numbers we have
     *  in the second list. */
    const m = new Map<number, number>();
    for (let i = 0; i < input.b.length; i++) {
        const n = input.b[i];
        const e = m.get(n);
        if (e === undefined) {
            m.set(n, 1);
        } else {
            m.set(n, e + 1);
        }
    }
    /** Now we can simply iterate the first list
     *  and multiply it by the amount from second
     *  list. */
    const xs: Array<number> = [];
    for (let i = 0; i < input.a.length; i++) {
        const n = input.a[i];
        const a = m.get(n) ?? 0;
        xs.push(n * a);
    }
    return U.sum(xs);
}

async function main() {
    const text = await Deno.readTextFile("inputs/day1.txt");
    const input = parseInput(text);
    console.log(partOne(input));
    console.log(partTwo(input));
}

main();

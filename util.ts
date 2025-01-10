export function sum(xs: Array<number>): number {
    return xs.reduce((x, y) => x + y, 0);
}

export function lines(input: string): Array<string> {
    return input
    .split("\n")
    .map(x => x.trim())
    .filter(x => x !== "")
}

export default "util";

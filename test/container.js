const mice = require('../MICE/build/Release/mice');

let container = {
    name: "BOWL",
    description: "A BOWL FOR UR FRUIT",
    wholesaleCost: 12.0,
    retailCost: 13.0,
    stockRemaining: 5,
    img: "path to img",
    scoopCount: 5
}
let container2 = {
    name: "CUP",
    description: "The bowls underachieving brother",
    wholesaleCost: 2.0,
    retailCost: 55.0,
    stockRemaining: 2,
    img: "path to img",
    scoopCount: 2
}
mice.createContainer(container);
mice.createContainer(container2);

console.log("about to get container");
console.log(mice.getState());
// console.log(mice.getContainer(0));
// console.log(mice.getContainer(1));
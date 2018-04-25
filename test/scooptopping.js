const mice = require('../MICE/build/Release/mice');

let scoop = {
    name: "VANIALLA",
    description: "BASIC VANILLA SCOOP",
    wholesaleCost: 12.0,
    retailCost: 13.0,
    stockRemaining: 5,
    img: "path to img",
    scoopCount: 5
}
let topping = {
    name: "SPRIKNLES",
    description: "EDGIER VANILLA",
    wholesaleCost: 2.0,
    retailCost: 55.0,
    stockRemaining: 4,
    img: "path to img",
    scoopCount: 2
}
mice.createScoop(scoop);
mice.createTopping(topping);

console.log("about to get scoop");
console.log(mice.getState());
// console.log(mice.getContainer(0));
// console.log(mice.getContainer(1));
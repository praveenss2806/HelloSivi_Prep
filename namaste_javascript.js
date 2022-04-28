var x = 1;
a();
b();
console.log(x);
function a() {
 var x = 10;
 console.log(x);
}
function b() {
 var x = 100;
 console.log(x);
}

//scope chain
var x = 10;
console.log(x);
console.log(this.x);
console.log(window.x);

//let and const
console.log(c)
let a = 10;
const b = 1000;
var c = 100;

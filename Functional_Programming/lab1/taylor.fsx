// Print a table of a given function f, computed by taylor series
// interval [0.1; 0.6]
// func (2x-3)/(x-1)^2
// series -3-4x-5x^2-(n+3)x^n
// function to compute
let f x = (2.*x-3.)/(x-1.)**2.

let a = 0.1
let b = 0.6
let n = 10
let eps = 0.005

// Define a function to compute f using naive taylor series method
let taylor_naive x f_res =
    let res = 0.
    let n  = 0.
    while ((abs (res - f_res)) <= eps) do
      let res = -1. * (n + 3.) * x**n
      let n = n + 1.
    res


// Define a function to do the same in a more efficient way
let taylor = f

let main =
   for i=0 to n do
     let x = a+(float i)/(float n)*(b-a) 
     let f_native = f x
     printfn "%5.2f  %10.6f  %10.6f   %10.6f" x f_native (taylor_naive x f_native) (taylor x)
// make sure to improve this table to include the required number of iterations
// for each of the methods
// Solution

// In this sample, the goal was to compute the length of the list

// Method 1: Library Function
let splitIntoPairs1 lst =
    List.chunkBySize 2 lst
    |> List.map (fun x -> (x.[0], x.[1]))

// Method 2: Recursion
let rec splitIntoPairs2 lst =
    match lst with
    | [] -> []
    | x::y::tl -> (x,y) :: splitIntoPairs2 tl
    | _ -> failwith "The list has an odd number of elements and cannot be split into pairs."

// Method 3: Tail Rec
let splitIntoPairs3 lst =
    let rec loop acc lst =
        match lst with
        | [] -> List.rev acc
        | x::y::tl -> loop ((x,y)::acc) tl
        | _ -> failwith "The list has an odd number of elements and cannot be split into pairs."
    loop [] lst

let lst = [1; 2; 3; 4]
let pairs1 = splitIntoPairs1 lst
printfn "%A" pairs1
let pairs2 = splitIntoPairs2 lst
printfn "%A" pairs2  
let pairs3 = splitIntoPairs3 lst
printfn "%A" pairs3
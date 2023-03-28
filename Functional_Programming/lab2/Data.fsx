// Part 2
// Task 3   - Для каждого студента, напечатайте его среднюю оценку и сдал ли он сессию (все оценки >2)
//          - Для каждого предмета, напечатайте список двоечников
//          - Для каждой группы, найдите студента (или студентов) с максимальной суммарной оценкой
// Load the data
#load "Four.fsx"
open Four

// Для каждого студента, напечатайте его среднюю оценку и сдал ли он сессию (все оценки >2)
let Task_1 (students : (int * string * (string * int) list) list) =
    students
    |> List.groupBy (fun (_, student_last_name, _) -> student_last_name)
    |> List.map (fun (student_last_name, students) ->
        let marks_of_student =
            students
            |> List.collect (fun (_, _, grades) -> grades)
            |> List.map snd
        let sum_of_marks = 
            marks_of_student
            |> List.sum
        let pass_session = 
            not(
                marks_of_student 
                |> List.exists (fun x -> x = 2)
            )
        printfn "Студент: %s" student_last_name
        printfn "Средняя оценка: %f" (float sum_of_marks / 6.0)
        printfn "Сессию сдал: %b" pass_session)

// Для каждого предмета, напечатайте список двоечников
let Task_2 studs subjs =
    subjs 
    |> List.iter (fun subjCode ->
    let failingStudents = 
        studs 
        |> List.filter (
        fun (_, _, subjList) ->
        subjList 
        |> List.exists (fun (subj, grade) -> subj = fst subjCode && grade = 2)
    )
    let subjName =
        subjs 
        |> List.find (fun (code, name) -> code = fst subjCode) 
        |> snd
    printfn "Двоечники по %s:" subjName
    failingStudents |> List.iter (fun (_, surname, _) -> printfn "- %s" surname))

// Для каждой группы, найдите студента (или студентов) с максимальной суммарной оценкой
let Task_3 (students : (int * string * (string * int) list) list) = 
    students
    |> List.map (fun (x, y, z) -> (x, y, List.sumBy snd z))
    |> List.groupBy (fun (groupNum, _, _) -> groupNum)
    |> List.map (fun (groupNum, groupList) ->
        let maxScore = groupList |> List.map (fun (_, _, score) -> score) |> List.max
        let studentsWithMaxScore = 
            groupList 
            |> List.choose (fun (groupNum, name, score) -> 
                if score = maxScore then Some name else None)
        (groupNum, studentsWithMaxScore))
    |> List.iter (fun (groupNum, studentsWithMaxScore) ->
        printfn "В группе %d есть следующие студенты, набравшие максимальную суммарную оценку: %A" groupNum studentsWithMaxScore)

Task_1 Four.studs 
Task_2 Four.studs Four.subjs
Task_3 Four.studs 
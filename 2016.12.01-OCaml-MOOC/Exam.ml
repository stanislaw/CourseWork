exception NotFound;;
exception Stan_Found;;

type 'e rel = 'e -> 'e list
type 'e prop = 'e -> bool

type ('a, 'set) set_operations = {
  empty : 'set;              (* The empty set. *)
  mem : 'a -> 'set -> bool;  (* [mem x s = true] iff [x] is in [s]. *)
  add : 'a -> 'set -> 'set;  (* [add s x] is the set [s] union {x}. *)
}

type ('configuration, 'move) puzzle = {
  move : 'configuration -> 'move -> 'configuration;
  possible_moves : 'configuration -> 'move list;
  final : 'configuration -> bool
}

type piece_kind = S | H | V | C | X
type piece = piece_kind * int
let x = (X, 0) and s = (S, 0) and h = (H, 0)
let (c0, c1, c2, c3) = ((C, 0), (C, 1), (C, 2), (C, 3))
let (v0, v1, v2, v3) = ((V, 0), (V, 1), (V, 2), (V, 3))
let all_pieces : piece list = [ s; h; c0; c1; c2; c3; v0; v1; v2; v3 ]

type board = piece array array
let initial_board =
  [| [| v0 ; s  ; s  ; v1 |];
     [| v0 ; s  ; s  ; v1 |];
     [| v2 ; h  ; h  ; v3 |];
     [| v2 ; c0 ; c1 ; v3 |];
     [| c2 ; x  ; x  ; c3 |] |]

let initial_board_simpler =
  [| [| c2 ; s  ; s  ; c1 |] ;
     [| c0 ; s  ; s  ; c3 |] ;
     [| v1 ; v2 ; v3 ; v0 |] ;
     [| v1 ; v2 ; v3 ; v0 |] ;
     [| x  ; x  ; x  ; x  |] |]

let initial_board_trivial =
  [| [| x  ; s  ; s  ; x  |] ;
     [| x  ; s  ; s  ; x  |] ;
     [| x  ; x  ; x  ; x  |] ;
     [| x  ; x  ; x  ; x  |] ;
     [| x  ; x  ; x  ; x  |] |]

type direction = { dcol : int; drow : int; }
type move = Move of piece * direction * board

let move _ (Move (_, _, b)) = b

(* Write a function loop of type
('a -> bool) -> ('a -> 'a) -> 'a -> 'a such that
loop p f x = x when p x = true and loop p f x = loop p f (f x) otherwise. *)
let rec loop p f x =
  if (p x)
  then
    x
  else
    loop p f (f x);;

let rec exists p l =
  match l with
  | [] -> false
  | x :: xs when p x -> true
  | _ :: xs -> exists p xs;;

let rec find p l =
  match l with
  | [] -> raise NotFound
  | x :: xs when p x -> x
  | _ :: xs -> find p xs;;

(* --- Part A: A Generic Problem Solver --- *)

let near =
  fun x ->
    [x - 2; x - 1; x; x + 1; x + 2];;

(* 'e rel -> ('e list -> 'e list) *)
let rec flat_map (r : 'e rel) : ('e list -> 'e list) = function
  | [] -> []
  | x :: xs -> (r x) @ (flat_map r xs);;

let rec iter_rel (rel : 'e rel) (n : int) : ('e rel) =
  if n < 2
  then
    rel
  else
    fun x ->
      let res : 'e list ref = ref [x] in
      for i = 1 to n do
        res := flat_map rel !res
      done;
      List.sort_uniq compare !res;;

(*
 Write a function solve of type 'a rel -> 'a prop -> 'a -> 'a such that
solve r p x computes the iteration of the relation ℛ represented by
r starting at x until it reaches an element y such that p y.
For instance, solve near (fun x -> x = 12) 0 should simply return 12.
Internally, the function will start from the set [0],
and iterate near to obtain first [-2;-1;0;1;2], then
a sequence of growing lists, until eventually one iteration returns
a list that contains 12.
*)
(* number of iterations should be limited somehow. the following has passed
   tests however it might hang under certain parameters *)
let solve (r : 'a rel) (p : 'a prop) (x : 'a) : 'a =
  let initial_set = [x] and
  iter_func = fun l' ->
    (flat_map r l') in
  let l = loop (exists p) iter_func initial_set in
  match l with
  | [] -> raise Not_found
  | x :: _ -> x
;;

(*
  Define a function solve_path of type 'a rel -> 'a prop -> 'a -> 'a list such
that solve_path r p x behaves exactly as solve except that it produces not only
the final value y such that p y but also all the intermediate elements from
x to y that show how x is related to y through r.
For instance, solve_path near (fun x -> x = 12) 0 should return
[0;2;4;6;8;10;12]. This function can be written simply by calling solve
with well-chosen arguments. The idea is to iterate over the set of paths to
destinations, instead of the set of destinations.*)

let rec uniq x =
  let rec uniq_help l n =
    match l with
    | [] -> []
    | h :: t -> if n = h then uniq_help t n else h::(uniq_help t n) in
  match x with
  | [] -> []
  | h::t -> h::(uniq_help (uniq t) h)

let solve_path (r : 'a rel) (p : 'a prop) (x : 'a) : 'a list =
  let initial_set = [x] and
  iter_func = fun l' ->
    (uniq (l' @ flat_map r l')) in
  let l = loop (exists p) iter_func initial_set in
  l
;;

(*
 Write a function archive_map of type
('a, 'set) set_operations -> 'a rel -> ('set * 'a list) -> ('set * 'a list)
such that: archive_map opset rel (s, l) = (s', l'), where:

    l' is the list of elements that are reachable using rel from
the elements of l and which are not already in the set s.
    s' is the union of s and the elements of l'.
*)
let archive_map (opset : ('a, 'set) set_operations) (r : 'a rel) (s, l) : ('set * 'a list) =
  let rec do_all f lst =
    match lst with
    | [] -> ()
    | x :: xs -> f x; do_all f xs
  and
    (* opset doesn't have an operation to make copies of existing set
       so this function workarounds that by using 'add' operation *)
    copy_set_by_adding_1st_el set l =
    match l with
    | [] -> set
    | x :: _ -> opset.add x set in
  let l' : 'a list ref = ref [] in
  let reachable_of_l = flat_map r l in
  let s' : 'set ref = ref (copy_set_by_adding_1st_el s reachable_of_l) in
  do_all (fun x ->
      s' := opset.add x !s';
      if not (opset.mem x s)
      then l' := x :: !l'
      else ()
    ) reachable_of_l;
  (!s', (List.rev !l'));;

(* Use archive_map to program a new function solve'
      (don't forget the quote after the name) of type
  ('a, 'set) set_operations -> 'a rel -> 'a prop -> 'a -> 'a that
    explores the search space with no redundancy. *)
let solve' (ops : ('a, 'set) set_operations) (r : 'a rel) (p : 'a prop) (x : 'a) : 'a =
  let initial_set = (ops.add x ops.empty) and
  iter_func = fun (s, l) ->
    (archive_map ops r (s, l)) in
  let (s, l) =
    loop
      (fun (s, l)
        -> (exists p l)
      )
      iter_func
      (initial_set, [x]) in
  match l with
  | [] -> raise Not_found
  | x :: _ -> x
;;

(* Same question for solve_path' of type
('a list, 'set) set_operations -> 'a rel -> 'a prop -> 'a -> 'a list.
*)
let solve_path'
    (opset : ('a list, 'set) set_operations)
    (r : 'a rel)
    (p : 'a prop)
    (x : 'a) : 'a list =
  let iter_func = fun (s, l) ->
    (archive_map
       opset
       (fun lst ->
          let available = (flat_map r lst) in
          List.map
            (fun el ->
               uniq (lst @ [el])
            )
            available
       )
       (s, l)
    ) in
  let (s, l) =
    loop
      (fun (s, l)
        -> (exists (exists p) l)
      )
      iter_func
      (opset.empty, [[x]]) in
  find (fun x -> (exists (fun x -> p x) x)) l
;;

(*
  Implement
solve_puzzle : ('c, 'm) puzzle -> ('c list, 's) set_operations -> 'c -> 'c list
such that solve_puzzle p opset c is a list of moves the application of which
to the configuration c results in a configuration c' such that
p.final c' = true.
Here, opset is a record of set operations which the implementation of
solve_puzzle may use.*)
let solve_puzzle
    (p : ('c, 'm) puzzle)
    (opset : ('c list, 's) set_operations)
    (c : 'c) : 'c list =
  solve_path'
    opset
    (fun conf ->
       (List.map (fun m -> p.move conf m) (p.possible_moves conf))
    )
    (fun conf -> (p.final conf))
    c;;

(* --- Part B: A Solver for Klotski --- *)
(* --- Part B: A Solver for Klotski --- *)

(* --- Part B: A Solver for Klotski --- *)
(* --- Part B: A Solver for Klotski --- *)

(* --- Part B: A Solver for Klotski --- *)
(* --- Part B: A Solver for Klotski --- *)

let clone_board board =
  Array.map Array.copy board;;

let final (board : board) : bool =
  board.(3).(1) = s && board.(3).(2) = s &&
  board.(4).(1) = s && board.(4).(2) = s;;

let find_pos piece board : direction =
  let found_pos : direction ref = ref { dcol = -1; drow = -1 } in
  try
    for row = 0 to 4 do
      for col = 0 to 3 do
        if board.(row).(col) = piece
        then
          begin
            found_pos := { dcol = col; drow = row };
            raise Stan_Found
          end
        else
          ()
      done;
    done;
    raise NotFound
  with Stan_Found -> !found_pos;;

let move_piece
    (board : board)
    (piece : piece)
    { drow; dcol } =
  let new_board = clone_board board in
  let pos = find_pos piece new_board and
  (piece_kind, piece_index) = piece in
  let new_pos = { drow = pos.drow + drow; dcol = pos.dcol + dcol } in
  match piece_kind with
  | C ->
    if new_pos.drow >= 0 && new_pos.drow <= 4 &&
       new_pos.dcol >= 0 && new_pos.dcol <= 3 &&
       new_board.(new_pos.drow).(new_pos.dcol) = x
    then
      begin
        new_board.(new_pos.drow).(new_pos.dcol) <- new_board.(pos.drow).(pos.dcol);
        new_board.(pos.drow).(pos.dcol) <- x;
        Some(new_board)
      end
    else
      None
  | V ->
    if (new_pos.drow + 1) <= 4 &&
       new_pos.drow >= 0 &&
       new_pos.dcol <= 3 &&
       new_pos.dcol >= 0 then
       if dcol != 0 &&
          new_board.(new_pos.drow).(new_pos.dcol) = x &&
          new_board.(new_pos.drow + 1).(new_pos.dcol) = x
       then
         begin
           new_board.(new_pos.drow).(new_pos.dcol) <- new_board.(pos.drow).(pos.dcol);
           new_board.(new_pos.drow + 1).(new_pos.dcol) <- new_board.(pos.drow + 1).(pos.dcol);
           new_board.(pos.drow).(pos.dcol) <- x;
           new_board.(pos.drow + 1).(pos.dcol) <- x;
           Some(new_board)
         end
       else
         if drow > 0 &&
            new_board.(new_pos.drow + 1).(new_pos.dcol) = x then
         begin
           new_board.(new_pos.drow + 1).(new_pos.dcol) <- new_board.(new_pos.drow).(pos.dcol);
           new_board.(new_pos.drow).(new_pos.dcol) <- new_board.(pos.drow).(pos.dcol);
           new_board.(pos.drow).(pos.dcol) <- x;
           Some(new_board)
         end
       else if drow < 0 &&
            new_board.(new_pos.drow).(new_pos.dcol) = x then
         begin
           new_board.(new_pos.drow).(new_pos.dcol) <- new_board.(pos.drow).(pos.dcol);
           new_board.(new_pos.drow + 1).(new_pos.dcol) <- new_board.(pos.drow + 1).(pos.dcol);
           new_board.(pos.drow + 1).(pos.dcol) <- x;
           Some(new_board)
         end
       else
         None
    else
      None
  | S ->
    if (new_pos.drow + 1) <= 4 &&
       new_pos.drow >= 0 &&
       (new_pos.dcol + 1) <= 3 &&
       new_pos.dcol >= 0 then
       if dcol > 0 &&
          new_board.(new_pos.drow).(new_pos.dcol + 1) = x &&
          new_board.(new_pos.drow + 1).(new_pos.dcol + 1) = x
       then
         begin
           new_board.(new_pos.drow).(new_pos.dcol + 1) <- new_board.(new_pos.drow).(new_pos.dcol);
           new_board.(new_pos.drow + 1).(new_pos.dcol + 1) <- new_board.(new_pos.drow + 1).(new_pos.dcol);

           new_board.(pos.drow).(pos.dcol) <- x;
           new_board.(pos.drow + 1).(pos.dcol) <- x;

           Some(new_board)
         end
       else if dcol < 0 &&
          new_board.(new_pos.drow).(new_pos.dcol) = x &&
          new_board.(new_pos.drow + 1).(new_pos.dcol) = x
       then
         begin
           new_board.(new_pos.drow).(new_pos.dcol) <- new_board.(new_pos.drow).(new_pos.dcol + 1);
           new_board.(new_pos.drow + 1).(new_pos.dcol) <- new_board.(new_pos.drow + 1).(new_pos.dcol + 1);

           new_board.(pos.drow).(pos.dcol + 1) <- x;
           new_board.(pos.drow + 1).(pos.dcol + 1) <- x;

           Some(new_board)
         end
       else if drow < 0 &&
          new_board.(new_pos.drow).(new_pos.dcol) = x &&
          new_board.(new_pos.drow).(new_pos.dcol + 1) = x
       then
         begin
           new_board.(new_pos.drow).(new_pos.dcol) <- s;
           new_board.(new_pos.drow).(new_pos.dcol + 1) <- s;

           new_board.(pos.drow + 1).(pos.dcol) <- x;
           new_board.(pos.drow + 1).(pos.dcol + 1) <- x;

           Some(new_board)
         end
       else if drow > 0 &&
          new_board.(new_pos.drow + 1).(new_pos.dcol) = x &&
          new_board.(new_pos.drow + 1).(new_pos.dcol + 1) = x
       then
         begin
           new_board.(new_pos.drow + 1).(new_pos.dcol) <- s;
           new_board.(new_pos.drow + 1).(new_pos.dcol + 1) <- s;

           new_board.(pos.drow).(pos.dcol) <- x;
           new_board.(pos.drow).(pos.dcol + 1) <- x;

           Some(new_board)
         end
       else
         None
    else
      None
  | H ->
     if (new_pos.dcol + 1) <= 3 &&
       new_pos.dcol >= 0 &&
       new_pos.drow <= 4 &&
       new_pos.drow >= 0 then
       if drow != 0 &&
          new_board.(new_pos.drow).(new_pos.dcol) = x &&
          new_board.(new_pos.drow).(new_pos.dcol + 1) = x
       then
         begin
           new_board.(new_pos.drow).(new_pos.dcol) <- new_board.(pos.drow).(pos.dcol);
           new_board.(new_pos.drow).(new_pos.dcol + 1) <- new_board.(pos.drow).(pos.dcol + 1);
           new_board.(pos.drow).(pos.dcol) <- x;
           new_board.(pos.drow).(pos.dcol + 1) <- x;
           Some(new_board)
         end
       else if dcol > 0 &&
            new_board.(new_pos.drow).(new_pos.dcol + 1) = x then
         begin
           new_board.(new_pos.drow).(new_pos.dcol + 1) <- new_board.(pos.drow).(pos.dcol);
           new_board.(pos.drow).(pos.dcol) <- x;
           Some(new_board)
         end
       else if dcol < 0 &&
            new_board.(new_pos.drow).(new_pos.dcol) = x then
         begin
           new_board.(new_pos.drow).(new_pos.dcol) <- new_board.(pos.drow).(pos.dcol);
           new_board.(pos.drow).(pos.dcol + 1) <- x;
           Some(new_board)
         end
       else
         None
    else
      None
  | X ->
    None;;

module IntPairs = (
  struct
  type t = int * int
  let compare (x0,y0) (x1,y1) =
    if x0 < x1
    then
      -1
    else if x0 > x1
    then
      1
    else
      if y0 < y1
      then -1
      else if y0 > y1
      then 1
      else 0
  end
)

module PairsSet = Set.Make(IntPairs);;

let possible_moves' = [| (0, 1); (0, -1); (1, 0); (-1, 0) |];;

(* let move_piece
    (board : board)
    (piece : piece)
    { drow; dcol } =

    let move _ (Move (_, _, b)) = b
 *)
exception Continue;;
let possible_moves board =
  let
  result : move list ref = ref []
  and
  skip = ref PairsSet.empty in
  for row = 0 to 4 do
    for col = 0 to 3 do
      try
        if (PairsSet.mem (row, col) !skip)
        then
          begin
            raise Continue;
          end;

        let piece = board.(row).(col) in
        let (piece_kind, piece_index) = piece in
        (match piece_kind with
        | V ->
          skip := PairsSet.add (row + 1, col) !skip
        | H ->
          skip := PairsSet.add (row, col + 1) !skip
        | S ->
          skip := PairsSet.add (row, col + 1) !skip;
          skip := PairsSet.add (row + 1, col) !skip;
          skip := PairsSet.add (row + 1, col + 1) !skip
        | _ -> ()
        );

        for move_index = 0 to 3 do
          let (drow, dcol) = possible_moves'.(move_index) in
          let dmove = { drow = drow; dcol = dcol } in
          let opt_board = move_piece board piece dmove in

          match opt_board with
          | Some(board) ->
            result := !result @ [ Move(piece, dmove, board) ]
          | _ -> ()
        done;
      with Continue -> ()
    done;
  done;
  !result;;

exception NotEq of int
let compare_boards_good board1 board2 =
  let compare_ints x y =
  if x < y
  then
    -1
  else if x > y
  then
    1
  else
    0
  in
  try
    for row = 0 to 4 do
      let board1_row = board1.(row) and
        board2_row = board2.(row) in
      for col = 0 to 3 do
        let el1 = board1_row.(col) and
            el2 = board2_row.(col) in
        let (el1_kind, el1_number) = el1 and
          (el2_kind, el2_number) = el2 in
        let cmp = match el1_kind, el2_kind with
        | S, S | H, H | C, C | V, V | X, X ->
          compare_ints el1_number el2_number
        | S, _ ->
          1
        | _, S ->
          -1
        | H, _ ->
          1
        | _, H ->
          -1
        | C, _ ->
          1
        | _, C ->
          -1
        | V, _ ->
          1
        | _, V ->
          -1
        in
        if cmp != 0
        then raise (NotEq cmp)
      done;
    done;
    0
  with NotEq(res) -> res

module BoardSet = Set.Make(
struct
  type t = board

  let compare board1 board2 =
    compare_boards_good board1 board2;;
end
);;

module BoardListSet = Set.Make(
  struct
    type t = board list

    let rec compare bl1 bl2 = match bl1, bl2 with
      | [], [] -> 0
      | [], _ -> -1
      | _, [] -> 1
      | x :: xs, y :: ys ->
          let cmp = compare_boards_good x y in
          if cmp = 0
          then
            compare xs ys
          else
            cmp;;
  end
  );;

let oppps : (board list, _) set_operations = {
  empty = BoardListSet.empty;
  mem = BoardListSet.mem;
  add = BoardListSet.add
};;

(* type ('configuration, 'move) puzzle =
  { move : 'configuration -> 'move -> 'configuration;
    possible_moves : 'configuration -> 'move list;
    final : 'configuration -> bool } *)
let klotski : (board, move) puzzle = { move; possible_moves; final }

let solve_klotski (board : board) : board list =
  [ board ];;

(* TESTS *)
let test condition condition_str : unit =
  if condition
  then
    Printf.printf "Test OK: %s\n" condition_str
  else
    Printf.printf "Test FAIL: %s\n" condition_str;;

let compare_boards board1 board2 : bool =
  try
    for i = 0 to 4 do
      for j = 0 to 3 do
        if board1.(i).(j) != board2.(i).(j)
        then
          raise NotFound
        else
          ()
      done;
    done;
    true
  with NotFound -> false;;

let compare_opt_boards board1 board2 : bool =
  match board1, board2 with
  | Some(board1), Some(board2) -> compare_boards board1 board2
  | _ -> false;;

(* TEST: compare_opt_boards *)

test (compare_boards initial_board initial_board) "compare_boards initial_board initial_board";;
test (not (compare_boards initial_board initial_board_trivial)) "not (compare_boards initial_board initial_board_trivial)";;


(* TEST: move_piece for C blocks *)

let board = move_piece
  [|[|(X, 0); (H, 0); (H, 0); (C, 2)|];
    [|(C, 3); (V, 3); (V, 1); (V, 0)|];
    [|(C, 0); (V, 3); (V, 1); (V, 0)|];
    [|(X, 0); (S, 0); (S, 0); (V, 2)|];
    [|(C, 1); (S, 0); (S, 0); (V, 2)|]|]
  (C, 3)
  {dcol = 0; drow = -1};;

let expected_board = Some(
  [|[|(C, 3); (H, 0); (H, 0); (C, 2)|];
    [|(X, 0); (V, 3); (V, 1); (V, 0)|];
    [|(C, 0); (V, 3); (V, 1); (V, 0)|];
    [|(X, 0); (S, 0); (S, 0); (V, 2)|];
    [|(C, 1); (S, 0); (S, 0); (V, 2)|]|]
  );;

test (compare_opt_boards board expected_board) "Boards when moving C should be equal...";;

(* Testing move_piece for C blocks *)

let board_when_moving_V = move_piece
  [|[|(X, 0); (C, 1); (C, 3); (X, 0)|];
    [|(H, 0); (H, 0); (V, 1); (V, 3)|];
    [|(V, 0); (C, 0); (V, 1); (V, 3)|];
    [|(V, 0); (S, 0); (S, 0); (V, 2)|];
    [|(C, 2); (S, 0); (S, 0); (V, 2)|]|]
  (V, 3)
  {dcol = 0; drow = -1}

let expected_board_when_moving_V = Some(
  [|[|(X, 0); (C, 1); (C, 3); (V, 3)|];
    [|(H, 0); (H, 0); (V, 1); (V, 3)|];
    [|(V, 0); (C, 0); (V, 1); (X, 0)|];
    [|(V, 0); (S, 0); (S, 0); (V, 2)|];
    [|(C, 2); (S, 0); (S, 0); (V, 2)|]|]
  );;

test (compare_opt_boards board_when_moving_V expected_board_when_moving_V) "Boards when moving V should be equal...";;

(* testing move_piece for H blocks LEFT *)

let board_when_moving_H_left = move_piece
   [|[|(C, 2); (X, 0); (H, 0); (H, 0)|];
     [|(V, 1); (S, 0); (S, 0); (V, 3)|];
     [|(X, 0); (S, 0); (S, 0); (X, 0)|];
     [|(X, 0); (X, 0); (X, 0); (X, 0)|];
     [|(X, 0); (X, 0); (X, 0); (X, 0)|]|]
  (H, 0)
  {dcol = -1; drow = 0}

let expected_board_when_moving_H_left = Some(
  [|[|(C, 2); (H, 0); (H, 0); (X, 0)|];
    [|(V, 1); (S, 0); (S, 0); (V, 3)|];
    [|(X, 0); (S, 0); (S, 0); (X, 0)|];
    [|(X, 0); (X, 0); (X, 0); (X, 0)|];
    [|(X, 0); (X, 0); (X, 0); (X, 0)|]|]
  );;

test (compare_opt_boards board_when_moving_H_left expected_board_when_moving_H_left) "Boards when moving H should be equal (LEFT)...";;


(* testing move_piece for H blocks TOP *)

let board_when_moving_H_top = move_piece
  [|[|(C, 2); (X, 0); (X, 0); (X, 0)|];
    [|(V, 1); (H, 0); (H, 0); (V, 3)|];
    [|(X, 0); (S, 0); (S, 0); (X, 0)|];
    [|(X, 0); (X, 0); (X, 0); (X, 0)|];
    [|(X, 0); (X, 0); (X, 0); (X, 0)|]|]
  (H, 0)
  {dcol = 0; drow = -1}

let expected_board_when_moving_H_top = Some(
  [|[|(C, 2); (H, 0); (H, 0); (X, 0)|];
    [|(V, 1); (X, 0); (X, 0); (V, 3)|];
    [|(X, 0); (S, 0); (S, 0); (X, 0)|];
    [|(X, 0); (X, 0); (X, 0); (X, 0)|];
    [|(X, 0); (X, 0); (X, 0); (X, 0)|]|]
  );;

test (compare_opt_boards board_when_moving_H_top expected_board_when_moving_H_top) "Boards when moving H should be equal (TOP)...";;

(* testing move_piece for S'quare blocks RIGHT *)
let board_when_moving_S_right = move_piece
  [|[|(C, 2); (V, 0); (H, 0); (H, 0)|];
    [|(C, 0); (V, 0); (V, 2); (V, 3)|];
    [|(V, 1); (C, 3); (V, 2); (V, 3)|];
    [|(V, 1); (S, 0); (S, 0); (X, 0)|];
    [|(C, 1); (S, 0); (S, 0); (X, 0)|]|]
  (S, 0)
  {dcol = 1; drow = 0}

let expected_board_when_moving_S_right = Some(
  [|[|(C, 2); (V, 0); (H, 0); (H, 0)|];
    [|(C, 0); (V, 0); (V, 2); (V, 3)|];
    [|(V, 1); (C, 3); (V, 2); (V, 3)|];
    [|(V, 1); (X, 0); (S, 0); (S, 0)|];
    [|(C, 1); (X, 0); (S, 0); (S, 0)|]|]
  );;

test (compare_opt_boards board_when_moving_S_right expected_board_when_moving_S_right) "Boards when moving S should be equal (RIGHT)...";;

(* testing move_piece for S'quare blocks LEFT *)
let board_when_moving_S_left = move_piece
  [|[|(C, 2); (V, 0); (H, 0); (H, 0)|];
    [|(C, 0); (V, 0); (V, 2); (V, 3)|];
    [|(V, 1); (C, 3); (V, 2); (V, 3)|];
    [|(X, 0); (S, 0); (S, 0); (X, 0)|];
    [|(X, 0); (S, 0); (S, 0); (X, 0)|]|]
  (S, 0)
  {dcol = -1; drow = 0}

let expected_board_when_moving_S_left = Some(
  [|[|(C, 2); (V, 0); (H, 0); (H, 0)|];
    [|(C, 0); (V, 0); (V, 2); (V, 3)|];
    [|(V, 1); (C, 3); (V, 2); (V, 3)|];
    [|(S, 0); (S, 0); (X, 0); (X, 0)|];
    [|(S, 0); (S, 0); (X, 0); (X, 0)|]|]
  );;

test (compare_opt_boards board_when_moving_S_left expected_board_when_moving_S_left) "Boards when moving S should be equal (LEFT)...";;

(* testing move_piece for S'quare blocks TOP *)

let board_when_moving_S_top = move_piece
  [|[|(C, 2); (V, 0); (H, 0); (H, 0)|];
    [|(C, 0); (V, 0); (V, 2); (V, 3)|];
    [|(V, 1); (X, 0); (X, 0); (V, 3)|];
    [|(X, 0); (S, 0); (S, 0); (X, 0)|];
    [|(X, 0); (S, 0); (S, 0); (X, 0)|]|]
  (S, 0)
  {dcol = 0; drow = -1}

let expected_board_when_moving_S_top = Some(
  [|[|(C, 2); (V, 0); (H, 0); (H, 0)|];
    [|(C, 0); (V, 0); (V, 2); (V, 3)|];
    [|(V, 1); (S, 0); (S, 0); (V, 3)|];
    [|(X, 0); (S, 0); (S, 0); (X, 0)|];
    [|(X, 0); (X, 0); (X, 0); (X, 0)|]|]
  );;

test (compare_opt_boards board_when_moving_S_top expected_board_when_moving_S_top) "Boards when moving S should be equal (TOP)...";;

(* testing move_piece for S'quare blocks BOTTOM *)

let board_when_moving_S_bottom = move_piece
  [|[|(C, 2); (V, 0); (H, 0); (H, 0)|];
    [|(V, 1); (S, 0); (S, 0); (V, 3)|];
    [|(X, 0); (S, 0); (S, 0); (X, 0)|];
    [|(X, 0); (X, 0); (X, 0); (X, 0)|];
    [|(X, 0); (X, 0); (X, 0); (X, 0)|]|]
  (S, 0)
  {dcol = 0; drow = 1}

let expected_board_when_moving_S_bottom = Some(
  [|[|(C, 2); (V, 0); (H, 0); (H, 0)|];
    [|(V, 1); (X, 0); (X, 0); (V, 3)|];
    [|(X, 0); (S, 0); (S, 0); (X, 0)|];
    [|(X, 0); (S, 0); (S, 0); (X, 0)|];
    [|(X, 0); (X, 0); (X, 0); (X, 0)|]|]
  );;

test (compare_opt_boards board_when_moving_S_bottom expected_board_when_moving_S_bottom) "Boards when moving S should be equal (BOTTOM)...";;

(* TEST: clone_board *)
test ((clone_board initial_board) = initial_board)
      "(clone_board initial_board) = initial_board)";;

(* TEST: find_pos *)
test ((find_pos v0 initial_board) = { dcol = 0; drow = 0 })
      "((find_pos v0 initial_board) = { dcol = 0; drow = 0 })";;

test ((find_pos c3 initial_board) = { dcol = 3; drow = 4 })
      "((find_pos c3 initial_board) = { dcol = 3; drow = 4 })";;


let board_1 =
  [|[|(V, 0); (C, 0); (V, 3); (X, 0)|];
    [|(V, 0); (C, 1); (V, 3); (C, 3)|];
    [|(V, 1); (X, 0); (H, 0); (H, 0)|];
    [|(V, 1); (S, 0); (S, 0); (V, 2)|];
    [|(C, 2); (S, 0); (S, 0); (V, 2)|]|];;
let board_1_moves = possible_moves board_1;;
test ((List.length board_1_moves) = 3) "List.count board_1_moves = 3";;

let board_2 =
  [|[|(C, 0); (V, 3); (X, 0); (C, 2)|];
    [|(V, 0); (V, 3); (X, 0); (V, 2)|];
    [|(V, 0); (S, 0); (S, 0); (V, 2)|];
    [|(C, 1); (S, 0); (S, 0); (V, 1)|];
    [|(H, 0); (H, 0); (C, 3); (V, 1)|]|];;
let board_2_moves = possible_moves board_2;;
test ((List.length board_2_moves) = 2) "List.count board_2_moves = 2";;

let board_3 =
  [|[|(V, 1); (C, 1); (C, 3); (V, 2)|];
    [|(V, 1); (H, 0); (H, 0); (V, 2)|];
    [|(V, 0); (C, 0); (C, 2); (V, 3)|];
    [|(V, 0); (S, 0); (S, 0); (V, 3)|];
    [|(X, 0); (S, 0); (S, 0); (X, 0)|]|];;

let board_3_moves = possible_moves board_3;;
test ((List.length board_3_moves) = 2) "List.count board_3_moves = 2";;

(* TEST BoardSet) *)

(* S > H > C > V > X *)
let board_comparison_1 = (compare_boards_good
  [|[|(C, 3); (X, 0); (C, 1); (V, 2)|];
    [|(V, 1); (C, 2); (X, 0); (V, 2)|];
    [|(V, 1); (H, 0); (H, 0); (V, 0)|];
    [|(V, 3); (S, 0); (S, 0); (V, 0)|];
    [|(V, 3); (S, 0); (S, 0); (C, 0)|]|]
  [|[|(C, 3); (C, 2); (C, 1); (V, 2)|];
    [|(V, 1); (X, 0); (X, 0); (V, 2)|];
    [|(V, 1); (H, 0); (H, 0); (V, 0)|];
    [|(V, 3); (S, 0); (S, 0); (V, 0)|];
    [|(V, 3); (S, 0); (S, 0); (C, 0)|]|]
);;

let board_comparison_2 = (compare_boards_good
  [|[|(C, 0); (C, 1); (V, 2); (C, 3)|];
    [|(H, 0); (H, 0); (V, 2); (V, 3)|];
    [|(C, 2); (X, 0); (X, 0); (V, 3)|];
    [|(V, 1); (S, 0); (S, 0); (V, 0)|];
    [|(V, 1); (S, 0); (S, 0); (V, 0)|]|]
  [|[|(C, 1); (X, 0); (X, 0); (C, 2)|];
    [|(H, 0); (H, 0); (V, 1); (V, 0)|];
    [|(C, 3); (C, 0); (V, 1); (V, 0)|];
    [|(V, 2); (S, 0); (S, 0); (V, 3)|];
    [|(V, 2); (S, 0); (S, 0); (V, 3)|]|]
);;
test (board_comparison_2 = -1) "";;

Printf.printf "Starting solve_klotski...\n";;

let solution = solve_klotski initial_board;;

Printf.printf "Finished solve_klotski: %d\n" (List.length solution);;


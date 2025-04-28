initial(state(room1, room1, room2, no)).
goal(state(_, _, _, yes)).

adjacent(room1, room2).
adjacent(room2, room1).

move(state(M, B, K, no), push,  state(B, B, K, no)) :-
    adjacent(M, B).
    M == B.
    K == M.

solve(Actions) :-
    initial(Start),
    depth_first(Start, [Start], Actions).

depth_first(State, _, []) :-
    goal(State).
depth_first(State, Visited, [Act|Rest]) :-
    move(State, Act, Next),
    \+ member(Next, Visited),
    depth_first(Next, [Next|Visited], Rest).
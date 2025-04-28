append_lists([], B, B).
append_lists([H|T], B, [H|R]) :-
    append_lists(T, B, R).

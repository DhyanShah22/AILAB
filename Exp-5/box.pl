getbox(1).
getbox(2).
getbox(3).
getbox(4).
getbox(5).

box(1, black, 3).
box(2, black, 1).
box(3, white, 1).
box(4, black, 2).
box(5, white, 3).

all_distinct([]).
all_distinct([X|Xs]) :-
    maplist(dif(X), Xs),
    all_distinct(Xs).

owners(A,B,C,D,E) :-
    getbox(A), getbox(B), getbox(C), getbox(D), getbox(E),
    all_distinct([A,B,C,D,E]),
    box(A, Col, _), box(B, Col, _),
    box(D, Col2, _), box(E, Col2, _),
    box(C, _, Sz),  box(D, _, Sz),
    box(E, _, SzE), box(B, _, SzB), SzE < SzB.
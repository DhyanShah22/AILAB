prime(2).
prime(3).
prime(N) :-
    N > 3,
    N mod 2 =\= 0,
    \+ has_factor(N,3).

has_factor(N,F) :-
    F * F =< N,
    (N mod F =:= 0 ;
     F2 is F + 2,
     has_factor(N,F2)).

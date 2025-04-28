go :-
    write('Enter a number 1: '), read(X),
    write('Enter a number 2: '), read(Y),
    com(X, Y).

com(X, Y):-
    ( X > Y ->
        write('X is greater than Y')
    ; X =:= Y ->
        write(' X is equal to Y')
    ;
        write('Y is greater than X')
    ).
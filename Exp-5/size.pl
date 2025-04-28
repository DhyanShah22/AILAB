% box(Number, Color, Size)
box(1, black, big).
box(2, black, small).
box(3, white, small).
box(4, black, small).
box(5, white, big).
solve :-
    Boxes = [1,2,3,4,5],
    permutation(Boxes, [A,B,C,D,E]),

    box(A, ColorA, SizeA),
    box(B, ColorB, _),
    box(C, _, SizeC),
    box(D, ColorD, SizeD),
    box(E, ColorE, SizeE),

    % Anay and Bill: same color
    ColorA = ColorB,

    % Don and Eric: same color
    ColorD = ColorE,

    % Charlie and Don: same size
    SizeC = SizeD,

    % Eric's box smaller than Bill’s
    smaller(SizeE, SizeB),

    format("Anay has box ~w~n", [A]),
    format("Bill has box ~w~n", [B]),
    format("Charlie has box ~w~n", [C]),
    format("Don has box ~w~n", [D]),
    format("Eric has box ~w~n", [E]).
smaller(small, big).
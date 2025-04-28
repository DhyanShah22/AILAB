person(raj, 5.6, black, black).
person(heena, 4.6, black, black).
person(monu, 5.6, brown, black).
person(mohil, 5.2, brown, black).

height_56 :-
    person(Name, 5.6, _, _),
    write(Name), nl,
    fail.
height_56.  

height_56_brown_eyes :-
    person(Name, 5.6, brown, _),
    write(Name), nl,
    fail.
height_56_brown_eyes.
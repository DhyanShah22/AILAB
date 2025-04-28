position(raj, 'assistant professor').
position(ramu, 'assistant professor').
position(renu, 'assistant professor').
position(ina, 'associate professor').
position(nyasha, 'associate professor').

get_faculty_by_designation :-
    write('Enter designation (e.g., assistant professor): '),
    flush_output,
    read(Designation),
    nl,
    write('Faculty with designation '), write(Designation), write(':'), nl,
    display_faculty(Designation).

display_faculty(Designation) :-
    position(Name, Designation),
    write('- '), write(Name), nl,
    fail.
display_faculty(_).  

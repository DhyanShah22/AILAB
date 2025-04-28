:- dynamic at/2. 

at(monkey, floor).
at(box, floor).
at(banana, high).

climb(X) :- 
    at(monkey, floor),          
    at(X, floor),               
    at(banana, high),           
    retract(at(monkey, floor)),  
    assert(at(monkey, X)),      
    write('Monkey climbs the box.'),
    nl.

reach_banana :- 
    climb(box),                  
    at(monkey, box),              
    at(banana, high),            
    write('Monkey reaches the banana!').



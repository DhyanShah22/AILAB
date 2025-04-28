studies(raj,cse).
studies(mann,cse).
studies(dharmi,me).
studies(dev,ce).

teaches(neetu,cse).
teaches(cheery,ce).
teaches(ram,me).
teaches(rahul,ece).

professor(X,Y) :- teaches(X,B),studies(Y,B).
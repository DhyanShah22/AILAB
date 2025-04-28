symptoms(common_cold, [cough, runny_nose, sneezing, sore_throat]).
symptoms(flu, [high_fever, cough, headache, body_ache, fatigue]).

subset([], _).
subset([H|T], L) :- member(H, L), subset(T, L).

diagnose(Symptoms, Disease) :-
    symptoms(Disease, DiseaseSymptoms),
    subset(DiseaseSymptoms, Symptoms).
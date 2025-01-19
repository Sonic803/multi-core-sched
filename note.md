# Note

## Variabili

- N: numero di cpu
- T: tempo prima del prossimo processo
- D: tempo di esecuzione del processo
- p: probabilità che il processo sia cpu bound

## Cose da fare

- verification:
  - Use a trivial simplified case at first
    - Generator with constant rate and length
  - Consistency test
  - Degeneracy test
  - Continuity test
- calibration:
  - Possibile che sia necessario cercare su google dei valori sensati per la media di T, D e p.
  
## Note

Il warm up quanto dura, e dura uguale per tutti?

## Metriche

- Tempo in coda pronti
  - Quanto tempo aspetta da pronto ogni processo
- Utilizzazione della cpu
  - Per ogni cpu tempo running / tempo totale
- Numero di cpu attive in ogni istante
  - Per ogni istante di tempo, quante cpu sono attive
- Numero di processi in coda pronti
  - Per ogni istante di tempo, quanti processi sono in coda pronti

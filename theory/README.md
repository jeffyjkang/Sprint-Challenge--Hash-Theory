# Theory of Computation Sprint Challenge

## Computation

Fill out truth tables for the following expressions:

1. `(A ∨ ¬B)` (alternate: `(A || !B)`)

```
(f or t)=t
(f or f)=f
(t or t)=t
(t or f)=t

A     B     result
-------------------
0     0       T
0     1       F
1     0       T
1     1       T
```

2. `(¬A ∨ B) ∧ ¬(A ∧ ¬B)` (alternate: `(!A || B) && !(A && !B)`)

```
(t or f)=t and not(f and t)f=t =>t
(t or t)=t and not(f and f)f=t => t
(f or f)=f and not(t and t)t=f => f
(f or t)=t and not(t and f)f=t => t

A     B     result
-------------------
0     0       T
0     1       T
1     0       F
1     1       T
```

3. `¬(A ∨ B) ∨ ( (A ∨ C) ∧ ¬(B ∨ ¬C) )` (alternate: `!(A || B) || ( (A || C) && !(B || !C) )`)

- (Hint: Is it possible to calculate this using code?)

```
not(f or f)f=t or ((f or f)=f and not(f or t)t=f) => t
not(f or f)f=t or ((f or t)=t and not(f or f)f=t) => t
not(f or t)t=f or ((f or f)=f and not(t or t)t=f) => f
not(f or t)t=f or ((f or t)=t and not(t or f)t=f) => f
not(t or f)t=f or ((t or f)=t and not(f or t)t=f) => f
not(t or f)t=f or ((t or t)=t and not(f or f)f=t) => t
not(t or t)t=f or ((t or f)=t and not(t or t)t=f) => f
not(t or t)t=f or ((t or t)=t and not(t or f)t=f) => f

A     B     C     result
-------------------------
0     0     0       T
0     0     1       T
0     1     0       F
0     1     1       F
1     0     0       F
1     0     1       T
1     1     0       F
1     1     1       F
```

## STRETCH GOAL

The sum of two binary digits can be represented with the following truth table:

- A + B

```
A     B     CARRY   SUM
------------------------
0     0       0      0
0     1       0      1
1     0       0      1
1     1       1      0
```

This can be represented with boolean algebra like so:

- `SUM = A ⊕ B` (alternate: `A ^ B` or `A xor B`)
- `CARRY = A ∧ B` (alternate: `A && B`)

How can you represent the SUM and CARRY of adding THREE digits with a truth table and in boolean algebra?

- A + B + C

```
A     B     C      carry   sum
--------------------------------
0     0     0        0      0
0     0     1        0      1
0     1     0        0      1
0     1     1        1      0
1     0     0        0      1
1     0     1        1      0
1     1     0        1      0
1     1     1        1      1
```

- SUM = a xor b xor c
- CARRY = a && b + c && (a xor b)

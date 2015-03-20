#!/usr/bin/env python
import sys
if len(sys.argv) > 2:
    print "Too many arguments"
    sys.exit()
elif len(sys.argv) == 2:
    n =  int(sys.argv[1])
else:
    n = input("Enter n: ")
j = 1
S = [[j]]
if n == 0:
    print "[]"
elif n == 1:
    print S[0]
while j < n:
    j = j + 1
    for s in S:
        if len(s) == j - 1:
            p = list(s)
            p.append(j)
            if j < n:
                S.append(p)
            #elif j==n:
                #print p
            i = j - 1
            q = list(p)
            while i >= 1:
                aux = q[i-1]
                q[i-1] = q[i]
                q[i] = aux
                if j < n:
                    S.append(q)
                #elif j==n:
                    #print q
                i = i - 1
                q = list(q)

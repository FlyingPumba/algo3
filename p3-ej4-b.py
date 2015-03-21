#!/usr/bin/env python
import sys
import string

if len(sys.argv) > 2:
    print "Too many arguments"
    sys.exit()
elif len(sys.argv) == 2:
    n =  int(sys.argv[1])
    if n < 2:
        print "n must be greater than 2"
        sys.exit()
else:
    print "Too few arguments"
    sys.exit()

# helper functions
def solveAux(n, p):
    days = []
    if n == 2:
        days.append([[p[0], p[1]]])
    elif n == 3:
        days.append([[p[0], p[1]]])
        days.append([[p[0], p[2]]])
        days.append([[p[1], p[2]]])
    else:
        if n % 2 == 0:
            # divide
            p1 = p[:n/2]
            p2 = p[n/2:]
            games1 = solveAux(n/2, p1)
            games2 = solveAux(n/2, p2)
            # conquer
            # first merge games1 and games2
            for i in xrange(n/2 - 1):
                days.append([])
                days[i].append(games1[i])
                days[i].append(games2[i])
            # second create the following n/2 days
            for i in xrange(n/2):
                days.append([])

            for i in xrange(n/2):
                for j in xrange(n/2):
                    days[n/2 + i - 1].append([p1[j], p2[(j+i) % (n/2)]])
        else:
            # divide
            p1 = p[:(n+1)/2]
            p2 = p[(n-1)/2:]
            games1 = solveAux((n+1)/2, p1)
            games2 = solveAux((n-1)/2, p2)
            # conquer
            # first merge games1 and games2
            left_days = 0
            if len(games1) > len(games2):
                for i in xrange(len(games2)):
                    days.append([])
                    days[i].append(games1[i])
                    days[i].append(games2[i])
                for i in xrange(len(games1) - len(games2)):
                    days.append([])
                    days[len(games2) + i].append(games1[len(games2) +i])
                left_days = n - len(games1)
            else:
                for i in xrange(len(games1)):
                    days.append([])
                    days[i].append(games1[i])
                    days[i].append(games2[i])
                for i in xrange(len(games2) - len(games1)):
                    days.append([])
                    days[len(games1) + i].append(games2[len(games1) +i])
                left_days = n - len(games2)
            # second create the following left days
            current_days = len(days)
            for i in xrange(left_days):
                days.append([])

            for i in xrange(left_days):
                for j in xrange(left_days):
                    days[current_days + i - 1].append([p1[j], p2[(j+i) % (n/2)]])
            
    return days

def solve():
    return solveAux(n, participants)

# initialize
participants = []
for i in xrange(n):
    participants.append(string.lowercase[i])

days = solve()
if n % 2 == 0:
    for i in xrange(n-1):
        print "Day ", i+1,": ",days[i]
else:
    #print days
    for i in xrange(len(days)):
        print "Day ", i+1,": ",days[i]
    

#!/usr/bin/env python
import sys
import os
import time

if len(sys.argv) > 2:
    print "Too many arguments"
    sys.exit()
elif len(sys.argv) == 2:
    n =  int(sys.argv[1])
else:
    print "Too few arguments"
    sys.exit()

# helper functions
def display():
    os.system('clear')
    print "T1: ", list(reversed(towers[0]))
    print "T2: ", list(reversed(towers[1]))
    print "T3: ", list(reversed(towers[2]))

def attemptMove(i):
    destination = []
    if len(towers[i]) == 0:
        return destination

    for j in xrange(3):
        if abs(j-i) == 1 and (len(towers[j]) == 0 or towers[i][0] < towers[j][0]):
            destination.append(j)
    return destination

# initialize
towers = [[],[],[]]
for i in xrange(1,n+1):
    towers[0].append(i)

display()
a = raw_input('')

last_destination_tower = -1
last_origin_tower = -1
while len(towers[2]) != n:
    # check which tower should move next
    origin_tower = -1
    destination_tower = -1
    for origin_tower in xrange(3):
        possible_destinations = attemptMove(origin_tower)
        if len(possible_destinations) == 0:
            continue
        found = False
        for destination_tower in possible_destinations:
            if not (destination_tower == last_origin_tower and origin_tower == last_destination_tower):
                last_origin_tower = origin_tower
                last_destination_tower = destination_tower
                found = True
                break
        if found:
            break
    #print next_tower
    disc = towers[origin_tower][0]
    towers[origin_tower] = towers[origin_tower][1:]
    if origin_tower < destination_tower:
        towers[origin_tower + 1][:0] = [disc]
    else:
        towers[origin_tower - 1][:0] = [disc]
    display()
    #time.sleep(0.25) # sleep 250 milliseconds
    a = raw_input('')

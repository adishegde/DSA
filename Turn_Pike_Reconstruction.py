''' This program aims to solve the Turn Pike Reconstruction problem. It generates
a random point set, finds the distance set and reconstructs the point set. '''

import random
MAXPTS = 5    #Maximum points in generated point set
MAXDIST = 20  #Maximum distance of a point from origin in point set

def reconstruct(dist):
	if ((1 + 8 * len(dist)) ** (0.5) - 1) / 2 - int(((1 + 8 * len(dist)) ** (0.5) - 1) / 2) != 0:
		print "No solution! Invalid number of elements!"
		return

	allSolutions = list()
	pts = [0 for i in xrange((int(((1 + 8 * len(dist)) ** (0.5) - 1)) / 2)+1)]
	pts[-1] = dist.pop(dist.index(max(dist)))
	getPts(pts, dist, len(pts)-2, 1, allSolutions)
	if len(allSolutions) == 0:
		print "No solution!"
		return

	print "Solutions:"
	for soln in xrange(len(allSolutions)):
		print soln+1,") ",allSolutions[soln],"\n"

def getPts(pts, dist, x, y, allSolutions):
	if x+1==y:
		if pts not in allSolutions:
			allSolutions.append(pts[:])
		return

	removed = list()
	pts[x] = dist.pop(dist.index(max(dist)))
	removed.append(pts[x])
	try:
		for point in pts[1:y]+pts[x+1:]:
			dist.remove(abs(point-pts[x]))
			removed.append(abs(point-pts[x]))
		getPts(pts, dist, x-1, y, allSolutions)

	except ValueError:
		pass

	dist.extend(removed)
	removed[:]=[]
	pts[x] = 0

	try:
		pts[y] = dist.pop(dist.index(pts[-1] - max(dist)))
		removed.append(pts[y])
		for point in pts[1:y]+pts[x+1:]:
			dist.remove(abs(point-pts[y]))
			removed.append(abs(point-pts[y]))

		getPts(pts, dist, x, y+1, allSolutions)

	except ValueError:
		pass

	dist.extend(removed)
	removed[:]=[]
	pts[y] = 0

def genRandomPtSet(l):
	global MAXDIST
	pts = [0]
	for num in xrange(l-1):
		pts.append(random.randint(1,MAXDIST))
	pts.sort()
	return pts

def genDistSet(pts):
	d=list()
	for point1 in xrange(len(pts)-1):
		for point2 in xrange(point1+1,len(pts)):
			d.append(pts[point2]-pts[point1])
	d.sort()
	return d

def main():
	S=genRandomPtSet(random.randint(2,MAXPTS))
	D=genDistSet(S)
	print "Set of Points:\n",S,"\n"
	print "Set of Distances:\n",D,"\n"
	print "Using distance set to reconstruct point set..."
	reconstruct(D)

main()

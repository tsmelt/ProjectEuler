# 85.py
# Tyler_Smelt@hmc.edu
# 8/13/2012
# Python implementation of Problem 85 from projecteuler.net
# Finds rectangular grid with number of rectangles closest to 2,000,000

from datetime import datetime
from multiprocessing import Pool

def rects(x, y):
    """Calculates the number of rectangles in an x*y rectangular grid"""
    n = 0
    for i in range(x):
        for j in range(y):
            n += ((x - i) * (y - j))    
    return n
    
def rectlist(x):
    """Calculates rects for all values of y associated with a value of x"""
    target = 2000000
    y = 0
    num = 0
    N = [[] for i in range(x + 1)]
    while (y < x) and (num < target):
        y += 1
        num = rects(x, y)
        N[y] = abs(num - target)
    return N
        

if __name__ == '__main__':
    time_start = datetime.now()
    
    target = 2000000
    max_size = 2000
    
    print("Targeting {:,} rectangles with maximum grid dimension {:,}..."
          .format(target, max_size))
    
    X = range(max_size + 1)
    pool = Pool()
    N = pool.map(rectlist, X)
    mins = pool.map(min, N)
    pool.close()
    pool.join()
    
    min_x = mins.index(min(mins))
    min_y = N[min_x].index(min(N[min_x]))
    min_area = min_x * min_y
    actual_rects = rects(min_x, min_y)
    
    time_end = datetime.now()
    time_elapsed = (time_end - time_start).total_seconds()
    print("Finished in {} seconds".format(time_elapsed))

    print("Area of closest solution is {:,} ({:,} x {:,}) with {:,} rectangles"
          .format(min_area, min_x, min_y, actual_rects))
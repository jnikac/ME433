import numpy as np# to get access to ulab numpy
import time
arr1 = np.arange(0,1024,1, dtype=int)
a = np.sin(arr1)
b = np.sin(arr1 * 3)
c = np.sin(arr1 * 2)

arr = np.add(a,b,c)
sp = np.fft.fft(arr)

i = 0;
flag = True;
while flag:
    time.sleep(0.05)
    print("("+str(sp[i].real)+",)")
    i = i+1
    if i == 1024:
        flag = False




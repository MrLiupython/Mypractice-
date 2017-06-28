import random
import time
import sys
sys.setrecursionlimit(10000)
def Insertion_s(A):#元素规模17408 时间15.412 评价：D
    for j in range(1,len(A)):
        key,i = A[j],j-1
        while i >= 0 and A[i] > key:
            A[i+1] = A[i]
            i -= 1
        A[i+1] = key


def Merge(A,p,q,r):#元素规模17408 时间0.074 评价：S
    L , R = A[p:q+1],A[q+1:r+1]
    L.append(99999999)
    R.append(99999999)
    i , j = 0,0
    for k in range(p,r+1):
        if L[i] <=R[j]:
            A[k] = L[i]
            i += 1
        elif L[i] == 99999999 and R[j] == 99999999:
            return
        else:
            A[k] = R[j]
            j += 1
def Merge_s(A,p,r):
    if p < r:
        q = (p + r)//2
        Merge_s(A,p,q)
        Merge_s(A,q+1,r)
        Merge(A,p,q,r)


def Bubble_s(A):#元素规模17408 时间34.537 评价：F
    for i in range(len(A)):
        for j in range(len(A)-1,i+1,-1):
            if A[j] < A[j-1]:
                A[j],A[j-1] = A[j-1],A[j]


def Random_s(A):
    for i in range(len(A)):
        n = random.randint(i, len(A)-1)
        A[i],A[n] = A[n],A[i]


def Partition(A,p,r):#元素规模17408 时间2.724 评价：B 注：量超过一定界限会出错（可能栈溢出）
    # a = random.randint(0,len(A)-1)?混乱原因未解决
    # A[r],A[a] = A[a],A[r]
    x,i = A[r], p-1
    for j in range(p,r):
        if A[j] <= x:
            i += 1
            A[i],A[j] = A[j], A[i]
    A[i+1],A[r] = A[r],A[i+1]
    return i+1
def Quick_s(A,p,r):
    while p < r:
    # if p<r:
        q = Partition(A,p,r)
        Quick_s(A,p,q-1)
        p = q+1
        # Quick_s(A, q+1,r)

def Counting_s(A,k):#元素规模17408 时间0.010 评价：S+
    C = [0 for i in range(k)]
    B = [0 for i in range(len(A))]
    for i in range(len(A)):
        C[A[i]] = C[A[i]] +1
    for j in range(k):
        C[j] = C[j] + C[j-1]
    for n in range(len(A)-1,-1,-1):
        B[C[A[n]]-1] = A[n]
        C[A[n]] = C[A[n]] - 1
    return B

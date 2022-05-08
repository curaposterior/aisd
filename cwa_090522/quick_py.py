#!/usr/bin/python3

def wyznaczPivot(T, lewy, prawy):
    granica = lewy
    pivot = prawy
    for i in range(lewy, prawy):
        if T[i] < T[pivot]:
            zamiana = T[i]
            T[i] = T[granica]
            T[granica] = zamiana
            granica += 1
    zamianaPivota = T[granica]
    T[granica] = T[pivot]
    T[pivot] = zamianaPivota
    return granica

def sortuj_szybko(T, lewy, prawy):
    if lewy < prawy:
        pivot = wyznaczPivot(T, lewy, prawy)
        sortuj_szybko(T, lewy, pivot - 1)
        sortuj_szybko(T, pivot + 1, prawy)
    return T

if (__name__ == "__main__"):
    tablica = [15,53,7,2,546,6,8,1,67,5,2]
    print(sortuj_szybko(tablica, 0, 10))
#!/usr/bin/env python
# -*- coding:  utf-8 -*-
import numpy as np


def evalf(x):
    # 目的関数の値f(x)を計算する
    f = x[0]**2 + x[1]
    return f


def evalg(x):
    # fの勾配を計算する
    g = np.array([2*x[0], 1])
    return g


def evalh(x):
    # fのヘッセ行列を計算する
    H = np.array([[2, 0], [0, 0]])
    return H


def main():
    x = np.array([0.3, 5])
    f = evalf(x)
    g = evalg(x)
    H = evalh(x)
    print('f =', f, '\ng =', g, '\nH = \n', H)
if __name__ == '__main__':
    main()

# 数理工学実験 #テーマ5 #課題7
import numpy as np
import matplotlib.pyplot as plt

n = [2, 5, 10]


def evalA(i):  # 行列Aを生成する
    Z = np.random.rand(n[i], n[i])
    A = np.dot(Z.T, Z)
    return A


def evalf(A, x):  # 目的関数の値f(x)を計算する
    f = 0.5*np.dot(np.dot(A, x), x)
    return f


def evalg(A, x):  # fの勾配を計算する
    g = np.dot(A, x)
    return g


def evalh(A):  # fのヘッセ行列を計算する
    H = A
    return H


rho = 0.5  # バックトラック法のρ
kusai = 10**(-4)  # バックトラック法のξ

for i in range(3):

    epsilon = n[i]*10**(-6)  # 終了条件εの定義

    k1 = [0]*5  # 最急降下法の反復回数
    k2 = [0]*5  # ニュートン法の反復回数

    I = np.eye(n[i])  # 単位行列

    for j in range(5):
        An = evalA(i)
        print("An=", An)

        # 最急降下法ここから
        xk1 = np.array([1]*n[i])  # 初期点
        while k1[j] < 100000:
            if np.linalg.norm(evalg(An, xk1)) > epsilon:
                dk = -evalg(An, xk1)  # 降下方向
                tk = 1.0  # tの初期値
                while evalf(An, xk1+tk*dk) > evalf(An, xk1)+kusai*tk*np.dot(dk, evalg(An, xk1)):
                    tk = rho*tk  # ステップサイズ
                xk1 = xk1+tk*dk  # 点xkの更新
                k1[j] = k1[j]+1
            else:
                sp1 = xk1  # 停留点
                break
        print("最急降下法")
        print("n=", n[i], ",", j+1, "回目")
        print("最適解は、", sp1)
        print("最適値は、", evalf(An, sp1))
        print("k=", k1[j])
        # 最急降下法ここまで

        # ニュートン法ここから
        xk2 = np.array([1]*n[i])  # 初期点
        while k2[j] < 100000:  # 最大反復回数
            if np.linalg.norm(evalg(An, xk2)) > epsilon:
                w, v = np.linalg.eig(evalh(An))
                if np.all(w > 0):  # 正定値の場合
                    tau = 0
                else:
                    tau = np.abs(min(w))+10**(-2)  # ニュートン法の修正で用いるτ
                dk = -np.dot(np.linalg.inv(evalh(An)+tau*I),
                             evalg(An, xk2))  # 降下方向
                tk = 1.0  # tの初期値
                while evalf(An, xk2+tk*dk) > evalf(An, xk2)+kusai*tk*np.dot(dk, evalg(An, xk2)):
                    tk = rho*tk  # ステップサイズ
                xk2 = xk2+tk*dk  # 点xkの更新
                k2[j] = k2[j]+1
            else:
                sp2 = xk2  # 停留点
                break
        print("ニュートン法")
        print("n=", n[i], ",", j+1, "回目")
        print("最適解は、", sp2)
        print("最適値は、", evalf(An, sp2))
        print("k=", k2[j])
        # ニュートン法ここまで
        print("\n")

    print("最急降下法のkの平均=", (k1[0]+k1[1]+k1[2]+k1[3]+k1[4])/5.0)
    print("ニュートン法のkの平均=", (k2[0]+k2[1]+k2[2]+k2[3]+k2[4])/5.0)
    print("\n")

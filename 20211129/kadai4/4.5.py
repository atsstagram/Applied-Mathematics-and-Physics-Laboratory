# 数理工学実験 #テーマ5 #課題4,5
import numpy as np
import matplotlib.pyplot as plt


def evalf(x):
    # 目的関数の値f(x)を計算する
    f = x[0]**2 + np.exp(x[0]) + x[1]**4 + x[1]**2 - 2*x[0]*x[1] + 3
    return f


def evalg(x):
    # fの勾配を計算する
    g = np.array([2*x[0] + np.exp(x[0]) - 2*x[1], 4*x[1]**3 + 2*x[1] - 2*x[0]])
    return g


def evalh(x):
    # fのヘッセ行列を計算する
    H = np.array([[2 + np.exp(x[0]), -2], [-2, 12*x[1]**2 + 2]])
    return H


epsilon = 2*10**(-6)  # 終了条件εの定義

# 最急降下法ここから
k = 0
xk = np.array([1.0, 1.0])  # 初期点
rho = 0.5  # バックトラック法のρ
kusai = 10**(-4)  # バックトラック法のξ
while k < 100:
    if np.linalg.norm(evalg(xk)) > epsilon:
        dk = -evalg(xk)  # 降下方向
        tk = 1.0  # tの初期値
        while evalf(xk+tk*dk) > evalf(xk)+kusai*tk*np.dot(dk, evalg(xk)):
            tk = rho*tk  # ステップサイズ
        xk = xk+tk*dk  # 点xkの更新
        k = k+1
    else:
        sp1 = xk  # 停留点
        break
print("最急降下法により求めた停留点")
print(sp1)
print("k=", k)
# 最急降下法ここまで

print("\n")

# ニュートン法ここから
k = 0
xk = np.array([1.0, 1.0])  # 初期点
rho = 0.5  # バックトラック法のρ
kusai = 10**(-4)  # バックトラック法のξ
while k < 100:  # 最大反復回数
    if np.linalg.norm(evalg(xk)) > epsilon:
        dk = -np.dot(np.linalg.inv(evalh(xk)), evalg(xk))  # 降下方向
        tk = 1.0  # tの初期値
        while evalf(xk+tk*dk) > evalf(xk)+kusai*tk*np.dot(dk, evalg(xk)):
            tk = rho*tk  # ステップサイズ
        xk = xk+tk*dk  # 点xkの更新
        k = k+1
    else:
        sp2 = xk  # 停留点
        break
print("ニュートン法により求めた停留点")
print(sp2)
print("k=", k)
# ニュートン法ここまで

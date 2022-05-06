# 数理工学実験 #テーマ5 #課題6
import numpy as np
import matplotlib.pyplot as plt

y = [1.5, 2.25, 2.625]


def evalfi(x, i):  # f_i(x)
    fi = y[i]-x[0]*(1-x[1]**(i+1))
    return fi


def evalgi(x, i):  # ∇(f_i(x))
    gi = np.array([-(1-x[1]**(i+1)), (i+1)*x[0]*x[1]**i])
    return gi


def evalhi(x, i):  # ∇^2(f_i(x))
    hi = np.array(
        [[0, (i+1)*x[1]**i], [(i+1)*x[1]**i, i*(i+1)*x[0]*x[1]**(i-1)]])
    return hi


def evalf(x):  # 目的関数の値f(x)を計算する
    f = 0
    for i in range(3):
        f = f+evalfi(x, i)**2
    return f


def evalg(x):  # fの勾配を計算する
    g = np.array([0, 0])
    for i in range(3):
        g = g+2*(evalfi(x, i)*evalgi(x, i))
    return g


def evalh(x):  # fのヘッセ行列を計算する
    H = np.array([[0, 0], [0, 0]])
    for i in range(3):
        m = evalgi(x, i)
        M = np.array([[m[0]**2, m[0]*m[1]], [m[1]*m[0], m[1]**2]])
        H = H+2*(evalfi(x, i)*evalhi(x, i))+2*M
    return H


epsilon = 2*10**(-6)  # 終了条件εの定義

# 最急降下法ここから
k = 0
xk = np.array([2.0, 0])  # 初期点
rho = 0.5  # バックトラック法のρ
kusai = 10**(-4)  # バックトラック法のξ
while k < 1000:
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
print("最急降下法")
print("最適解は、", sp1)
print("最適値は、", evalf(sp1))
print("k=", k)
# 最急降下法ここまで

print("\n")

# ニュートン法ここから
# np.nan_to_num()でnan:0^(-1)を0で置換
k = 0
xk = np.array([2.0, 0])  # 初期点
rho = 0.5  # バックトラック法のρ
kusai = 10**(-4)  # バックトラック法のξ
I = np.array([[1, 0], [0, 1]])  # 単位行列
while k < 1000:  # 最大反復回数
    if np.linalg.norm(evalg(xk)) > epsilon:
        # fのヘッセ行列の固有値（と固有ベクトル）を取得
        w, v = np.linalg.eig(np.nan_to_num(evalh(xk)))
        if w[0] > 0 and w[1] > 0:  # 正定値の場合
            tau = 0
        else:
            tau = np.abs(min(w))+10**(-2)  # ニュートン法の修正で用いるτ
        dk = -np.dot(np.linalg.inv(np.nan_to_num(evalh(xk)+tau*I)),
                     evalg(xk))  # 降下方向
        tk = 1.0  # tの初期値
        while evalf(xk+tk*dk) > evalf(xk)+kusai*tk*np.dot(dk, evalg(xk)):
            tk = rho*tk  # ステップサイズ
        xk = xk+tk*dk  # 点xkの更新
        k = k+1
    else:
        sp2 = xk  # 停留点
        break
print("ニュートン法")
print("最適解は、", sp2)
print("最適値は、", evalf(sp2))
print("k=", k)
# ニュートン法ここまで
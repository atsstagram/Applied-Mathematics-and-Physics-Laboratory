# 数理工学実験 #テーマ5 #課題3
import numpy as np
import matplotlib.pyplot as plt


def func(x):  # f(x)の関数定義
    return 1/3.0*x**3-x**2-3*x+5/3.0


def dfunc(x):  # f(x)の導関数f'(x)の関数定義
    return x**2-2*x-3


def d2func(x):  # f''(x)の関数定義
    return 2*x-2


x = np.arange(-10, 10, 0.1)
y = func(x)
plt.plot(x, y, "red")
plt.xlim(-10, 10)
plt.ylim(-10, 10)
plt.axhline(0, c="black")
plt.axvline(0, c="black")
plt.xlabel("x")
plt.ylabel("f(x)")
plt.title("Graph of f(x)")
plt.show()

epsilon = 10**(-6)  # 終了条件εの定義

# 最急降下法ここから
k = 0
xk = 0  # 初期点
while k < 100:
    if np.abs(dfunc(xk)) > epsilon:
        dk = -dfunc(xk)  # 降下方向
        tk = 1/(k+1)  # ステップサイズ
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
xk = 5  # 初期点
tk = 1  # ステップサイズ
while k < 100:  # 最大反復回数
    if np.abs(dfunc(xk)) > epsilon:
        dk = -dfunc(xk)/d2func(xk)  # 降下方向
        xk = xk+tk*dk  # 点xkの更新
        k = k+1
    else:
        sp2 = xk  # 停留点
        break
print("ニュートン法により求めた停留点")
print(sp2)
print("k=", k)
# ニュートン法ここまで

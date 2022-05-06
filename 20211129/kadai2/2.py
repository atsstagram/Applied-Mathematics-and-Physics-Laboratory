# 数理工学実験 #テーマ5 #課題2
import numpy as np
import matplotlib.pyplot as plt


def func(x):  # f(x)の関数定義
    return x**3+2*x**2-5*x-6


def dfunc(x):  # f(x)の導関数f'(x)の関数定義
    return 3*x**2+4*x-5


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

# 二分法ここから
a = [-5.0, 0.0, 0.0]  # 異なる３つの零点に対するaの初期値
b = [-2.5, -2.5, 2.5]  # 異なる３つの零点に対するbの初期値
c = [(a[0]+b[0])/2, (a[1]+b[1])/2, (a[2]+b[2])/2]

zero1 = [None]*3  # 二分法により求めた零点を格納する配列

while zero1[0] is None or zero1[1] is None or zero1[2] is None:
    for i in range(0, 3, 1):
        if np.abs(func(c[i])) > epsilon:
            c[i] = (a[i]+b[i])/2
            if func(c[i]) < 0:
                a[i] = c[i]
            else:
                b[i] = c[i]
        else:
            zero1[i] = c[i]

print("二分法により求めた零点")
for i in range(0, 3, 1):
    print(zero1[i])
# 二分法ここまで

print("\n")

# ニュートン法ここから
xk = [-3.75, -1.25, 2.5]  # 零点付近にある初期点x_0

zero2 = [None]*3  # ニュートン法により求めた零点を格納する配列

while zero2[0] is None or zero2[1] is None or zero2[2] is None:
    for i in range(0, 3, 1):
        if np.abs(func(xk[i])) > epsilon:
            deltaX = -func(xk[i])/dfunc(xk[i])
            xk[i] = xk[i]+deltaX
        else:
            zero2[i] = xk[i]

print("ニュートン法により求めた零点")
for i in range(0, 3, 1):
    print(zero2[i])
# ニュートン法ここまで

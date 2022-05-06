import numpy as np
import matplotlib.pyplot as plt

x = np.arange(-5, 5, 0.1)
y = np.sin(x)
plt.plot(x, y, "red")
plt.xlim(-5, 5)
plt.ylim(-5, 5)
plt.axhline(0, c="black")
plt.axvline(0, c="black")
plt.xlabel("x")
plt.ylabel("y")
plt.title("Graph of y=sin(x)")
plt.show()

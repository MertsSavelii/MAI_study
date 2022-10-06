# Мерц Савелий Павлович
# лабораторная по КГ №1
# вариант 17: x = a*ф - b*sin(ф)
#             y = a - b*cos(ф)
#             a < b, A <= ф <= B

import matplotlib.pyplot as plt
import numpy as np
import sympy as sp

fig = plt.figure('Мерц Савелий. 17 Вариант. Лабораторная работа №1', figsize=(7, 6))
plt.title('x = a*ф - b*sin(ф), y = a - b*cos(ф), a < b, A <= ф <= B')
print(' Введите ограничения на ф')
A = int(input())
B = int(input())
phi = np.arange(A, B, 0.01)
print(' Введите значение параметрров a и b')
a = int(input())
b = int(input())
a = min(a, b)
b = max(a, b)
X = a * phi - b * np.sin(phi)
Y = a - b * np.cos(phi)
plt.plot(X, Y)
plt.show()
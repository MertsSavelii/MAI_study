import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d.art3d import Poly3DCollection
from matplotlib.widgets import Button


def TransparentON(event):
    axis.add_collection3d(Poly3DCollection(
        frame, facecolors=[0.5, 0.4, 0.3], alpha=0.7, linewidths=1, edgecolors='black'))


def TransparentOFF(event):
    axis.add_collection3d(Poly3DCollection(
        frame, facecolors=[0.5, 0.4, 0.3], alpha=1, linewidths=1, edgecolors='black'))


fig = plt.figure('Мерц Савелий. Вариант №14. Лабораторная работа №2', figsize=(7, 6))
axis = fig.add_subplot(111, projection='3d')

buttonON = fig.add_subplot(863)
btnON = Button(buttonON, 'ON')
btnON.on_clicked(TransparentON)
btnON.color = '#778899'

buttonOFF = fig.add_subplot(864)
btnOFF = Button(buttonOFF, 'OFF')
btnOFF.on_clicked(TransparentOFF)
btnOFF.color = '#778899'

xC = 0
yC = 0
zC = 0
R = 10
H = 15

p = np.array([
    [xC - R, yC, zC],
    [xC - 0.5 * R, yC - 3**0.5 / 2 * R, zC],
    [xC + 0.5 * R, yC - 3**0.5 / 2 * R, zC],
    [xC + R, yC, zC],
    [xC + 0.5 * R, yC + 3**0.5 / 2 * R, zC],
    [xC - 0.5 * R, yC + 3**0.5 / 2 * R, zC],
    [xC - R + 4, yC, zC + H],
    [xC - 0.5 * R + 4, yC - 3 ** 0.5 / 2 * R, zC + H],
    [xC + 0.5 * R + 4, yC - 3 ** 0.5 / 2 * R, zC + H],
    [xC + R + 4, yC, zC + H],
    [xC + 0.5 * R + 4, yC + 3 ** 0.5 / 2 * R, zC + H],
    [xC - 0.5 * R + 4, yC + 3 ** 0.5 / 2 * R, zC + H]
])
frame = [
    [p[0], p[1], p[2], p[3], p[4], p[5]],
    [p[6], p[7], p[8], p[9], p[10], p[11]],
    [p[0], p[1], p[7], p[6]],
    [p[1], p[2], p[8], p[7]],
    [p[2], p[3], p[9], p[8]],
    [p[3], p[4], p[10], p[9]],
    [p[4], p[5], p[11], p[10]],
    [p[5], p[0], p[6], p[11]],
]

axis.scatter3D(p[:, 0], p[:, 1], p[:, 2], color='black')

axis.add_collection3d(Poly3DCollection(
    frame, facecolors=[0.5, 0.4, 0.3], alpha=0.7, linewidths=1, edgecolors='black'))

axis.set_xlabel('X', fontsize=20, color='black')
axis.set_ylabel('Y', fontsize=20, color='black')
axis.set_zlabel('Z', fontsize=20, color='black')
axis.set_title('\"Призма - 7-угольник\"\nПрозрачность')

plt.show()

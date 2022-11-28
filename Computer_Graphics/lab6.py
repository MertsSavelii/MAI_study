from OpenGL.GL import *
from OpenGL.GLU import *
from OpenGL.GLUT import *
import numpy as np
import sys
import threading
import time
from itertools import cycle

#ccordinates
xrot = 0
yrot = 0
zrot = 4
#constant
amountInList = 100
f = 4
s = 3
third = 2
thurs = 6
c = 1.5
a = 1.2
z_h = 15
z_l = 5
intensiv = 10
reflection = 128
light_coord = (20, 30, 30)
size1 = 4
appr = 100


def drawBox():
    global xrot, yrot, reflection, z_h, z_l, appr, a, c
    glPushMatrix()
    glMaterialf(GL_FRONT, GL_SHININESS, reflection)
    draw(z_h, z_l, appr, a, c)
    glPopMatrix()
    glutSwapBuffers()


def init():
    glShadeModel(GL_SMOOTH)
    glEnable(GL_CULL_FACE)
    glEnable(GL_DEPTH_TEST)
    glEnable(GL_LIGHTING)
    light0_specualar = [0.7, 0.7, 0.2]
    light0_position = [0.0, 0.0, 1.0, 1.0]
    light0_spot_direction = [0.0, 0.0, -1.0]
    glEnable(GL_LIGHT0)
    glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specualar)
    glLightfv(GL_LIGHT0, GL_POSITION, light0_position)
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 30)
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light0_spot_direction)
    glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 15.0)
    glEnable(GL_LIGHT0)

def draw(z_h, z_l, appr,a, c):
    u = np.linspace(0, 2 * np.pi, int(appr*100))
    v = np.linspace(-1000,1000,int(appr*100))
    verts = []
    for i in range(appr*100 - 1):
        temp = c * np.cosh(u[i])
        if((z_h > temp) and (temp > z_l)):
            verts.append(((a * np.sinh(u[i]) * np.cos(v[i])),(a * np.sinh(u[i]) * np.sin(v[i])),(c * np.cosh(u[i]))))
    glBegin(GL_POLYGON)
    for v in verts:
        glVertex3fv(v)
    glEnd()

def reshape(width, height):
    glViewport(0, 0, width, height)
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    gluPerspective(60.0, float(width)/float(height), 1.0, 60.0)
    glMatrixMode(GL_MODELVIEW)
    glLoadIdentity()
    gluLookAt(0.0, 0.0, 0.0, 1.0, -1.0, 1.0, 10.0, 1, 0.0)


def display():
    global size1
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
    glMatrixMode(GL_MODELVIEW)
    glLoadIdentity()
    gluLookAt(-20, -20, -15, 10, 10, 20, 0, 0, 10)
    glTranslatef(size1, size1, size1)
    glRotatef(xrot, 1, 0, 0)
    glRotatef(yrot, 0, 0, 1)
    glRotatef(zrot, 0, 1, 0)
    drawBox()

def specialkeys(key, x, y):
    global xrot, yrot, zrot, size1
    if key == b'w':
        xrot += 2
    elif key == b's':
        xrot -= 2
    elif key == b'a':
        yrot += 2
    elif key == b'd':
        yrot -= 2
    elif key == b'q':
        zrot += 2
    elif key == b'e':
        zrot -= 2
    elif key == b'=':
        size1 += 1
    elif key == b'-':
        size1 -= 1
    elif key == b'c':
        app_change(appr + 1)
    elif key == b'v':
        app_change(appr - 1)
    elif key == b'p':
        exit(0)
    glutPostRedisplay()


def rotate():
    global zrot, xrot, yrot, f, s, third, thurs, amountInList
    u = np.linspace(0, 2 * np.pi, int(amountInList))
    speed = []
    for i in range(amountInList):
        speed.append((f + s * np.sin(third * u[i] + thurs)) * 0.001)
        for val in cycle(speed):
            print(val)
            begin = time.time()
            while time.time() - begin < 1:
                xrot += val
                yrot += val
                glutPostRedisplay()

def app_change(x):
    global appr
    appr = x
    glutPostRedisplay()
    return 0


def main():
    glutInit(sys.argv)
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH)
    glutInitWindowSize(500, 500)
    glutInitWindowPosition(0, 0)
    glutCreateWindow("lab6")
    glutDisplayFunc(display)
    glutReshapeFunc(reshape)
    glutKeyboardFunc(specialkeys)
    init()
    glutMainLoop()

if __name__ == "__main__":
   main()
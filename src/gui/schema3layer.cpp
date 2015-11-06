#include "schema3layer.h"



Schema3Layer::Schema3Layer(QWidget* parent): QOpenGLWidget(parent)
{
}



void Schema3Layer::initializeGL()
{
    //glClearColor(Qt::black);
    glShadeModel(GL_FLAT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
}



void Schema3Layer::resizeGL(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    GLfloat x = GLfloat(width)/height;
    glFrustum(-x, +x, -1.0, +1.0, 4.0, 15.0);
    glMatrixMode(GL_MODELVIEW);
}



void Schema3Layer::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    draw();
}



void Schema3Layer::draw()
{
    static const GLfloat P1[3] = { 0.0, -1.0, +2.0 };
    static const GLfloat P2[3] = { +1.73205081, -1.0, -1.0 };
    static const GLfloat P3[3] = { -1.73205081, -1.0, -1.0 };
    static const GLfloat P4[3] = { 0.0, +2.0, 0.0 };
    static const GLfloat* const coods[4][3] =
    {
        {P1, P2, P3}, {P1, P3, P4}, {P1, P4, P2}, {P2, P4, P3}
    };

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -10.0);
    glRotatef(rotationX, 1.0, 0.0, 0.0);
    glRotatef(rotationY, 0.0, 1.0, 0.0);
    glRotatef(rotationZ, 0.0, 0.0, 1.0);

    for(int i=0; i<4; i++)
    {
        glLoadName(i);
        glBegin(GL_TRIANGLES);
        //
        for(int j=0; j<3; ++j)
        {
            glVertex3f(coods[i][j][0], coods[i][j][1], coods[i][j][2]);
        }
        glEnd();
    }
}

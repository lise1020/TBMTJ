#include "schema3layer.h"
#include <QMouseEvent>



Schema3Layer::Schema3Layer(QWidget* parent): QOpenGLWidget(parent)
{
    //setFormat(QGLFormat(QGL::DoubleBuffer) | QGL::DepthBuffer);
    rotationX = -21.0;
    rotationY = -57.0;
    rotationZ =   0.0;
}



void Schema3Layer::initializeGL()
{
    /* set viewing projection */
    glMatrixMode(GL_PROJECTION);
    glFrustum(-0.5F, 0.5F, -0.5F, 0.5F, 1.0F, 3.0F);

    /* position viewer */
    glMatrixMode(GL_MODELVIEW);
    glTranslatef(0.0F, 0.0F, -2.0F);

    /* position object */
    glRotatef(30.0F, 1.0F, 0.0F, 0.0F);
    glRotatef(30.0F, 0.0F, 1.0F, 0.0F);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
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
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -10.0);
    glRotatef(rotationX, 0.0, 0.0, 0.0);
    glRotatef(rotationY, 0.0, 0.0, 0.0);
    glRotatef(rotationZ, 0.0, 0.0, 0.0);


    static GLfloat center1[3] = {1.0, 0.0, 0.0};
    static GLfloat  color1[3] = {0.0, 0.0, 1.0};
    static GLfloat length1[3] = {0.5, 0.5, 0.5};
    drawCuboid(center1, length1, color1);

    static GLfloat center2[3] = {0.0, 0.0, 0.0};
    static GLfloat  color2[3] = {0.0, 1.0, 0.0};
    static GLfloat length2[3] = {0.5, 0.5, 0.5};
    drawCuboid(center2, length2, color2);

    static GLfloat center3[3] = {-1.0, 0.0, 0.0};
    static GLfloat  color3[3] = {1.0, 0.0 ,0.0 };
    static GLfloat length3[3] = {0.5, 0.5, 0.5};
    drawCuboid(center3, length3, color3);


    glBegin(GL_LINES);
        glColor3f(0.0f,0.0f,0.0f);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 1.0f, 0.0f);
    glEnd();
}



void Schema3Layer::mousePressEvent(QMouseEvent* event)
{
    lastPos = event->pos();
}



void Schema3Layer::mouseMoveEvent(QMouseEvent* event)
{
    GLfloat dx = GLfloat(event->x() - lastPos.x()) / width();
    GLfloat dy = GLfloat(event->y() - lastPos.y()) / height();

    if(event->buttons() & Qt::LeftButton)
    {
        rotationX += 180*dy;
        rotationY += 180*dx;
        update();//
    }
    else if(event->buttons() & Qt::RightButton)
    {
        rotationX += 180*dy;
        rotationY += 180*dx;
        update();//
    }
    lastPos = event->pos();
}



void Schema3Layer::drawCuboid(const GLfloat center[3], const GLfloat length[3], const GLfloat color[3])
{
    GLfloat xl = length[0], yl = length[1], zl = length[2];
    GLfloat xc = center[0], yc = center[1], zc = center[2];
    glColor3f(color[0], color[1], color[2]);

    glBegin(GL_QUADS);
        /* Top */
        glNormal3f( 0.0F, 0.0F, 1.0F);
        glVertex3f( xl+xc, yl+yc,-zl+zc);
        glVertex3f(-xl+xc, yl+yc,-zl+zc);
        glVertex3f(-xl+xc, yl+yc, zl+zc);
        glVertex3f( xl+xc, yl+yc, zl+zc);
        /* Bottom */
        glNormal3f( 0.0F, 0.0F,-1.0F);
        glVertex3f( xl+xc,-yl+yc, zl+zc);
        glVertex3f(-xl+xc,-yl+yc, zl+zc);
        glVertex3f(-xl+xc,-yl+yc,-zl+zc);
        glVertex3f( xl+xc,-yl+yc,-zl+zc);
        /* Front */
        glNormal3f( 0.0F, 1.0F, 0.0F);
        glVertex3f( xl+xc, yl+yc, zl+zc);
        glVertex3f(-xl+xc, yl+yc, zl+zc);
        glVertex3f(-xl+xc,-yl+yc, zl+zc);
        glVertex3f( xl+xc,-yl+yc, zl+zc);
        /* Back */
        glNormal3f( 0.0F,-1.0F, 0.0F);
        glVertex3f( xl+xc,-yl+yc,-zl+zc);
        glVertex3f(-xl+xc,-yl+yc,-zl+zc);
        glVertex3f(-xl+xc, yl+yc,-zl+zc);
        glVertex3f( xl+xc, yl+yc,-zl+zc);
        /* Left */
        glNormal3f( 1.0F, 0.0F, 0.0F);
        glVertex3f(-xl+xc, yl+yc, zl+zc);
        glVertex3f(-xl+xc, yl+yc,-zl+zc);
        glVertex3f(-xl+xc,-yl+yc,-zl+zc);
        glVertex3f(-xl+xc,-yl+yc, zl+zc);
        /* Right */
        glNormal3f(-1.0F, 0.0F, 0.0F);
        glVertex3f( xl+xc, yl+yc,-zl+zc);
        glVertex3f( xl+xc, yl+yc, zl+zc);
        glVertex3f( xl+xc,-yl+yc, zl+zc);
        glVertex3f( xl+xc,-yl+yc,-zl+zc);
    glEnd();
}

#ifndef SCHEMA3LAYER_H
#define SCHEMA3LAYER_H
#include <QOpenGLWidget>



class Schema3Layer: public QOpenGLWidget
{
    Q_OBJECT

public:
    explicit Schema3Layer(QWidget* parent = 0);

protected:
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);

private:
    void draw();
    void drawCuboid(const GLfloat center[], const GLfloat length[], const GLfloat color[]);

private:
    GLfloat rotationX;
    GLfloat rotationY;
    GLfloat rotationZ;
    QPoint lastPos;
};



#endif // SCHEMA3LAYER_H

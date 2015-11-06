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

private:
    void draw();

private:
    GLfloat rotationX;
    GLfloat rotationY;
    GLfloat rotationZ;
};



#endif // SCHEMA3LAYER_H

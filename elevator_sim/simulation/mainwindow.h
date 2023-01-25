#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QElapsedTimer>
#include <QTimer>
#include <QPushButton>

#include "simulation.h"
#include "elevator_output.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(elevator_output *out, QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void setMotorSpeed(float speed) { sim.setMotorSpeed(speed); }
    void setLampState(lamp_state lamps) { myScene.setLampState(lamps); }
    void setDoorsOpen(bool open) { sim.setDoorsOpen(open); }

private:
    Ui::MainWindow *ui;
    QElapsedTimer sim_timer;
    Simulation sim;
    QTimer sim_tick;
    QTimer refresh_tick;
    uint64_t ticks = 0;
    QGraphicsScene scene;
    class MyScene {
        QGraphicsScene *scene;
        QGraphicsRectItem *carriage;
        QGraphicsRectItem *doors[2];
        QGraphicsEllipseItem *lamps[5];
        QGraphicsEllipseItem *emergency_lamp;
        QBrush brush_lamp_off, brush_lamp_on, brush_lamp_emergency;
    public:
        MyScene(QGraphicsScene *scene);
        void setElevatorHeight(float pos);
        void setDoorsClosed(bool closed);
        void setLampState(lamp_state state);
        void setError(bool error);
    } myScene;

    static const int button_count = 7;
    struct buttons_ty {
        QPushButton *button;
        button_state bit;
    } (*buttons);

    void updateScene();
    void updateSimulation();

    elevator_output *out;
    void button_pressed(button_state button);
    void button_released(button_state button);
};
#endif // MAINWINDOW_H

#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QPropertyAnimation>
#include <QGraphicsItemAnimation>
#include <QGraphicsRectItem>
#include <QSlider>

#include <iostream>
#include <iomanip>

MainWindow::MainWindow(elevator_output *out, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , scene(0,0,200,598)
    , myScene(&scene)
    , out(out)
{
    ui->setupUi(this);
    ui->graphicsView->setScene(&scene);
    sim_timer.start();
    sim_tick.start(1);
    QObject::connect(&sim_tick, &QTimer::timeout,
                     this, &MainWindow::updateSimulation);
    /* Hard-coded 60Hz refresh rate. Yuck. */
    refresh_tick.start(16);
    QObject::connect(&refresh_tick, &QTimer::timeout,
                     this, &MainWindow::updateScene);

    buttons = new buttons_ty[button_count] {
        {ui->buttonFloor0,    BUTTON_STATE_FLOOR0},
        {ui->buttonFloor1,    BUTTON_STATE_FLOOR1},
        {ui->buttonFloor2,    BUTTON_STATE_FLOOR2},
        {ui->buttonFloor3,    BUTTON_STATE_FLOOR3},
        {ui->buttonFloor4,    BUTTON_STATE_FLOOR4},
        {ui->buttonEmergency, BUTTON_STATE_EMERGENCY},
        {ui->buttonStart,     BUTTON_STATE_START},
    };
    for (unsigned i = 0; i < button_count; ++i) {
        QObject::connect(buttons[i].button, &QPushButton::pressed,
                         std::bind(&MainWindow::button_pressed, this,
                                   buttons[i].bit));
        QObject::connect(buttons[i].button, &QPushButton::released,
                         std::bind(&MainWindow::button_released, this,
                                   buttons[i].bit));
    }
}

MainWindow::~MainWindow()
{
    {
        std::lock_guard<std::mutex> guard(out->mutex);
        out->simulation_stopped = true;
    }
    refresh_tick.stop();
    sim_tick.stop();
    delete ui;
}

MainWindow::MyScene::MyScene(QGraphicsScene *scene) : scene(scene),
    brush_lamp_off(QColor::fromRgb(200,200,200)),
    brush_lamp_on(QColor::fromRgb(50,255,75)),
    brush_lamp_emergency(QColor::fromRgb(255,25,25)) {
    QPen blackPen(QColor::fromRgb(0,0,0));
    for (int f = 0; f < 5; ++f) {
        qreal y = 95+450/4.f * (4-f);
        scene->addLine(0, y, 200, y, blackPen);
        auto label = scene->addSimpleText(("Floor " + std::to_string(f)).c_str());
        label->setPos(10, y-30);
        lamps[f] = scene->addEllipse(62,y-26,10,10,blackPen,brush_lamp_off);
    }
    QBrush metalBrush(QColor::fromRgb(200,200,200));
    carriage = scene->addRect(100,0,40,50,blackPen,metalBrush);
    doors[0] = scene->addRect(100,5,20,40,blackPen,metalBrush);
    doors[1] = scene->addRect(120,5,20,40,blackPen,metalBrush);
    auto emergency_text = scene->addSimpleText("Emergency lamp");
    emergency_text->setPos(26, 6);
    emergency_lamp = scene->addEllipse(10, 10, 10, 10, blackPen, brush_lamp_off);
    setElevatorHeight(0);
    setDoorsClosed(false);
}

void MainWindow::MyScene::setElevatorHeight(float pos) {
    qreal y = 50 + pos * 450;
    // std::cerr << "y = " << y << "\n";
    carriage->setY(y);
    doors[0]->setY(y);
    doors[1]->setY(y);
}

void MainWindow::MyScene::setDoorsClosed(bool closed) {
    qreal offset = closed ? 0 : 18;
    doors[0]->setX(-offset);
    doors[1]->setX(+offset);
}

void MainWindow::MyScene::setLampState(lamp_state states) {
    for (int f = 0; f < 5; ++f) {
        bool state = states & (1 << f);
        lamps[f]->setBrush(state ? brush_lamp_on : brush_lamp_off);
    }
    bool emerg = states & LAMP_STATE_EMERGENCY;
    emergency_lamp->setBrush(emerg ? brush_lamp_emergency : brush_lamp_off);
}

void MainWindow::MyScene::setError(bool error) {
    if (error) {
        scene->setBackgroundBrush(QBrush(QColor::fromRgb(255,100,100)));
    }
}

void MainWindow::updateScene() {
    updateSimulation();
    myScene.setDoorsClosed(!sim.get_doors_open());
    myScene.setElevatorHeight(1 - sim.get_cart_position() / 4.f);
    myScene.setError(sim.has_error());
    ui->labelCartPosition->setText(("cart_position = " + std::to_string(sim.get_position_signal())).c_str());
    if (sim.has_error())
        ui->labelError->setText(("Error: " + sim.get_error_message()).c_str());
}

void MainWindow::updateSimulation() {
    sim.setErrorInjection(ui->buttonInjectError->isChecked());
    double t = sim_timer.nsecsElapsed() / 1000000000.0;
    double tick_length = sim.get_tick_length();
    long steps = (long)((t - ticks * tick_length)/tick_length);
    for (long i = 0; i < steps; ++i) {
        sim.tick();
    }
    ticks += steps;
    {
        std::lock_guard<std::mutex> guard(out->mutex);
        out->cart_position = sim.get_position_signal();
    }
}

void MainWindow::button_pressed(button_state button) {
    assert((button&(button-1)) == 0);
    std::lock_guard<std::mutex> guard(out->mutex);
    out->buttons |= button;
}

void MainWindow::button_released(button_state button) {
    assert((button&(button-1)) == 0);
    std::lock_guard<std::mutex> guard(out->mutex);
    out->buttons &= ~button;
}

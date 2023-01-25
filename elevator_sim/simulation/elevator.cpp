#include "mainwindow.h"
#include "elevator.h"
#include "elevator_output.h"

#include <QApplication>
#include <thread>
#include <future>
#include <iostream>

struct elevator {
    elevator(MainWindow &w, elevator_output *out) : w(w), out(out) {}
    MainWindow &w;
    elevator_output *out;
    /* Set asynchronously; should not be accessed from itself */
    std::thread main;
};

static void run(std::promise<elevator_h> &promise) {
    try {
        int argc = 0;
        char *argv[1] = {strdup("elevator_sim")};
        std::unique_ptr<elevator_output> output(new elevator_output());
        QApplication app(argc, argv);
        MainWindow w(output.get());
        elevator_h e = new elevator(w, output.get());
        w.show();
        promise.set_value(e);
        app.exec();
    } catch (...) {
        promise.set_exception(std::current_exception());
    }
}

int start_elevator(elevator_h *epp) {
    try {
        std::promise<elevator_h> promise;
        std::thread t(run, std::ref(promise));
        *epp = promise.get_future().get();
        (*epp)->main = std::move(t);
        return 0;
    }  catch (...) {
        *epp = nullptr;
        return 1;
    }
}

static void shutdown(elevator_h ep) {
    ep->main.join();
    delete ep;
    exit(0);
}

void set_motor_speed(elevator_h ep, float speed) {
    // std::cerr << "Setting motor speed to " << speed << std::endl;
    if (ep->out->simulation_stopped) shutdown(ep);
    QMetaObject::invokeMethod(&ep->w,
                              std::bind(&MainWindow::setMotorSpeed, &ep->w,
                                        speed));
}

void set_doors_open(elevator_h ep, _Bool open) {
    // std::cerr << "Setting door state to " << open << std::endl;
    if (ep->out->simulation_stopped) shutdown(ep);
    QMetaObject::invokeMethod(
                &ep->w, std::bind(&MainWindow::setDoorsOpen, &ep->w, open));
}

void stop_elevator(elevator_h ep) {
    // std::cerr << "Stopping elevator" << std::endl;
    if (!ep->out->simulation_stopped)
        QMetaObject::invokeMethod(&ep->w, &MainWindow::close);
    ep->main.join();
    delete ep;
}

/* Note: Does not promt simulation update; might provide stale data if UI thread gets blocked */
float get_cart_position(elevator_h ep) {
    if (ep->out->simulation_stopped) shutdown(ep);
    std::lock_guard<std::mutex> guard(ep->out->mutex);
    return ep->out->cart_position;
}

button_state get_button_state(elevator_h ep) {
    if (ep->out->simulation_stopped) shutdown(ep);
    std::lock_guard<std::mutex> guard(ep->out->mutex);
    return ep->out->buttons;
}

void set_lamp_state(elevator_h ep, lamp_state state) {
    if (ep->out->simulation_stopped) shutdown(ep);
    QMetaObject::invokeMethod(
                &ep->w, std::bind(&MainWindow::setLampState, &ep->w, state));
}

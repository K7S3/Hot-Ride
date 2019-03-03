#include "timer.h"
#include <GLFW/glfw3.h>
#define GLM_ENABLE_EXPERIMENTAL
Timer::Timer(double interval) {
    prev = 0;
    this->interval = interval;
}

bool Timer::processTick() {
    double cur = glfwGetTime();
    if (cur - prev >= interval) {
        prev = cur;
        return true;
    } else
        return false;
}

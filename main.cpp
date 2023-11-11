#include "Application.h"

int main() {
    if (!Application::setup()) {
        return 1;
    }
    Application application;
    if (!application.initialize()) {
        return 1;
    }
    application.run();
    Application::finalize();
    return 0;
}

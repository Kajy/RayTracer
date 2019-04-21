#pragma comment (lib, "SDL2.lib")
#pragma comment (lib, "SDL2main.lib")

#include <iostream>
#include <libfswatch/c++/monitor_factory.hpp>
#include <signal.h>
#include <unistd.h>
#include "RayTracer/RayTracer.hpp"

int main(int argc, char **argv) {
    if (argc != 2) {
        Debug::printError("Usage : ./RT {filename}.json");
        return 1;
    }
    std::string filename(argv[1]);
    RayTracer       app;

    app.setFilename(filename);
    app.setScene(RayTracer::parse(filename));
    app.run();
    return 0;
}
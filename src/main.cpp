#pragma comment (lib, "SDL2.lib")
#pragma comment (lib, "SDL2main.lib")

#include <iostream>
#include <signal.h>
#include <unistd.h>
#include <Common/Parser.hpp>
#include "RayTracer/RayTracer.hpp"

int main(int argc, char **argv) {
    if (argc != 3) {
        Debug::printError("Usage : ./RT {config}.json {filename}.json");
        return 1;
    }

    std::string     config(argv[1]);
    std::string     scene(argv[2]);
    RayTracer       app(Parser::ParseConfiguration(config));

    app.setFilename(scene);
    app.setScene(app.parse(scene));
    app.run();

    return 0;
}
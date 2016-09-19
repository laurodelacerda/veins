#include <algorithm>

#include "veins/modules/waveApplication/gps/SimpleGPS.h"

SimpleGPS::SimpleGPS(TraCICommandInterface::Vehicle* vehicle) {
    traciVehicle = vehicle;
}

/*
 * Returns a string with the course (the current lane + a defined number of planned roads) of the vehicle.
 * int maxNumberofRoutes = 3
 * string format: (l1)[r1][[r2][r3]
 * l1 = current lane
 * r1, r2, r3 = route (collection 3 of roads)
 */
std::string SimpleGPS::getCourse(int maxNumberOfRoads) {

    //TODO Verificar o que ocorre quando a Rota Planejada é alterada em tempo de execução
    std::list<std::string> route = traciVehicle->getPlannedRoadIds();
    std::string roadInTransit = formatRoad(traciVehicle->getRoadId());
    std::string formattedCourse = "";

    int addedRoads = 0;
    bool addInMessage = false;

    //TODO pessima logica, melhorar
    for (std::list<std::string>::iterator roadId = route.begin(); roadId != route.end(); ++roadId) {
        std::string road = formatRoad(*roadId);
        if (road == roadInTransit)
            addInMessage = true;

        if (addInMessage) {
            if (addedRoads < maxNumberOfRoads) {
                formattedCourse = formattedCourse + road;
                addedRoads++;
            } else {
                break;
            }
        }
    }

    formattedCourse = formatLane(traciVehicle->getLaneIndex())
            + formattedCourse;

    return formattedCourse;
}

bool SimpleGPS::onRoute(std::string course) {

    std::string roadInTransit = formatRoad(traciVehicle->getRoadId());
    std::string laneInTransit = formatLane(traciVehicle->getLaneIndex());

    if (course.find(roadInTransit) != std::string::npos)
        if (course.find(laneInTransit) != std::string::npos)
            return true; //on route

    return false; //not on route
}

std::string SimpleGPS::formatRoad(std::string road) {
    return "[" + road + "]";
}

std::string SimpleGPS::formatLane(int lane) {
    return "(" + std::to_string(lane) + ")";
}

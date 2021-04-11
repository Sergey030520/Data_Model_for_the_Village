#include <iostream>
#include <vector>

enum type_construct{
    house, garage, bathhouse, barn
};
enum type_room{
    bedroom, kitchen, bathroom, children, living
};
struct Room{
    type_room name_room;
    float area = 0.0f;
};
struct Storey{
    float height = 0.0f;
    std::vector<Room> rooms;
};
struct Construction{
    type_construct name_construct;
    float area = 0.0f;
    bool fireplace = false;
    std::vector<Storey> storeys;
};
struct Plot{
    int unique_number = rand()%100;
    float area = 0.0f;
    std::vector<Construction> constructions;
};
struct Village{
    std::vector<Plot> plots;
};

void show_occupied_area(const Village& village){
    float area = 0.f;
    for (int counter_plot = 0; counter_plot < village.plots.size(); ++counter_plot){
        area += village.plots[counter_plot].area;
    }
    std::cout << "The village occupies an area of " << area << "m^2!" << std::endl;
}
std::string determine_type_room(const type_room& typeRoom){
    switch (int(typeRoom)) {
        case bedroom:
            return "bedroom";
        case kitchen:
            return "kitchen";
        case bathroom:
            return "bathroom";
        case children:
            return "children";
        case living:
            return "living";
    }
    return "unknown";
}
std::string determine_type_construct(const type_construct& typeConstruct){
    switch (int(typeConstruct)) {
        case house:
            return "house";
        case garage:
            return "garage";
        case bathhouse:
            return "bathhouse";
        case barn:
            return "barn";
    }
    return "unknown";
}
void showVillage(const Village& village){
    std::cout << "Village:\n";
    for (int numb_plot = 0; numb_plot < village.plots.size(); ++numb_plot) {
        std::cout << "\tPlot" << numb_plot + 1 << ":\n";
        for (int numb_construct = 0; numb_construct < village.plots[numb_plot].constructions.size(); ++numb_construct) {
            std::string name_construct = determine_type_construct(village.plots[numb_plot].constructions[numb_construct].name_construct);
            std::cout << "\t\tName construct: " << name_construct << std::endl;
            std::cout << "\t\tArea: " << village.plots[numb_plot].constructions[numb_construct].area << std::endl;
            if(name_construct == "house" || name_construct == "bathhouse"){
                std::cout << "\t\tFireplace: " << (village.plots[numb_plot].constructions[numb_construct].fireplace ? "Yes" : "No")
                    << std::endl;
            }
            for (int numb_storey = 0; numb_storey < village.plots[numb_plot].constructions[numb_construct].storeys.size(); ++numb_storey) {
                std::cout << "\t\t\tStorey: " << numb_storey + 1 << std::endl;
                std::cout << "\t\t\tHeight: " << village.plots[numb_plot].constructions[numb_construct].storeys[numb_storey].height
                    << std::endl;
                for (int numb_room = 0; numb_room < village.plots[numb_plot].constructions[numb_construct].storeys[numb_storey].rooms.size(); ++numb_room) {
                    std::cout << "\t\t\t\tName: " <<
                        determine_type_room(village.plots[numb_plot].constructions[numb_construct].storeys[numb_storey].rooms[numb_room].name_room) << std::endl;
                    std::cout << "\t\t\t\tArea:" <<
                        village.plots[numb_plot].constructions[numb_construct].storeys[numb_storey].rooms[numb_room].area << std::endl;
                }
            }
        }
    }
}
int main() {
    Village village;
    int countPlot = 0;
    std::cout << "Input the count of plot: ";
    std::cin >> countPlot;
    for (int numb_plot  = 0; numb_plot < countPlot; ++numb_plot) {
        Plot plot;
        int countConstruct = 0;
        std::cout << "Input the plot area: ";
        std::cin >> plot.area;
        std::cout << "Input the count of constructions: ";
        std::cin >> countConstruct;
        for (int numb_construct = 0; numb_construct < countConstruct; ++numb_construct){
            Construction construct;
            int typeConstruct, count_storey; std::string answer;
            std::cout << "Input the name of the construction:\n\thouse - 0,\n\tgarage - 1,\n\tbathhouse - 2,\n\tbarn - 3:\n";
            std::cin >> typeConstruct;
            construct.name_construct = (type_construct)typeConstruct;
            std::cout << "Input the plot area: ";
            std::cin >> construct.area;
            if (typeConstruct == house || typeConstruct == bathhouse){
                std::cout << "Is there a fireplace in the construction(Yes/No):";
                std::cin >> answer;
                construct.fireplace = answer == "Yes";
            }else construct.fireplace = false;
            if (construct.name_construct == house){
                while (true){
                    std::cout << "Input the count of storey: ";
                    std::cin >> count_storey;
                    if (count_storey < 1 || count_storey > 3){
                        std::cout << "Error: there may be 1 - 3 storey in the house!\n";
                        continue;
                    }
                    break;
                }
            }
            else{
                std::cout << "Input the count of storey: ";
                std::cin >> count_storey;
            }
            for (int numb_storey = 0; numb_storey <  count_storey; ++numb_storey) {
                Storey storey; int count_room = 0;
                std::cout << "Input the height of the storey: ";
                std::cin >> storey.height;
                if(construct.name_construct == house){
                    while(true){
                        std::cout << "Input the count of room: ";
                        std::cin >> count_room;
                        if (count_room < 2 || count_room > 4){
                            std::cout << "Error: there may be 2 - 4 room in the house!\n";
                            continue;
                        }
                        break;
                    }
                }
                else{
                    std::cout << "Input the count of room: ";
                    std::cin >> count_room;
                }
                for (int numb_room = 0; numb_room < count_room; ++numb_room) {
                    Room room; int typeRoom;
                    std::cout << "Input the name of the room:\n\tbedroom - 0,\n\tkitchen - 1,\n\tbathroom - 2,\n\tchildren - 3,\n\tliving - 4):\n";
                    std::cin >> typeRoom;
                    std::cout << "Input the plot area: ";
                    std::cin >> room.area;
                    room.name_room = (type_room)typeRoom;
                    storey.rooms.push_back(room);
                }
                construct.storeys.push_back(storey);
            }
            plot.constructions.push_back(construct);
        }
        village.plots.push_back(plot);
    }
    showVillage(village);
    show_occupied_area(village);
}
#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "mountain";

void create_mirkwood_central_forest_mountain_room() {

    add_mirkwood_exits(([
        "southeast" : "r03/m35",
        "southwest" : "r03/f33",
        "south" : "r03/f34",
        "northwest" : "r05/m33",
        "east" : "r04/m35",
        "north" : "r05/m34",
        "northeast" : "r05/m35",
        "west" : "r04/m33",
    ]));
    
}

#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "mountain";

void create_mirkwood_central_forest_mountain_room() {

    add_mirkwood_exits(([
        "southeast" : "r02/f36",
        "southwest" : "r02/f34",
        "south" : "r02/f35",
        "northwest" : "r04/m34",
        "east" : "r03/m36",
        "north" : "r04/m35",
        "northeast" : "r04/m36",
        "west" : "r03/f34",
    ]));
    
}

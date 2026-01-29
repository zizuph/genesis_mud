#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "mountain";

void create_mirkwood_central_forest_mountain_room() {

    add_mirkwood_exits(([
        "southeast" : "r03/m36",
        "southwest" : "r03/f34",
        "south" : "r03/m35",
        "northwest" : "r05/m34",
        "east" : "r04/m36",
        "north" : "r05/m35",
        "northeast" : "r05/m36",
        "west" : "r04/m34",
    ]));
    
}

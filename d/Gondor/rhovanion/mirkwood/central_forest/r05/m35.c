#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "mountain";

void create_mirkwood_central_forest_mountain_room() {

    add_mirkwood_exits(([
        "southeast" : "r04/m36",
        "southwest" : "r04/m34",
        "south" : "r04/m35",
        "northwest" : "r06/m34",
        "east" : "r05/m36",
        "north" : "r06/m35",
        "northeast" : "r06/m36",
        "west" : "r05/m34",
    ]));
    
}

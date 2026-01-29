#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "mountain";

void create_mirkwood_central_forest_mountain_room() {

    add_mirkwood_exits(([
        "southeast" : "r05/m36",
        "southwest" : "r05/m34",
        "south" : "r05/m35",
        "northwest" : "r07/f34",
        "east" : "r06/m36",
        "north" : "r07/f35",
        "northeast" : "r07/m36",
        "west" : "r06/m34",
    ]));
    
}

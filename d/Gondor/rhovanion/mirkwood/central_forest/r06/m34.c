#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "mountain";

void create_mirkwood_central_forest_mountain_room() {

    add_mirkwood_exits(([
        "southeast" : "r05/m35",
        "southwest" : "r05/m33",
        "south" : "r05/m34",
        "northwest" : "r07/f33",
        "east" : "r06/m35",
        "north" : "r07/f34",
        "northeast" : "r07/f35",
        "west" : "r06/m33",
    ]));
    
}

#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "mountain";

void create_mirkwood_central_forest_mountain_room() {

    add_mirkwood_exits(([
        "southeast" : "r05/f42",
        "southwest" : "r05/m40",
        "south" : "r05/f41",
        "northwest" : "r07/f40",
        "east" : "r06/f42",
        "north" : "r07/f41",
        "northeast" : "r07/f42",
        "west" : "r06/m40",
    ]));
    
}

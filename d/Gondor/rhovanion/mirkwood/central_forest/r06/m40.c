#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "mountain";

void create_mirkwood_central_forest_mountain_room() {

    add_mirkwood_exits(([
        "southeast" : "r05/f41",
        "southwest" : "r05/m39",
        "south" : "r05/m40",
        "northwest" : "r07/m39",
        "east" : "r06/m41",
        "north" : "r07/f40",
        "northeast" : "r07/f41",
        "west" : "r06/m39",
    ]));
    
}

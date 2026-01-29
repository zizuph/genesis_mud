#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "mountain";

void create_mirkwood_central_forest_mountain_room() {

    add_mirkwood_exits(([
        "southeast" : "r04/f41",
        "southwest" : "r04/f39",
        "south" : "r04/f40",
        "northwest" : "r06/m39",
        "east" : "r05/f41",
        "north" : "r06/m40",
        "northeast" : "r06/m41",
        "west" : "r05/m39",
    ]));
    
}

#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "mountain";

void create_mirkwood_central_forest_mountain_room() {

    add_mirkwood_exits(([
        "southeast" : "r04/f40",
        "southwest" : "r04/m38",
        "south" : "r04/f39",
        "northwest" : "r06/m38",
        "east" : "r05/m40",
        "north" : "r06/m39",
        "northeast" : "r06/m40",
        "west" : "r05/m38",
    ]));
    
}

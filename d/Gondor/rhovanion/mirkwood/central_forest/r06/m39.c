#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "mountain";

void create_mirkwood_central_forest_mountain_room() {

    add_mirkwood_exits(([
        "southeast" : "r05/m40",
        "southwest" : "r05/m38",
        "south" : "r05/m39",
        "northwest" : "r07/m38",
        "east" : "r06/m40",
        "north" : "r07/m39",
        "northeast" : "r07/f40",
        "west" : "r06/m38",
    ]));
    
}

#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "mountain";

void create_mirkwood_central_forest_mountain_room() {

    add_mirkwood_exits(([
        "southeast" : "r04/f39",
        "southwest" : "r04/m37",
        "south" : "r04/m38",
        "northwest" : "r06/m37",
        "east" : "r05/m39",
        "north" : "r06/m38",
        "northeast" : "r06/m39",
        "west" : "r05/m37",
    ]));
    
}

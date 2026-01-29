#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "mountain";

void create_mirkwood_central_forest_mountain_room() {

    add_mirkwood_exits(([
        "southeast" : "r04/f23",
        "southwest" : "r04/f21",
        "south" : "r04/f22",
        "northwest" : "r06/f21",
        "east" : "r05/m23",
        "north" : "r06/f22",
        "northeast" : "r06/f23",
        "west" : "r05/f21",
    ]));
    
}

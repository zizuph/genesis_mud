#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "mountain";

void create_mirkwood_central_forest_mountain_room() {

    add_mirkwood_exits(([
        "southeast" : "r04/f24",
        "southwest" : "r04/f22",
        "south" : "r04/f23",
        "northwest" : "r06/f22",
        "east" : "r05/m24",
        "north" : "r06/f23",
        "northeast" : "r06/f24",
        "west" : "r05/m22",
    ]));
    
}

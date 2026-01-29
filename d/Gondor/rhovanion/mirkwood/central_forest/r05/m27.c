#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "mountain";

void create_mirkwood_central_forest_mountain_room() {

    add_mirkwood_exits(([
        "southeast" : "r04/f28",
        "southwest" : "r04/f26",
        "south" : "r04/f27",
        "northwest" : "r06/m26",
        "east" : "r05/m28",
        "north" : "r06/m27",
        "northeast" : "r06/m28",
        "west" : "r05/m26",
    ]));
    
}

#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "mountain";

void create_mirkwood_central_forest_mountain_room() {

    add_mirkwood_exits(([
        "southeast" : "r04/f27",
        "southwest" : "r04/f25",
        "south" : "r04/f26",
        "northwest" : "r06/m25",
        "east" : "r05/m27",
        "north" : "r06/m26",
        "northeast" : "r06/m27",
        "west" : "r05/m25",
    ]));
    
}

#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "mountain";

void create_mirkwood_central_forest_mountain_room() {

    add_mirkwood_exits(([
        "southeast" : "r04/f29",
        "southwest" : "r04/f27",
        "south" : "r04/f28",
        "northwest" : "r06/m27",
        "east" : "r05/m29",
        "north" : "r06/m28",
        "northeast" : "r06/m29",
        "west" : "r05/m27",
    ]));
    
}

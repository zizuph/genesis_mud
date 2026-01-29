#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "mountain";

void create_mirkwood_central_forest_mountain_room() {

    add_mirkwood_exits(([
        "southeast" : "r04/f30",
        "southwest" : "r04/f28",
        "south" : "r04/f29",
        "northwest" : "r06/m28",
        "east" : "r05/m30",
        "north" : "r06/m29",
        "northeast" : "r06/m30",
        "west" : "r05/m28",
    ]));
    
}

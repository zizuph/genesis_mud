#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "mountain";

void create_mirkwood_central_forest_mountain_room() {

    add_mirkwood_exits(([
        "southeast" : "r05/m28",
        "southwest" : "r05/m26",
        "south" : "r05/m27",
        "northwest" : "r07/m26",
        "east" : "r06/m28",
        "north" : "r07/m27",
        "northeast" : "r07/f28",
        "west" : "r06/m26",
    ]));
    
}

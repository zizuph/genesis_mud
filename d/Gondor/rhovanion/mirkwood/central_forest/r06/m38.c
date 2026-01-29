#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "mountain";

void create_mirkwood_central_forest_mountain_room() {

    add_mirkwood_exits(([
        "southeast" : "r05/m39",
        "southwest" : "r05/m37",
        "south" : "r05/m38",
        "northwest" : "r07/m37",
        "east" : "r06/m39",
        "north" : "r07/m38",
        "northeast" : "r07/m39",
        "west" : "r06/m37",
    ]));
    
}

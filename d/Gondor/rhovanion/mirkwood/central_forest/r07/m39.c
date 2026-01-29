#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "mountain";

void create_mirkwood_central_forest_mountain_room() {

    add_mirkwood_exits(([
        "southeast" : "r06/m40",
        "southwest" : "r06/m38",
        "south" : "r06/m39",
        "northwest" : "r08/m38",
        "east" : "r07/f40",
        "north" : "r08/f39",
        "northeast" : "r08/f40",
        "west" : "r07/m38",
    ]));
    
}

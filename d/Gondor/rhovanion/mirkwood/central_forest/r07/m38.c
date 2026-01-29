#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "mountain";

void create_mirkwood_central_forest_mountain_room() {

    add_mirkwood_exits(([
        "southeast" : "r06/m39",
        "southwest" : "r06/m37",
        "south" : "r06/m38",
        "northwest" : "r08/m37",
        "east" : "r07/m39",
        "north" : "r08/m38",
        "northeast" : "r08/f39",
        "west" : "r07/m37",
    ]));
    
}

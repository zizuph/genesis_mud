#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "mountain";

void create_mirkwood_central_forest_mountain_room() {

    add_mirkwood_exits(([
        "southeast" : "r06/m38",
        "southwest" : "r06/m36",
        "south" : "r06/m37",
        "northwest" : "r08/m36",
        "east" : "r07/m38",
        "north" : "r08/m37",
        "northeast" : "r08/m38",
        "west" : "r07/m36",
    ]));
    
}

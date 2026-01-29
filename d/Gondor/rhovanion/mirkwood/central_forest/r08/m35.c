#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "mountain";

void create_mirkwood_central_forest_mountain_room() {

    add_mirkwood_exits(([
        "southeast" : "r07/m36",
        "southwest" : "r07/f34",
        "south" : "r07/f35",
        "northwest" : "r09/f34",
        "east" : "r08/m36",
        "north" : "r09/f35",
        "northeast" : "r09/f36",
        "west" : "r08/f34",
    ]));
    
}

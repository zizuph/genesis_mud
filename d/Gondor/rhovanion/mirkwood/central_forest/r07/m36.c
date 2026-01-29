#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "mountain";

void create_mirkwood_central_forest_mountain_room() {

    add_mirkwood_exits(([
        "southeast" : "r06/m37",
        "southwest" : "r06/m35",
        "south" : "r06/m36",
        "northwest" : "r08/m35",
        "east" : "r07/m37",
        "north" : "r08/m36",
        "northeast" : "r08/m37",
        "west" : "r07/f35",
    ]));
    
}

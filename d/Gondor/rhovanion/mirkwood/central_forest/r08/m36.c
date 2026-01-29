#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "mountain";

void create_mirkwood_central_forest_mountain_room() {

    add_mirkwood_exits(([
        "southeast" : "r07/m37",
        "southwest" : "r07/f35",
        "south" : "r07/m36",
        "northwest" : "r09/f35",
        "east" : "r08/m37",
        "north" : "r09/f36",
        "northeast" : "r09/f37",
        "west" : "r08/m35",
    ]));
    
}

#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "mountain";

void create_mirkwood_central_forest_mountain_room() {

    add_mirkwood_exits(([
        "southeast" : "r07/m38",
        "southwest" : "r07/m36",
        "south" : "r07/m37",
        "northwest" : "r09/f36",
        "east" : "r08/m38",
        "north" : "r09/f37",
        "northeast" : "r09/f38",
        "west" : "r08/m36",
    ]));
    
}

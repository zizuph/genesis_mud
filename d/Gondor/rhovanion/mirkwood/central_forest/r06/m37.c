#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "mountain";

void create_mirkwood_central_forest_mountain_room() {

    add_mirkwood_exits(([
        "southeast" : "r05/m38",
        "southwest" : "r05/m36",
        "south" : "r05/m37",
        "northwest" : "r07/m36",
        "east" : "r06/m38",
        "north" : "r07/m37",
        "northeast" : "r07/m38",
        "west" : "r06/m36",
    ]));
    
}

#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "mountain";

void create_mirkwood_central_forest_mountain_room() {

    add_mirkwood_exits(([
        "southeast" : "r05/m37",
        "southwest" : "r05/m35",
        "south" : "r05/m36",
        "northwest" : "r07/f35",
        "east" : "r06/m37",
        "north" : "r07/m36",
        "northeast" : "r07/m37",
        "west" : "r06/m35",
    ]));
    
}

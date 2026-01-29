#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "mountain";

void create_mirkwood_central_forest_mountain_room() {

    add_mirkwood_exits(([
        "southeast" : "r04/m37",
        "southwest" : "r04/m35",
        "south" : "r04/m36",
        "northwest" : "r06/m35",
        "east" : "r05/m37",
        "north" : "r06/m36",
        "northeast" : "r06/m37",
        "west" : "r05/m35",
    ]));
    
}

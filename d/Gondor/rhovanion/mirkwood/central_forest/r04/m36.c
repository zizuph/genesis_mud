#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "mountain";

void create_mirkwood_central_forest_mountain_room() {

    add_mirkwood_exits(([
        "southeast" : "r03/f37",
        "southwest" : "r03/m35",
        "south" : "r03/m36",
        "northwest" : "r05/m35",
        "east" : "r04/m37",
        "north" : "r05/m36",
        "northeast" : "r05/m37",
        "west" : "r04/m35",
    ]));
    
}

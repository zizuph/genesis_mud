#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "mountain";

void create_mirkwood_central_forest_mountain_room() {

    add_mirkwood_exits(([
        "southeast" : "r03/f38",
        "southwest" : "r03/m36",
        "south" : "r03/f37",
        "northwest" : "r05/m36",
        "east" : "r04/m38",
        "north" : "r05/m37",
        "northeast" : "r05/m38",
        "west" : "r04/m36",
    ]));
    
}

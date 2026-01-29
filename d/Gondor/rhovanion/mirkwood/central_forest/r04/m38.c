#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "mountain";

void create_mirkwood_central_forest_mountain_room() {

    add_mirkwood_exits(([
        "southeast" : "r03/f39",
        "southwest" : "r03/f37",
        "south" : "r03/f38",
        "northwest" : "r05/m37",
        "east" : "r04/f39",
        "north" : "r05/m38",
        "northeast" : "r05/m39",
        "west" : "r04/m37",
    ]));
    
}

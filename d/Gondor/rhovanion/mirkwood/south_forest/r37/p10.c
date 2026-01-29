#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "path";

void create_mirkwood_south_forest_path_room() {

    add_mirkwood_exits(([]
        "southeast" : "r38/f11",
        "southwest" : "r38/p09",
        "south" : "r38/f10",
        "northwest" : "r36/f09",
        "east" : "r37/p11",
        "north" : "r36/f10",
        "northeast" : "r36/f11",
        "west" : "r37/f09",
    ]));
    
}

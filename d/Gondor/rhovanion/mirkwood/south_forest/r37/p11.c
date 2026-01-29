#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "path";

void create_mirkwood_south_forest_path_room() {

    add_mirkwood_exits(([]
        "southeast" : "r38/f12",
        "southwest" : "r38/f10",
        "south" : "r38/f11",
        "northwest" : "r36/f10",
        "east" : "r37/f12",
        "north" : "r36/f11",
        "west" : "r37/p10",
    ]));
    
}

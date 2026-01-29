#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "path";

void create_mirkwood_south_forest_path_room() {

    add_mirkwood_exits(([]
        "southeast" : "r39/f10",
        "northwest" : "r37/f08",
        "east" : "r38/f10",
        "north" : "r37/f09",
        "northeast" : "r37/p10",
        "west" : "r38/f08",
    ]));
    
}

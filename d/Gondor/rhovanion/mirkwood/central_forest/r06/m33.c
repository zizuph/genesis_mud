#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "mountain";

void create_mirkwood_central_forest_mountain_room() {

    add_mirkwood_exits(([
        "southeast" : "r05/m34",
        "southwest" : "r05/m32",
        "south" : "r05/m33",
        "northwest" : "r07/f32",
        "east" : "r06/m34",
        "north" : "r07/f33",
        "northeast" : "r07/f34",
        "west" : "r06/m32",
    ]));
    
}

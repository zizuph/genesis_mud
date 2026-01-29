#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "mountain";

void create_mirkwood_central_forest_mountain_room() {

    add_mirkwood_exits(([
        "southeast" : "r03/f34",
        "southwest" : "r03/f32",
        "south" : "r03/f33",
        "northwest" : "r05/m32",
        "east" : "r04/m34",
        "north" : "r05/m33",
        "northeast" : "r05/m34",
        "west" : "r04/f32",
    ]));
    
}

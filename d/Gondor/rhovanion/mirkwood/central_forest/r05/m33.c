#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "mountain";

void create_mirkwood_central_forest_mountain_room() {

    add_mirkwood_exits(([
        "southeast" : "r04/m34",
        "southwest" : "r04/f32",
        "south" : "r04/m33",
        "northwest" : "r06/m32",
        "east" : "r05/m34",
        "north" : "r06/m33",
        "northeast" : "r06/m34",
        "west" : "r05/m32",
    ]));
    
}

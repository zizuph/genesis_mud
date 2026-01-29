#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "mountain";

void create_mirkwood_central_forest_mountain_room() {

    add_mirkwood_exits(([
        "southeast" : "r04/m33",
        "southwest" : "r04/f31",
        "south" : "r04/f32",
        "northwest" : "r06/m31",
        "east" : "r05/m33",
        "north" : "r06/m32",
        "northeast" : "r06/m33",
        "west" : "r05/m31",
    ]));
    
}

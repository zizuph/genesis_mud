#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "mountain";

void create_mirkwood_central_forest_mountain_room() {

    add_mirkwood_exits(([
        "southeast" : "r05/m33",
        "southwest" : "r05/m31",
        "south" : "r05/m32",
        "northwest" : "r07/f31",
        "east" : "r06/m33",
        "north" : "r07/f32",
        "northeast" : "r07/f33",
        "west" : "r06/m31",
    ]));
    
}

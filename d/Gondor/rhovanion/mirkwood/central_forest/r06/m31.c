#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "mountain";

void create_mirkwood_central_forest_mountain_room() {

    add_mirkwood_exits(([
        "southeast" : "r05/m32",
        "southwest" : "r05/m30",
        "south" : "r05/m31",
        "northwest" : "r07/f30",
        "east" : "r06/m32",
        "north" : "r07/f31",
        "northeast" : "r07/f32",
        "west" : "r06/m30",
    ]));
    
}

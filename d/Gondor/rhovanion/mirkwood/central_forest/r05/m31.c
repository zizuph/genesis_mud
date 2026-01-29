#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "mountain";

void create_mirkwood_central_forest_mountain_room() {

    add_mirkwood_exits(([
        "southeast" : "r04/f32",
        "southwest" : "r04/f30",
        "south" : "r04/f31",
        "northwest" : "r06/m30",
        "east" : "r05/m32",
        "north" : "r06/m31",
        "northeast" : "r06/m32",
        "west" : "r05/m30",
    ]));
    
}

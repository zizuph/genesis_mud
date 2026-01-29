#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "mountain";

void create_mirkwood_central_forest_mountain_room() {

    add_mirkwood_exits(([
        "southeast" : "r04/f31",
        "southwest" : "r04/f29",
        "south" : "r04/f30",
        "northwest" : "r06/m29",
        "east" : "r05/m31",
        "north" : "r06/m30",
        "northeast" : "r06/m31",
        "west" : "r05/m29",
    ]));
    
}

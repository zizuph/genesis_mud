#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "mountain";

void create_mirkwood_central_forest_mountain_room() {

    add_mirkwood_exits(([
        "southeast" : "r05/m31",
        "southwest" : "r05/m29",
        "south" : "r05/m30",
        "northwest" : "r07/f29",
        "east" : "r06/m31",
        "north" : "r07/f30",
        "northeast" : "r07/f31",
        "west" : "r06/m29",
    ]));
    
}

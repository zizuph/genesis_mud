#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "mountain";

void create_mirkwood_central_forest_mountain_room() {

    add_mirkwood_exits(([
        "southeast" : "r05/m26",
        "southwest" : "r05/m24",
        "south" : "r05/m25",
        "northwest" : "r07/f24",
        "east" : "r06/m26",
        "north" : "r07/f25",
        "northeast" : "r07/m26",
        "west" : "r06/f24",
    ]));
    
}

#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "mountain";

void create_mirkwood_central_forest_mountain_room() {

    add_mirkwood_exits(([
        "southeast" : "r05/m29",
        "southwest" : "r05/m27",
        "south" : "r05/m28",
        "northwest" : "r07/m27",
        "east" : "r06/m29",
        "north" : "r07/f28",
        "northeast" : "r07/f29",
        "west" : "r06/m27",
    ]));
    
}

#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "mountain";

void create_mirkwood_central_forest_mountain_room() {

    add_mirkwood_exits(([
        "southeast" : "r05/m30",
        "southwest" : "r05/m28",
        "south" : "r05/m29",
        "northwest" : "r07/f28",
        "east" : "r06/m30",
        "north" : "r07/f29",
        "northeast" : "r07/f30",
        "west" : "r06/m28",
    ]));
    
}

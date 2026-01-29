#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "mountain";

void create_mirkwood_central_forest_mountain_room() {

    add_mirkwood_exits(([
        "southeast" : "r05/m27",
        "southwest" : "r05/m25",
        "south" : "r05/m26",
        "northwest" : "r07/f25",
        "east" : "r06/m27",
        "north" : "r07/m26",
        "northeast" : "r07/m27",
        "west" : "r06/m25",
    ]));
    
}

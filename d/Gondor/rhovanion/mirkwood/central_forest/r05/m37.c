#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "mountain";

void create_mirkwood_central_forest_mountain_room() {

    add_mirkwood_exits(([
        "southeast" : "r04/m38",
        "southwest" : "r04/m36",
        "south" : "r04/m37",
        "northwest" : "r06/m36",
        "east" : "r05/m38",
        "north" : "r06/m37",
        "northeast" : "r06/m38",
        "west" : "r05/m36",
    ]));


    add_exit(MIRKWOOD_CENTRAL_FOREST_DIR + "caves/cave13", "enter");
    
}

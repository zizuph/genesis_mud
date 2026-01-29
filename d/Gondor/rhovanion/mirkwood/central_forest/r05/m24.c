#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "mountain";

void create_mirkwood_central_forest_mountain_room() {

    add_mirkwood_exits(([
        "southeast" : "r04/f25",
        "southwest" : "r04/f23",
        "south" : "r04/f24",
        "northwest" : "r06/f23",
        "east" : "r05/m25",
        "north" : "r06/f24",
        "northeast" : "r06/m25",
        "west" : "r05/m23",
    ]));
    
}

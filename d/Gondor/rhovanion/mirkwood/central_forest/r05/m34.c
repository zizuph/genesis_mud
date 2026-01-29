#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "mountain";

void create_mirkwood_central_forest_mountain_room() {

    add_mirkwood_exits(([
        "southeast" : "r04/m35",
        "southwest" : "r04/m33",
        "south" : "r04/m34",
        "northwest" : "r06/m33",
        "east" : "r05/m35",
        "north" : "r06/m34",
        "northeast" : "r06/m35",
        "west" : "r05/m33",
    ]));
    
}

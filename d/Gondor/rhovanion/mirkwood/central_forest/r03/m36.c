#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "mountain";

void create_mirkwood_central_forest_mountain_room() {

    add_mirkwood_exits(([
        "southeast" : "r02/f37",
        "southwest" : "r02/f35",
        "south" : "r02/f36",
        "northwest" : "r04/m35",
        "east" : "r03/f37",
        "north" : "r04/m36",
        "northeast" : "r04/m37",
        "west" : "r03/m35",
    ]));
    
}

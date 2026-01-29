#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "mountain";

void create_mirkwood_central_forest_mountain_room() {

    add_mirkwood_exits(([
        "southeast" : "r07/m39",
        "southwest" : "r07/m37",
        "south" : "r07/m38",
        "northwest" : "r09/f37",
        "east" : "r08/f39",
        "north" : "r09/f38",
        "northeast" : "r09/f39",
        "west" : "r08/m37",
    ]));
    
}

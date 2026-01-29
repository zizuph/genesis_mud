#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest_edge";

void create_mirkwood_south_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(50);
    add_mirkwood_exits(([
        "northwest" : MIRKWOOD_OLDROAD_DIR + "r07",
        "north" : MIRKWOOD_OLDROAD_DIR + "r08",
        "northeast" : MIRKWOOD_OLDROAD_DIR + "r09",

        "southeast" : "r01/f14",
        "southwest" : "r01/f12",
        "south" : "r01/f13",
        "east" : "r00/f14",
        "west" : "r00/f12",
    ]));
    
}

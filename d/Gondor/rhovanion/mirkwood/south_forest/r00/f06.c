#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest_edge";

void create_mirkwood_south_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(30);
    add_mirkwood_exits(([
        "north" : MIRKWOOD_OLDROAD_DIR + "r01",
        "northeast" : MIRKWOOD_OLDROAD_DIR + "r02",

        "southeast" : "r01/f07",
        "south" : "r01/f06",
        "east" : "r00/f07",
    ]));
    
}

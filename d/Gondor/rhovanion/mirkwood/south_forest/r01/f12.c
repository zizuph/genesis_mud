#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest_edge";

void create_mirkwood_south_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(50);
    add_mirkwood_exits(([
        "southeast" : "r02/f13",
        "southwest" : "r02/f11",
        "south" : "r02/f12",
        "northwest" : "r00/f11",
        "east" : "r01/f13",
        "north" : "r00/f12",
        "northeast" : "r00/f13",
        "west" : "r01/f11",
    ]));
    
}

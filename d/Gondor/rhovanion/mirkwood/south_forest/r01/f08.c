#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest_edge";

void create_mirkwood_south_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(30);
    add_mirkwood_exits(([
        "southeast" : "r02/f09",
        "southwest" : "r02/f07",
        "south" : "r02/p08-r02",
        "northwest" : "r00/f07",
        "east" : "r01/p09-r01",
        "north" : "r00/f08",
        "northeast" : "r00/p09-r00",
        "west" : "r01/f07",
    ]));
    
}

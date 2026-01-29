#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest_edge";

void create_mirkwood_south_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(50);
    add_mirkwood_exits(([
        "southeast" : "r02/f12",
        "southwest" : "r02/f10",
        "south" : "r02/f11",
        "northwest" : "r00/f10",
        "east" : "r01/f12",
        "north" : "r00/f11",
        "northeast" : "r00/f12",
        "west" : "r01/f10",
    ]));
    
}

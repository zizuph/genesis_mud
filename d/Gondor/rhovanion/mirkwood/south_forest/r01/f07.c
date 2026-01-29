#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest_edge";

void create_mirkwood_south_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(30);
    add_mirkwood_exits(([
        "southeast" : "r02/p08-r02",
        "southwest" : "r02/f06",
        "south" : "r02/f07",
        "northwest" : "r00/f06",
        "east" : "r01/f08",
        "north" : "r00/f07",
        "northeast" : "r00/f08",
        "west" : "r01/f06",
    ]));
    
}

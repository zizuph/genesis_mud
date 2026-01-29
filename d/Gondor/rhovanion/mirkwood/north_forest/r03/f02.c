#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest_edge";

void create_mirkwood_north_forest_edge_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_movement_difficulty(50);
    add_mirkwood_exits(([
        "southeast" : "r02/f03",
        "southwest" : "r02/f01",
        "south" : "r02/f02",
        "northwest" : "r04/f01",
        "east" : "r03/f03",
        "north" : "r04/f02",
        "northeast" : "r04/f03",
        "west" : "r03/f01",
    ]));
    
}

#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(11);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r01/f14",
        "southwest" : "r01/f12",
        "south" : "r01/f13",
        "northwest" : "r03/f12",
        "east" : "r02/f14",
        "north" : "r03/f13",
        "northeast" : "r03/f14",
        "west" : "r02/f12",
    ]));
    
}

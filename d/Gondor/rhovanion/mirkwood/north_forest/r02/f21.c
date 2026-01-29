#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(58);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r02/f22",
        "southwest" : "r01/f20",
        "south" : "r01/f21",
        "northwest" : "r03/f20",
        "east" : "r02/f22",
        "north" : "r03/f21",
        "northeast" : "r03/f22",
        "west" : "r02/f20",
    ]));
    
}

#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(75);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r02/f21",
        "southwest" : "r02/f19",
        "south" : "r02/f20",
        "northwest" : "r04/f19",
        "east" : "r03/f21",
        "north" : "r04/f20",
        "northeast" : "r04/f21",
        "west" : "r03/f19",
    ]));
    
}

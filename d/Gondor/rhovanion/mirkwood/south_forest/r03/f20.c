#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r04/f21",
        "southwest" : "r04/f19",
        "south" : "r04/f20",
        "northwest" : "r02/f19",
        "east" : "r03/f21",
        "north" : "r02/f20",
        "northeast" : "r02/f21",
        "west" : "r03/f19",
    ]));
    
}

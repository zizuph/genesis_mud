#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r05/f21",
        "southwest" : "r05/f19",
        "south" : "r05/f20",
        "northwest" : "r03/f19",
        "east" : "r04/f21",
        "north" : "r03/f20",
        "northeast" : "r03/f21",
        "west" : "r04/f19",
    ]));
    
}

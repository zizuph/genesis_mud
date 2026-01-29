#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r40/f21",
        "southwest" : "r40/f19",
        "south" : "r40/f20",
        "northwest" : "r38/f19",
        "east" : "r39/f21",
        "north" : "r38/f20",
        "northeast" : "r38/f21",
        "west" : "r39/f19",
    ]));
    
}

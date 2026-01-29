#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r40/f35",
        "southwest" : "r40/f33",
        "south" : "r40/f34",
        "northwest" : "r38/f33",
        "east" : "r39/f35",
        "north" : "r38/f34",
        "northeast" : "r38/f35",
        "west" : "r39/f33",
    ]));
    
}

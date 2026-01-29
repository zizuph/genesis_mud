#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r39/f35",
        "southwest" : "r39/f33",
        "south" : "r39/f34",
        "northwest" : "r37/f33",
        "east" : "r38/f35",
        "north" : "r37/f34",
        "northeast" : "r37/f35",
        "west" : "r38/f33",
    ]));
    
}

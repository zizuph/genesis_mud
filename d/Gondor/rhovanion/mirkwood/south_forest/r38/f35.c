#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r39/f36",
        "southwest" : "r39/f34",
        "south" : "r39/f35",
        "northwest" : "r37/f34",
        "east" : "r38/f36",
        "north" : "r37/f35",
        "northeast" : "r37/f36",
        "west" : "r38/f34",
    ]));
    
}

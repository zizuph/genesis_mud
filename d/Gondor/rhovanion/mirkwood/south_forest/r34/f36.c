#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r35/f37",
        "southwest" : "r35/f35",
        "south" : "r35/f36",
        "northwest" : "r33/f35",
        "east" : "r34/f37",
        "north" : "r33/f36",
        "northeast" : "r33/f37",
        "west" : "r34/f35",
    ]));
    
}

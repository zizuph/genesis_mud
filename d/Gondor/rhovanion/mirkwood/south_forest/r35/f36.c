#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r36/f37",
        "southwest" : "r36/f35",
        "south" : "r36/f36",
        "northwest" : "r34/f35",
        "east" : "r35/f37",
        "north" : "r34/f36",
        "northeast" : "r34/f37",
        "west" : "r35/f35",
    ]));
    
}

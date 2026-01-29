#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r36/f38",
        "southwest" : "r36/f36",
        "south" : "r36/f37",
        "northwest" : "r34/f36",
        "east" : "r35/f38",
        "north" : "r34/f37",
        "northeast" : "r34/f38",
        "west" : "r35/f36",
    ]));
    
}

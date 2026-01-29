#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(6);
    add_mirkwood_exits(([
        "southeast" : "r36/f19",
        "southwest" : "r36/f17",
        "south" : "r36/f18",
        "northwest" : "r34/f17",
        "east" : "r35/f19",
        "north" : "r34/f18",
        "northeast" : "r34/f19",
        "west" : "r35/f17",
    ]));
    
}

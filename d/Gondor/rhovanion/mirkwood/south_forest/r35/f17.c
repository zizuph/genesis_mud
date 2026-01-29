#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(6);
    add_mirkwood_exits(([
        "southeast" : "r36/f18",
        "southwest" : "r36/f16",
        "south" : "r36/f17",
        "northwest" : "r34/f16",
        "east" : "r35/f18",
        "north" : "r34/f17",
        "northeast" : "r34/f18",
        "west" : "r35/f16",
    ]));
    
}

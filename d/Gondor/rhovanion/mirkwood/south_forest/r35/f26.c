#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(8);
    add_mirkwood_exits(([
        "southeast" : "r36/f27",
        "southwest" : "r36/f25",
        "south" : "r36/f26",
        "northwest" : "r34/f25",
        "east" : "r35/f27",
        "north" : "r34/f26",
        "northeast" : "r34/f27",
        "west" : "r35/f25",
    ]));
    
}

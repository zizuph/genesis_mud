#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(8);
    add_mirkwood_exits(([
        "southeast" : "r36/f31",
        "southwest" : "r36/f29",
        "south" : "r36/f30",
        "northwest" : "r34/f29",
        "east" : "r35/f31",
        "north" : "r34/f30",
        "northeast" : "r34/f31",
        "west" : "r35/f29",
    ]));
    
}

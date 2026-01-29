#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r36/f06",
        "southwest" : "r36/f04",
        "south" : "r36/f05",
        "northwest" : "r34/f04",
        "east" : "r35/f06",
        "north" : "r34/f05",
        "northeast" : "r34/f06",
        "west" : "r35/f04",
    ]));
    
}

#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(8);
    add_mirkwood_exits(([
        "southeast" : "r36/f24",
        "southwest" : "r36/f22",
        "south" : "r36/f23",
        "northwest" : "r34/f22",
        "east" : "r35/f24",
        "north" : "r34/f23",
        "northeast" : "r34/f24",
        "west" : "r35/f22",
    ]));
    
}

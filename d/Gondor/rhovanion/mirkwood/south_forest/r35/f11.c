#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southwest" : "r36/f10",
        "south" : "r36/f11",
        "northwest" : "r34/f10",
        "east" : "r35/f12",
        "north" : "r34/f11",
        "northeast" : "r34/f12",
        "west" : "r35/f10",
    ]));
    
}

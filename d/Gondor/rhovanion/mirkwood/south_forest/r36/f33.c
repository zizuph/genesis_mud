#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r37/f34",
        "southwest" : "r37/f32",
        "south" : "r37/f33",
        "northwest" : "r35/f32",
        "east" : "r36/f34",
        "north" : "r35/f33",
        "northeast" : "r35/f34",
        "west" : "r36/f32",
    ]));
    
}

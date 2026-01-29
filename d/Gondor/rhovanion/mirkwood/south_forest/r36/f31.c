#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(6);
    add_mirkwood_exits(([
        "southeast" : "r37/f32",
        "southwest" : "r37/f30",
        "south" : "r37/f31",
        "northwest" : "r35/f30",
        "east" : "r36/f32",
        "north" : "r35/f31",
        "northeast" : "r35/f32",
        "west" : "r36/f30",
    ]));
    
}

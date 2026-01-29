#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(7);
    add_mirkwood_exits(([
        "southeast" : "r37/f30",
        "southwest" : "r37/f28",
        "south" : "r37/f29",
        "northwest" : "r35/f28",
        "east" : "r36/f30",
        "north" : "r35/f29",
        "northeast" : "r35/f30",
        "west" : "r36/f28",
    ]));
    
}

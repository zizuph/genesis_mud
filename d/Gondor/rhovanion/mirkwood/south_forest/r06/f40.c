#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(2);
    set_spider_nest_chance(23);

    set_distance_to_edge(6);
    add_mirkwood_exits(([
        "southeast" : "r07/f41",
        "southwest" : "r07/f39",
        "south" : "r07/f40",
        "northwest" : "r05/f39",
        "east" : "r06/f41",
        "north" : "r05/f40",
        "northeast" : "r05/f41",
        "west" : "r06/f39",
    ]));
    
}

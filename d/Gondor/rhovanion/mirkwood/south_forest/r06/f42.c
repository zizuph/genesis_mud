#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(14);

    set_distance_to_edge(6);
    add_mirkwood_exits(([
        "southeast" : "r07/f43",
        "southwest" : "r07/f41",
        "south" : "r07/f42",
        "northwest" : "r05/f41",
        "east" : "r06/f43",
        "north" : "r05/f42",
        "northeast" : "r05/f43",
        "west" : "r06/f41",
    ]));
    
}

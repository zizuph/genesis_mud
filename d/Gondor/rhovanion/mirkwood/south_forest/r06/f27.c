#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(6);
    add_mirkwood_exits(([
        "southeast" : "r07/f28",
        "southwest" : "r07/f26",
        "south" : "r07/f27",
        "northwest" : "r05/f26",
        "east" : "r06/f28",
        "north" : "r05/f27",
        "northeast" : "r05/f28",
        "west" : "r06/f26",
    ]));
    
}

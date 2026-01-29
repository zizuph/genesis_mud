#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(6);
    add_mirkwood_exits(([
        "southeast" : "r07/f27",
        "southwest" : "r07/f25",
        "south" : "r07/f26",
        "northwest" : "r05/f25",
        "east" : "r06/f27",
        "north" : "r05/f26",
        "northeast" : "r05/f27",
        "west" : "r06/f25",
    ]));
    
}

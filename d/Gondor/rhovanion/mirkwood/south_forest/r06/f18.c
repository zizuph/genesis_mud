#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(6);
    add_mirkwood_exits(([
        "southeast" : "r07/f19",
        "southwest" : "r07/f17",
        "south" : "r07/f18",
        "northwest" : "r05/f17",
        "east" : "r06/f19",
        "north" : "r05/f18",
        "northeast" : "r05/f19",
        "west" : "r06/f17",
    ]));
    
}

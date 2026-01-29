#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(6);
    add_mirkwood_exits(([
        "southeast" : "r07/f20",
        "southwest" : "r07/f18",
        "south" : "r07/f19",
        "northwest" : "r05/f18",
        "east" : "r06/f20",
        "north" : "r05/f19",
        "northeast" : "r05/f20",
        "west" : "r06/f18",
    ]));
    
}

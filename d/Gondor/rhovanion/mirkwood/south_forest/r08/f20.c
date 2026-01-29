#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(8);
    add_mirkwood_exits(([
        "southeast" : "r09/f21",
        "southwest" : "r09/f19",
        "south" : "r09/f20",
        "northwest" : "r07/f19",
        "east" : "r08/f21",
        "north" : "r07/f20",
        "northeast" : "r07/f21",
        "west" : "r08/f19",
    ]));
    
}

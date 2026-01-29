#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(7);
    add_mirkwood_exits(([
        "southeast" : "r09/f14",
        "southwest" : "r09/f12",
        "south" : "r09/f13",
        "northwest" : "r07/f12",
        "east" : "r08/f14",
        "north" : "r07/f13",
        "northeast" : "r07/f14",
        "west" : "r08/f12",
    ]));
    
}

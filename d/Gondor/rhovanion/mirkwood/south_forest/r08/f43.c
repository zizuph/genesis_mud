#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(12);

    set_distance_to_edge(7);
    add_mirkwood_exits(([
        "southeast" : "r09/f44",
        "southwest" : "r09/f42",
        "south" : "r09/f43",
        "northwest" : "r07/f42",
        "east" : "r08/f44",
        "north" : "r07/f43",
        "northeast" : "r07/f44",
        "west" : "r08/f42",
    ]));
    
}

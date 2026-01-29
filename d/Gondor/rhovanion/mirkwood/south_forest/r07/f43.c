#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(18);

    set_distance_to_edge(7);
    add_mirkwood_exits(([
        "southeast" : "r08/f44",
        "southwest" : "r08/f42",
        "south" : "r08/f43",
        "northwest" : "r06/f42",
        "east" : "r07/f44",
        "north" : "r06/f43",
        "northeast" : "r06/f44",
        "west" : "r07/f42",
    ]));
    
}

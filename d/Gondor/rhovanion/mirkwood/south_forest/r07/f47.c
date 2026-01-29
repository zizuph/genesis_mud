#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(19);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r08/f48",
        "southwest" : "r08/f46",
        "south" : "r08/f47",
        "northwest" : "r06/f46",
        "east" : "r07/f48",
        "north" : "r06/f47",
        "northeast" : "r06/f48",
        "west" : "r07/f46",
    ]));
    
}

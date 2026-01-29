#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(17);

    set_distance_to_edge(7);
    add_mirkwood_exits(([
        "southeast" : "r08/f35",
        "southwest" : "r08/f33",
        "south" : "r08/f34",
        "northwest" : "r06/f33",
        "east" : "r07/f35",
        "north" : "r06/f34",
        "northeast" : "r06/f35",
        "west" : "r07/f33",
    ]));
    
}

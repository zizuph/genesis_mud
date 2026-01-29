#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(13);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r06/f35",
        "southwest" : "r06/f33",
        "south" : "r06/f34",
        "northwest" : "r08/f33",
        "east" : "r07/f35",
        "north" : "r08/f34",
        "northeast" : "r08/f35",
        "west" : "r07/f33",
    ]));
    
}

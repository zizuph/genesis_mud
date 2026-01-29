#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(72);

    set_distance_to_edge(7);
    add_mirkwood_exits(([
        "southeast" : "r08/f09",
        "southwest" : "r08/f07",
        "south" : "r08/f08",
        "northwest" : "r10/f07",
        "east" : "r09/f09",
        "north" : "r10/f08",
        "northeast" : "r10/f09",
        "west" : "r09/f07",
    ]));
    
}

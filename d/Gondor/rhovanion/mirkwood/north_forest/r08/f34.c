#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(17);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r07/f35",
        "southwest" : "r07/f33",
        "south" : "r07/f34",
        "northwest" : "r09/f33",
        "east" : "r08/f35",
        "north" : "r09/f34",
        "northeast" : "r09/f35",
        "west" : "r08/f33",
    ]));
    
}

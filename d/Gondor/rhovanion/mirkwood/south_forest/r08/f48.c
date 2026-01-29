#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(13);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r09/f49",
        "southwest" : "r09/f47",
        "south" : "r09/f48",
        "northwest" : "r07/f47",
        "east" : "r08/f49",
        "north" : "r07/f48",
        "northeast" : "r07/f49",
        "west" : "r08/f47",
    ]));
    
}

#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(11);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r09/f50",
        "southwest" : "r09/f48",
        "south" : "r09/f49",
        "northwest" : "r07/f48",
        "east" : "r08/f50",
        "north" : "r07/f49",
        "northeast" : "r07/f50",
        "west" : "r08/f48",
    ]));
    
}

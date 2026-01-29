#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(10);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r08/f50",
        "southwest" : "r08/f48",
        "south" : "r08/f49",
        "northwest" : "r06/f48",
        "east" : "r07/f50",
        "north" : "r06/f49",
        "northeast" : "r06/f50",
        "west" : "r07/f48",
    ]));
    
}

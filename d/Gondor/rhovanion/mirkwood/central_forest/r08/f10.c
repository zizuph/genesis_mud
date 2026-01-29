#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(17);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r07/f11",
        "southwest" : "r07/f09",
        "south" : "r07/f10",
        "northwest" : "r09/f09",
        "east" : "r08/f11",
        "north" : "r09/f10",
        "northeast" : "r09/f11",
        "west" : "r08/f09",
    ]));
    
}

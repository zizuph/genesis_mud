#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(16);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r07/f10",
        "southwest" : "r07/f08",
        "south" : "r07/f09",
        "northwest" : "r09/f08",
        "east" : "r08/f10",
        "north" : "r09/f09",
        "northeast" : "r09/f10",
        "west" : "r08/f08",
    ]));
    
}

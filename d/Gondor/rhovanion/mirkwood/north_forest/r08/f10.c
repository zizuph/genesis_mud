#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(76);

    set_distance_to_edge(7);
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

#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(3);
    set_spider_nest_chance(35);

    set_distance_to_edge(6);
    add_mirkwood_exits(([
        "southeast" : "r06/f11",
        "southwest" : "r06/f09",
        "south" : "r06/f10",
        "northwest" : "r08/f09",
        "east" : "r07/f11",
        "north" : "r08/f10",
        "northeast" : "r08/f11",
        "west" : "r07/f09",
    ]));
    
}

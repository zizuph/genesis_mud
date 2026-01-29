#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(10);

    set_distance_to_edge(7);
    add_mirkwood_exits(([
        "southeast" : "r08/f28",
        "southwest" : "r08/f26",
        "south" : "r08/f27",
        "northwest" : "r06/f26",
        "east" : "r07/f28",
        "north" : "r06/f27",
        "northeast" : "r06/f28",
        "west" : "r07/f26",
    ]));
    
}

#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(3);
    set_spider_nest_chance(37);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r06/f28",
        "southwest" : "r06/f26",
        "south" : "r06/f27",
        "northwest" : "r08/f26",
        "east" : "r07/f28",
        "north" : "r08/f27",
        "northeast" : "r08/f28",
        "west" : "r07/f26",
    ]));
    
}

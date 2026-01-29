#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(2);
    set_spider_nest_chance(21);

    set_distance_to_edge(6);
    add_mirkwood_exits(([
        "southeast" : "r07/f28",
        "southwest" : "r07/f26",
        "south" : "r07/f27",
        "northwest" : "r09/f26",
        "east" : "r08/f28",
        "north" : "r09/f27",
        "northeast" : "r09/f28",
        "west" : "r08/f26",
    ]));
    
}

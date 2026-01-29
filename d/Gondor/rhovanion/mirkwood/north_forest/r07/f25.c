#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(3);
    set_spider_nest_chance(33);

    set_distance_to_edge(6);
    add_mirkwood_exits(([
        "southeast" : "r06/f26",
        "southwest" : "r06/f24",
        "south" : "r06/f25",
        "northwest" : "r08/f24",
        "east" : "r07/f26",
        "north" : "r08/f25",
        "northeast" : "r08/f26",
        "west" : "r07/f24",
    ]));
    
}

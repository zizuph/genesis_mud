#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(14);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r08/f47",
        "southwest" : "r08/f45",
        "south" : "r08/f46",
        "northwest" : "r06/f45",
        "east" : "r07/f47",
        "north" : "r06/f46",
        "northeast" : "r06/f47",
        "west" : "r07/f45",
    ]));
    
}

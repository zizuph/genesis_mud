#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(7);
    add_mirkwood_exits(([
        "southeast" : "r08/f22",
        "southwest" : "r08/f20",
        "south" : "r08/f21",
        "northwest" : "r06/f20",
        "east" : "r07/f22",
        "north" : "r06/f21",
        "northeast" : "r06/f22",
        "west" : "r07/f20",
    ]));
    
}

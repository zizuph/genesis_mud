#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(61);

    set_distance_to_edge(7);
    add_mirkwood_exits(([
        "southeast" : "r08/f39",
        "southwest" : "r08/f37",
        "south" : "r08/f38",
        "northwest" : "r06/f37",
        "east" : "r07/f39",
        "north" : "r06/f38",
        "northeast" : "r06/f39",
        "west" : "r07/f37",
    ]));
    
}

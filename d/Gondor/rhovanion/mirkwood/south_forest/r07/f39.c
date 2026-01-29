#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(3);
    set_spider_nest_chance(30);

    set_distance_to_edge(7);
    add_mirkwood_exits(([
        "southeast" : "r08/f40",
        "southwest" : "r08/f38",
        "south" : "r08/f39",
        "northwest" : "r06/f38",
        "east" : "r07/f40",
        "north" : "r06/f39",
        "northeast" : "r06/f40",
        "west" : "r07/f38",
    ]));
    
}

#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(12);

    set_distance_to_edge(8);
    add_mirkwood_exits(([
        "southeast" : "r09/f40",
        "southwest" : "r09/f38",
        "south" : "r09/f39",
        "northwest" : "r07/f38",
        "east" : "r08/f40",
        "north" : "r07/f39",
        "northeast" : "r07/f40",
        "west" : "r08/f38",
    ]));
    
}

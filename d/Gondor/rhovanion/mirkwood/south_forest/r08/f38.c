#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(4);
    set_spider_nest_chance(42);

    set_distance_to_edge(8);
    add_mirkwood_exits(([
        "southeast" : "r09/f39",
        "southwest" : "r09/f37",
        "south" : "r09/f38",
        "northwest" : "r07/f37",
        "east" : "r08/f39",
        "north" : "r07/f38",
        "northeast" : "r07/f39",
        "west" : "r08/f37",
    ]));
    
}

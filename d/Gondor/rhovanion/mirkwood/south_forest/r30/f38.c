#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r31/f39",
        "southwest" : "r31/f37",
        "south" : "r31/f38",
        "northwest" : "r29/f37",
        "east" : "r30/f39",
        "north" : "r29/f38",
        "northeast" : "r29/f39",
        "west" : "r30/f37",
    ]));
    
}

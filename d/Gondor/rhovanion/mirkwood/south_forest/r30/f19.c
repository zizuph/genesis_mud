#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(7);
    add_mirkwood_exits(([
        "southeast" : "r31/f20",
        "southwest" : "r31/f18",
        "south" : "r31/f19",
        "northwest" : "r29/f18",
        "east" : "r30/f20",
        "north" : "r29/f19",
        "northeast" : "r29/f20",
        "west" : "r30/f18",
    ]));
    
}

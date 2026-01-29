#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r31/f18",
        "southwest" : "r31/f16",
        "south" : "r31/f17",
        "northwest" : "r29/f16",
        "east" : "r30/f18",
        "north" : "r29/f17",
        "northeast" : "r29/f18",
        "west" : "r30/f16",
    ]));
    
}

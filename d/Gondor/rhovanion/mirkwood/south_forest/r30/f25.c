#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(13);
    add_mirkwood_exits(([
        "southeast" : "r31/f26",
        "southwest" : "r31/f24",
        "south" : "r31/f25",
        "northwest" : "r29/f24",
        "east" : "r30/f26",
        "north" : "r29/f25",
        "northeast" : "r29/f26",
        "west" : "r30/f24",
    ]));
    
}

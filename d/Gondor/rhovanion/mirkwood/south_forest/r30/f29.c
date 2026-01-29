#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(12);
    add_mirkwood_exits(([
        "southeast" : "r31/f30",
        "southwest" : "r31/f28",
        "south" : "r31/f29",
        "northwest" : "r29/f28",
        "east" : "r30/f30",
        "north" : "r29/f29",
        "northeast" : "r29/f30",
        "west" : "r30/f28",
    ]));
    
}

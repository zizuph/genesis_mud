#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(11);
    add_mirkwood_exits(([
        "southeast" : "r31/f31",
        "southwest" : "r31/f29",
        "south" : "r31/f30",
        "northwest" : "r29/f29",
        "east" : "r30/f31",
        "north" : "r29/f30",
        "northeast" : "r29/f31",
        "west" : "r30/f29",
    ]));
    
}

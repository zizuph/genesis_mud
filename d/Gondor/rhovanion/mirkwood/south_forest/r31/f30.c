#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(12);
    add_mirkwood_exits(([
        "southeast" : "r32/f31",
        "southwest" : "r32/f29",
        "south" : "r32/f30",
        "northwest" : "r30/f29",
        "east" : "r31/f31",
        "north" : "r30/f30",
        "northeast" : "r30/f31",
        "west" : "r31/f29",
    ]));
    
}

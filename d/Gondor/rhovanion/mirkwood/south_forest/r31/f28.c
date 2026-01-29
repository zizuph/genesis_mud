#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(12);
    add_mirkwood_exits(([
        "southeast" : "r32/f29",
        "southwest" : "r32/f27",
        "south" : "r32/f28",
        "northwest" : "r30/f27",
        "east" : "r31/f29",
        "north" : "r30/f28",
        "northeast" : "r30/f29",
        "west" : "r31/f27",
    ]));
    
}

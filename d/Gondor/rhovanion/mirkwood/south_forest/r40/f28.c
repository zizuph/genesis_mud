#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r41/f29",
        "southwest" : "r41/f27",
        "south" : "r41/f28",
        "northwest" : "r39/f27",
        "east" : "r40/f29",
        "north" : "r39/f28",
        "northeast" : "r39/f29",
        "west" : "r40/f27",
    ]));
    
}

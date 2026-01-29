#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r41/f27",
        "southwest" : "r41/f25",
        "south" : "r41/f26",
        "northwest" : "r39/f25",
        "east" : "r40/f27",
        "north" : "r39/f26",
        "northeast" : "r39/f27",
        "west" : "r40/f25",
    ]));
    
}

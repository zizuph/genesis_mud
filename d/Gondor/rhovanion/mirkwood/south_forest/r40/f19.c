#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r41/f20",
        "southwest" : "r41/f18",
        "south" : "r41/f19",
        "northwest" : "r39/f18",
        "east" : "r40/f20",
        "north" : "r39/f19",
        "northeast" : "r39/f20",
        "west" : "r40/f18",
    ]));
    
}

#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(3);
    add_mirkwood_exits(([
        "southeast" : "r41/f24",
        "southwest" : "r41/f22",
        "south" : "r41/f23",
        "northwest" : "r39/f22",
        "east" : "r40/f24",
        "north" : "r39/f23",
        "northeast" : "r39/f24",
        "west" : "r40/f22",
    ]));
    
}

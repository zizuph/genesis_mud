#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(11);
    add_mirkwood_exits(([
        "southeast" : "r31/f24",
        "southwest" : "r31/f22",
        "south" : "r31/f23",
        "northwest" : "r29/f22",
        "east" : "r30/f24",
        "north" : "r29/f23",
        "northeast" : "r29/f24",
        "west" : "r30/f22",
    ]));
    
}

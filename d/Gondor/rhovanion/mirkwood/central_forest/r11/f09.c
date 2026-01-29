#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(13);

    set_distance_to_edge(1);
    add_mirkwood_exits(([
        "southeast" : "r10/f10",
        "southwest" : "r10/f08",
        "south" : "r10/f09",
        "northwest" : "r12/f08",
        "east" : "r11/f10",
        "north" : "r12/f09",
        "northeast" : "r12/f10",
        "west" : "r11/f08",
    ]));
    
}

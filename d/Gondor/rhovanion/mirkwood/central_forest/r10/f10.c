#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(16);

    set_distance_to_edge(2);
    add_mirkwood_exits(([
        "southeast" : "r09/f11",
        "southwest" : "r09/f09",
        "south" : "r09/f10",
        "northwest" : "r11/f09",
        "east" : "r10/f11",
        "north" : "r11/f10",
        "northeast" : "r11/f11",
        "west" : "r10/f09",
    ]));
    
}

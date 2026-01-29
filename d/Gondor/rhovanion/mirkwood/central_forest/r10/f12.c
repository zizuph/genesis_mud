#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(15);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r09/f13",
        "southwest" : "r09/f11",
        "south" : "r09/f12",
        "northwest" : "r11/f11",
        "east" : "r10/f13",
        "north" : "r11/f12",
        "northeast" : "r11/f13",
        "west" : "r10/f11",
    ]));
    
}

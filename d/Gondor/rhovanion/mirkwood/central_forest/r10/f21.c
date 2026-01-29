#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(71);

    set_distance_to_edge(6);
    add_mirkwood_exits(([
        "southeast" : "r09/f22",
        "southwest" : "r09/f20",
        "south" : "r09/f21",
        "northwest" : "r11/f20",
        "east" : "r10/f22",
        "north" : "r11/f21",
        "northeast" : "r11/f22",
        "west" : "r10/f20",
    ]));
    
}

#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(6);
    add_mirkwood_exits(([
        "southeast" : "r11/f13",
        "southwest" : "r11/f11",
        "south" : "r11/f12",
        "northwest" : "r09/f11",
        "east" : "r10/f13",
        "north" : "r09/f12",
        "northeast" : "r09/f13",
        "west" : "r10/f11",
    ]));
    
}

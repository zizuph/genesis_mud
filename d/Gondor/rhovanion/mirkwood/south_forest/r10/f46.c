#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(17);

    set_distance_to_edge(4);
    add_mirkwood_exits(([
        "southeast" : "r11/f47",
        "southwest" : "r11/f45",
        "south" : "r11/f46",
        "northwest" : "r09/f45",
        "east" : "r10/f47",
        "north" : "r09/f46",
        "northeast" : "r09/f47",
        "west" : "r10/f45",
    ]));
    
}

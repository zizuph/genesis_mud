#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(10);
    add_mirkwood_exits(([
        "southeast" : "r11/f19",
        "southwest" : "r11/f17",
        "south" : "r11/f18",
        "northwest" : "r09/f17",
        "east" : "r10/f19",
        "north" : "r09/f18",
        "northeast" : "r09/f19",
        "west" : "r10/f17",
    ]));
    
}

#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r12/f46",
        "southwest" : "r12/f44",
        "south" : "r12/f45",
        "northwest" : "r10/f44",
        "east" : "r11/f46",
        "north" : "r10/f45",
        "northeast" : "r10/f46",
        "west" : "r11/f44",
    ]));
    
}

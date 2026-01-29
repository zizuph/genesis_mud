#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(0);
    set_spider_nest_chance(0);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r13/f46",
        "southwest" : "r13/f44",
        "south" : "r13/f45",
        "northwest" : "r11/f44",
        "east" : "r12/f46",
        "north" : "r11/f45",
        "northeast" : "r11/f46",
        "west" : "r12/f44",
    ]));
    
}

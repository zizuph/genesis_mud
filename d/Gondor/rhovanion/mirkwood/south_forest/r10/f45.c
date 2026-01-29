#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(11);

    set_distance_to_edge(5);
    add_mirkwood_exits(([
        "southeast" : "r11/f46",
        "southwest" : "r11/f44",
        "south" : "r11/f45",
        "northwest" : "r09/f44",
        "east" : "r10/f46",
        "north" : "r09/f45",
        "northeast" : "r09/f46",
        "west" : "r10/f44",
    ]));
    
}

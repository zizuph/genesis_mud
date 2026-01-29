#include "../../defs.h";

inherit MIRKWOOD_SOUTH_FOREST_DIR + "forest";

void create_mirkwood_south_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(17);

    set_distance_to_edge(6);
    add_mirkwood_exits(([
        "southeast" : "r11/f45",
        "southwest" : "r11/f43",
        "south" : "r11/f44",
        "northwest" : "r09/f43",
        "east" : "r10/f45",
        "north" : "r09/f44",
        "northeast" : "r09/f45",
        "west" : "r10/f43",
    ]));
    
}

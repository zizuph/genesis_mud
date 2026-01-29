#include "../../defs.h";

inherit MIRKWOOD_NORTH_FOREST_DIR + "forest";

void create_mirkwood_north_forest_forest_room() {

    set_max_spider_nest_size(2);
    set_spider_nest_chance(25);

    set_distance_to_edge(8);
    add_mirkwood_exits(([
        "southeast" : "r09/f27",
        "southwest" : "r09/f25",
        "south" : "r09/f26",
        "northwest" : "r11/f25",
        "east" : "r10/f27",
        "north" : "r11/f26",
        "northeast" : "r11/f27",
        "west" : "r10/f25",
    ]));
    
}

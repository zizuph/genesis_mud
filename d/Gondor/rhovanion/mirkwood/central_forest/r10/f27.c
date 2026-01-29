#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(69);

    set_distance_to_edge(8);
    add_mirkwood_exits(([
        "southeast" : "r09/f28",
        "southwest" : "r09/f26",
        "south" : "r09/f27",
        "northwest" : "r11/f26",
        "east" : "r10/f28",
        "north" : "r11/f27",
        "northeast" : "r11/f28",
        "west" : "r10/f26",
    ]));
    
}

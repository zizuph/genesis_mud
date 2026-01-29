#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(74);

    set_distance_to_edge(6);
    add_mirkwood_exits(([
        "southeast" : "r09/f23",
        "southwest" : "r09/f21",
        "south" : "r09/f22",
        "northwest" : "r11/f21",
        "east" : "r10/f23",
        "north" : "r11/f22",
        "northeast" : "r10/f23",
        "west" : "r10/f21",
    ]));
    
}

#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(2);
    set_spider_nest_chance(27);

    set_distance_to_edge(7);
    add_mirkwood_exits(([
        "southeast" : "r09/f18",
        "southwest" : "r09/f16",
        "south" : "r09/f17",
        "northwest" : "r11/f16",
        "east" : "r10/f18",
        "north" : "r11/f17",
        "northeast" : "r11/f18",
        "west" : "r10/f16",
    ]));
    
}

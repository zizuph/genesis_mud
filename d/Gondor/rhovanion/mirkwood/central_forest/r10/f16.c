#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(1);
    set_spider_nest_chance(19);

    set_distance_to_edge(7);
    add_mirkwood_exits(([
        "southeast" : "r09/f17",
        "southwest" : "r09/f15",
        "south" : "r09/f16",
        "northwest" : "r11/f15",
        "east" : "r10/f17",
        "north" : "r11/f16",
        "northeast" : "r11/f17",
        "west" : "r10/f15",
    ]));
    
}

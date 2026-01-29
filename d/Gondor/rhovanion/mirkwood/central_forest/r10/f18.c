#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(2);
    set_spider_nest_chance(22);

    set_distance_to_edge(6);
    add_mirkwood_exits(([
        "southeast" : "r09/f19",
        "southwest" : "r09/f17",
        "south" : "r09/f18",
        "northwest" : "r11/f17",
        "east" : "r10/f19",
        "north" : "r11/f18",
        "northeast" : "r11/f19",
        "west" : "r10/f17",
    ]));
    
}

#include "../../defs.h";

inherit MIRKWOOD_CENTRAL_FOREST_DIR + "forest";

void create_mirkwood_central_forest_forest_room() {

    set_max_spider_nest_size(5);
    set_spider_nest_chance(57);

    set_distance_to_edge(6);
    add_mirkwood_exits(([
        "southeast" : "r09/f20",
        "southwest" : "r09/f18",
        "south" : "r09/f19",
        "northwest" : "r11/f18",
        "east" : "r10/f20",
        "north" : "r11/f19",
        "northeast" : "r11/f20",
        "west" : "r10/f18",
    ]));
    
}
